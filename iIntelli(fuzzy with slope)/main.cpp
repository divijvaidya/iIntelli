/* 
 * File:   main.cpp
 * Author: Divij
 *
 * Created on 27 March, 2011, 12:35 PM
 */
#include "Definitions.h"


word lookupDB(string query_word){
    /* Returns word with key as empty string if the word is not found
     * else
     * It returns word
     */
    word n;
    n.key="-1";
    if(database.count(query_word)==0)return n;
    else
        return database[query_word];
}

word* lookupDBcheck(string query_word){
    /* Returns word with key as empty string if the word is not found
     * else
     * It returns word
     */
    //word n;
    //n.key="-1";
    //if(database.count(query_word)==0)return n;
    //else
        return &database[query_word];
}

void posTagger(word root){

    string base=root.key;
    int j=1,i,flag;
    string ss="",ssa,ssb,base_type;
    multimap<string,string> m;

    
    ifstream iifile;
    iifile.open("tag_o.txt");
    while(iifile>>ss){
	i=0;
	ssa="";
	ssb="";
	flag=0;
	while(ss[i]!='_'){
	    ssa+=ss[i];
	    i++;
	}

	if(ssa==base){
	    flag=1;
	}
	//ssa=ssa+'-'+(char)(j+'0');
	i++;
	while(i<ss.length()){
		ssb+=ss[i];
		i++;
	}
	if(flag==1){//storing the type of the base word so that other words with the same type can be found out
	    base_type=ssb;
	    flag=0;
	}
	m.insert( pair<string,string>(ssb,ssa));//Stores the word as data with their type as key
	j++;
    }
    iifile.close();
   

    multimap<string,string> ::iterator it;
    /*for(it=m.begin();it!=m.end();it++){
	cout << it->first<< " "<<it->second<<endl;
    }*/

    //=============Now we start inserting words into the mesh==============//
    multimap<string,string> ::iterator itr;

    // More things can be added here. Right now it just sees the same relation as per pos tagger
    for(itr=m.begin();itr!=m.end();itr++){
	if(itr->first==base_type){
	    //then itr->second is a word having the same type as our base word in the sentence
            if(lookupDB(itr->second).key!=""){//the word already exists
		edge e1;
		e1.weight=ST_WEIGHT;//=========================================check
		e1.relation="ST";
                e1.topic=base;//put main topic of discussion here
		e1.firstWord=root;
		e1.secondWord=lookupDB(itr->second);
                e1.slope=SLOPE;

                word* pot;
                pot=lookupDBcheck(itr->second);
                (*pot).connections.push_back(e1);

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }else{
		word newWord;
		newWord.key=itr->second;

		edge e1;
		e1.weight=ST_WEIGHT;//=========================================check
		e1.relation="ST";
                e1.topic=base;//put main topic of discussion here
		e1.firstWord=root;
		e1.secondWord=newWord;
                e1.slope=SLOPE;

                newWord.connections.push_back(e1);


		database[newWord.key]=newWord;
                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }
	}else if(itr->first=="NN" || itr->first=="NNS" || itr->first=="NNP" || itr->first=="NNPS"){
	    //then itr->second is a word which is a noun in the sentence
	    if(lookupDB(itr->second).key!=""){
		edge e1;
		e1.weight=SNN_WEIGHT;//=========================================check
		e1.relation="SNN";
                e1.topic=base;//put main topic of discussion here
		e1.firstWord=root;
		e1.secondWord=lookupDB(itr->second);
                e1.slope=SLOPE;

                word* pot;
                pot=lookupDBcheck(itr->second);
                (*pot).connections.push_back(e1);

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }else{
		word newWord;
		newWord.key=itr->second;

		edge e1;
		e1.weight=SNN_WEIGHT;//=========================================check
		e1.relation="SNN";
                e1.topic=base;//put main topic of discussion here
		e1.firstWord=root;
		e1.secondWord=newWord;
                e1.slope=SLOPE;

                newWord.connections.push_back(e1);


		database[newWord.key]=newWord;
                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }
	}else if(itr->first=="JJ"){
	    //then itr->second is a word which is an adjective in the sentence
            if(lookupDB(itr->second).key!=""){
		edge e1;
		e1.weight=SA_WEIGHT;//=========================================check
		e1.relation="SA";
                e1.topic=base;//put main topic of discussion here
		e1.firstWord=root;
		e1.secondWord=lookupDB(itr->second);
                e1.slope=SLOPE;

                word* pot;
                pot=lookupDBcheck(itr->second);
                (*pot).connections.push_back(e1);

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }else{
		word newWord;
		newWord.key=itr->second;

		edge e1;
		e1.weight=SA_WEIGHT;//=========================================check
		e1.relation="SA";
                e1.topic=base;//put main topic of discussion here
		e1.firstWord=root;
		e1.secondWord=newWord;
                e1.slope=SLOPE;

                newWord.connections.push_back(e1);


		database[newWord.key]=newWord;
                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }
	}
    }

    return;
}

bool findkey(string temp,string base)
{
    string s="";
    for(int i=0;i<temp.size();i++){
	if(temp[i]==' '){
	    if(s==base)return true;
	    s="";
	}else
	    s+=temp[i];
    }
    if(s==base)return true;
    return false;
    //finds the presence of base in text temp.
}

void posParser(word root)
{
    string base=root.key;
    string ss,ssa,ssb,ssc;
    int i;

    ifstream ifile;
    ifile.open("par_final.txt");

   
    multimap<string,string> mm;// stores the relation as the key and second word as the data

    while(getline(ifile,ss)){
	if(ss==""){
	    continue;
	}

	i=0;
	ssa="";//Stores the type of relation
	ssb="";//first word i.e. the base word
	ssc="";//second word
	while(ss[i]!='('){
		ssa+=ss[i];
		i++;
	}
	i++;

	while(ss[i]!='-'){
		ssb+=ss[i];
		i++;
	}
	i++;
	while(ss[i]!=','){
	    i++;
	}
	i++;
	while(ss[i]!='-'){
		ssc+=ss[i];
		i++;
	}
	i++;
	while(ss[i]!=')'){
	    i++;
	}
	int flag=0;
	
	if(ssa=="abbrev" || ssa=="acomp" || ssa=="agent" || ssa=="cop" || ssa=="nn" || ssa=="poss" || ssa=="rcmod" || ssa=="ref"){
	    if(ssb==base){
		mm.insert(pair<string,string>(ssa,ssc));
	    }else{
		mm.insert(pair<string,string>(ssa,ssb));
	    }
	}
    }
    ifile.close();
    
    //all permissible relations checked.
    multimap<string,string> :: iterator itr;
   /* for(itr=mm.begin();itr!=mm.end();itr++){
	cout << itr->first << " " << itr->second << "\n";
    }*/
    for(itr=mm.begin();itr!=mm.end();itr++){
        if(itr->first=="nn"){
	    if(lookupDB(itr->second).key==""){
	        word newWord;
	        newWord.key=itr->second;
	
    		edge e1;
		e1.weight=NN_WEIGHT;
		e1.relation="NN";
                e1.topic=base;//Add the topic here
		e1.firstWord=root;
		e1.secondWord=newWord;
                e1.slope=SLOPE;

                newWord.connections.push_back(e1);
		
		database[newWord.key]=newWord;
                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);
	    }else{
	        edge e1;
	        e1.weight=NN_WEIGHT;
	        e1.relation="NN";
                e1.topic=base;//Add the topic here
	        e1.firstWord=root;
	        e1.secondWord=lookupDB(itr->second);
                e1.slope=SLOPE;

                word* pot;
                pot=lookupDBcheck(itr->second);
                (*pot).connections.push_back(e1);

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);
	    }
	}
    }
    return;
}

void exeWordnet(word root)
{
    string base=root.key;


    //for hyponyms
    insert_hype(root.key);
    for(int i=0;i<hype.size();++i){
            if(lookupDB(hype[i]).key=="-1"){
	        word newWord;
	        newWord.key=hype[i];

    		edge e1;
		e1.weight=HYN_WEIGHT;
		e1.relation="HYN";
                e1.topic=base;//Add the topic here
		e1.firstWord=root;
		e1.secondWord=newWord;
                e1.slope=SLOPE;

                newWord.connections.push_back(e1);

		database[newWord.key]=newWord;
                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }else{
	        edge e1;
	        e1.weight=HYN_WEIGHT;
	        e1.relation="HYN";
                e1.topic=base;//Add the topic here
	        e1.firstWord=root;
	        e1.secondWord=lookupDB(hype[i]);
                e1.slope=SLOPE;

                word* pot;
                pot=lookupDBcheck(hype[i]);
                (*pot).connections.push_back(e1);

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);
                lookupDB(base).key="blah";
	    }

    }

    insert_deri(root.key);
	//for derived words
	//cout<<"derived\n";
	for(int i=0;i<deri.size();++i){
            if(lookupDB(deri[i]).key=="-1"){
	        word newWord;
	        newWord.key=deri[i];

    		edge e1;
		e1.weight=DERI_WEIGHT;
		e1.relation="DERI";
                e1.topic=base;//Add the topic here
		e1.firstWord=root;
		e1.secondWord=newWord;
                e1.slope=SLOPE;

                newWord.connections.push_back(e1);

		database[newWord.key]=newWord;
                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);
	    }else{
	        edge e1;
	        e1.weight=DERI_WEIGHT;
	        e1.relation="DERI";
                e1.topic=base;//Add the topic here
	        e1.firstWord=root;
	        e1.secondWord=lookupDB(deri[i]);
                e1.slope=SLOPE;

                word* pot;
                pot=lookupDBcheck(deri[i]);
                (*pot).connections.push_back(e1);

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);
	    }
	}

	//for synonyms

	insert_syns(root.key);
	for(int i=0;i<syns.size();++i){
            if(lookupDB(syns[i]).key=="-1"){
	        word newWord;
	        newWord.key=syns[i];

    		edge e1;
		e1.weight=SYN_WEIGHT;
		e1.relation="SYN";
                e1.topic=base;//Add the topic here
		e1.firstWord=root;
		e1.secondWord=newWord;
                e1.slope=SLOPE;


                newWord.connections.push_back(e1);


		database[newWord.key]=newWord;

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);
	    }else{
	        edge e1;
	        e1.weight=SYN_WEIGHT;
	        e1.relation="SYN";
                e1.topic=base;//Add the topic here
	        e1.firstWord=root;
	        e1.secondWord=lookupDB(syns[i]);
                e1.slope=SLOPE;
                word* pot;
                pot=lookupDBcheck(syns[i]);
                (*pot).connections.push_back(e1);

                word* ref;
                ref=lookupDBcheck(base);
                (*ref).connections.push_back(e1);

	    }
	}

	return;
}
void parseSentence(string s,word root )
{

    //parse using pos tagger and
    fstream ofile("data.txt",ios::out);
    ofile << s;
    ofile.close();
  
    string sss="sh run.sh data.txt > tag_o.txt";
   

    system(sss.c_str());
    posTagger(root);//Inserts the relations produced by the posTagger into the main database

    

    system("sh parser.sh data.txt > par_o.txt");

    string word_command="cat par_o.txt | grep ";
    word_command+=root.key;
    word_command+=" > par_final.txt";
    system(word_command.c_str());
    
    
    
    posParser(root);//Inserts the relations produced by the posParser into the main database

    string wordnet_command="";

    exeWordnet(root);//Insert the words produces by the wordnet
/*
    for(int i=0;i<database.size();i++){
	cout << database[i].key << endl;
    }
    int c;
    cin >> c;*/
   
}


void evaluate(string base)
{

    string index=base;
    vector<word> relatedWords;
    vector<double> relatedWeights;
    char ch;

    for(int i=0;i<database[index].connections.size();i++){
        if(database[index].connections[i].secondWord.key!=base){
            relatedWords.push_back(database[index] .connections[i].secondWord);
            relatedWeights.push_back(database[index].connections[i].weight);
        }else{
            relatedWords.push_back(database[index].connections[i].firstWord);
            relatedWeights.push_back(database[index].connections[i].weight);
        }
    }
    fstream ifile("source.txt",ios::in);

    string temp="";
    double score_value=0.0;
    double score_slope=0.0;

    //double score=0.0;

    priorityq q;

        int flag=0;
    while(!ifile.eof()){
        ifile.get(ch);
        if(ch=='[')flag=1;
        if(ch==']'){
                flag=0;
                continue;
        }

        f_number* fuzzyScore;
        fuzzyScore = new f_number;
        fuzzyScore->a = 0.0;
        fuzzyScore->lambda = SLOPE;

        if(flag==1)continue;
        if(ch=='.'){
            if(findkey(temp,base)){
                f_number* fuzzytemp;
                fuzzytemp = new f_number;
                fuzzytemp->a = getntof(KEY_WEIGHT);
                fuzzytemp->lambda = SLOPE;
                fuzzyScore=fuzzy_addition(fuzzyScore,fuzzytemp);
            }
            for(int i=0;i<relatedWords.size();i++){
                if(findkey(temp,relatedWords[i].key)){//Look if the sentence contains the word
                    f_number* fuzzytemp;
                    fuzzytemp = new f_number;
                    fuzzytemp->a = getntof(relatedWeights[i]);
                    fuzzytemp->lambda = SLOPE;
                    fuzzyScore=fuzzy_addition(fuzzyScore,fuzzytemp);

                   //score+=(relatedWeights[i]);//Scoring the sentence;
                }
            }

            score_value=getfton(fuzzyScore);
            score_slope=fuzzyScore->lambda;
            //cout << "score\t" << score_value << score_slope << endl;
            q.add(temp,score_value,score_slope);
            //Adding the sentence and the score to a heap
            temp="";
            score_value=0.0;
            score_slope=0.0;
        }else{
            temp+=ch;
        }
    }
    ifile.close();

    q.buildHeap();

    fstream ofile("out.txt",ios::out);
    int a=q.heap.size();
    for(int i=0;i<a;i++){
        ofile << q.top().sentence;
        ofile << "." << endl;
        //cout << q.top().sentence << endl;
        q.remove();
    }

}

int main(int argc, char* argv[]) {
//cout << argc << endl;

	string base="";
	for(int i=1;i<argc;i++){
		string temp(argv[i]);
		base+=temp;
	}    


    word root;
    if(lookupDB(base).key=="-1"){
	root.key=base;
	database[base]=root;
    }else{
	root=lookupDB(base);
    }



    fstream ifile("source.txt",ios::in);
    char ch;
    string temp="";

    vector<string> probable;

    while(!ifile.eof()){
	//cout << "Reading Char" << endl;
	ifile.get(ch);
	ch=tolower(ch);

	if(ch==';'|| ch==')' || ch=='(')continue;//done so that shell doesn;t stop
	if(ch=='.'){
	    //cout << "Full Stop"<<endl;
	    //cout << temp << endl;
	    if(findkey(temp,base)){//Look if the sentence contains the base word
		probable.push_back(temp);
	    }
	    temp="";
	}else{
	    temp+=ch;
	}
    }


    ifile.close();
    
    for(int i=0;i<probable.size();i++){
	parseSentence(probable[i],root);//Add words from the sentence to the mesh
    }

    /*map<string,word> :: iterator point;
    for(point=database.begin();point!=database.end();point++){
	cout << point->first << endl;
        cout << "size "<< point->second.connections.size() << endl;
    }*/

    //till now we'd have the word mesh!!

    //Now we'd extract the sentences that contain the words in the word mesh with a certain threshold weigtage

    evaluate(base);
   
    return 0;
}
