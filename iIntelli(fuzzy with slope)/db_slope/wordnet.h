// wrrapper C++ Header for using  Word Net
#include "Definitions.h"

void insert_hype(string word)
{
	int i,j,k,flag=1;
	string s,t,ww;
	s= "wn "+ word + " -hypen -hypev  >temp.txt";
	
	system(s.c_str()); // hypen and hypev
	//extracting words
	ifstream fi;
	fi.open("temp.txt");
	while(fi>>t){
		g:;
		if(t.compare("Sense")==0){
			fi>>t;
			flag=0;
		}
		while(flag==0){
			fi>>t;//got our first word.
			while(t[t.length()-1]!=','){
				if(t.compare(word)!=0 && t.compare("=>")!=0 ) {
					ww+=t+" ";
				}
				if(!(fi>>t)){
					if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
						hype.push_back(ww);
					}
					ww="";
					goto end;
				}
		
				if(t.compare("=>")==0){
					if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
						hype.push_back(ww);
					}
					ww="";
					flag=1;
					goto g;
				}
			}
			if(!flag){
				string te =t.substr(0,t.length()-1);
				if(te.compare(word)!=0 && te.compare("=")!=0){
					ww+=te;
				}
			}
			if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
				hype.push_back(ww);
				ww="";
			}
		
		}
	}
	end:;
	//removing duplicates
	sort(hype.begin(),hype.end());
	vector<string> ::iterator it;
	it=unique(hype.begin(),hype.end());
	hype.resize(it-hype.begin());
	fi.close();
}
void insert_deri(string word)
{
	int i,j,k,flag=1;
	string s,t,ww;
	s= "wn "+ word + " -derin -deriv  > temp.txt";
	system(s.c_str()); // derin and deriv
	//extracting words
	ifstream fi;
	fi.open("temp.txt");
	while(fi>>t){
		g:;
		if(t.compare("=>")==0){
			flag=0;
		}
		while(flag==0){
			fi>>t;//got our first word.
			while(t[t.length()-1]!=','){
				if(t.compare(word)!=0 && t.compare("=>")!=0 ) {
					ww+=t+" ";
				}
				if(!(fi>>t)){
					if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
						deri.push_back(ww);
					}
					ww="";
					goto end;
				}
		
				if(t.compare("RELATED")==0 || t.compare("Sense")==0){
					if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
						deri.push_back(ww);
					}
					ww="";
					flag=1;
					goto g;
				}
			}
			if(!flag){
				string te =t.substr(0,t.length()-1);
				if(te.compare(word)!=0 && te.compare("=")!=0){
					ww+=te;
				}
			}
			if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
				deri.push_back(ww);
				ww="";
			}
		
		}
	}
	end:;
	
	//removing duplicates
	sort(deri.begin(),deri.end());
	vector<string> ::iterator it;
	it=unique(deri.begin(),deri.end());
	deri.resize(it - deri.begin());
	fi.close();
	
}
int insert_syns(string word)
{
	//data after line "Sense #" like hype
	int i,j,k,flag=1;
	string s,t,t2,ww;
	s= "wn "+ word + " -synsn -synsv -synsa -synsr >temp.txt";
	//cout<<s<<"\n";
	system(s.c_str()); // synonyms
	//extracting words
	ifstream fi;
	fi.open("temp.txt");
	while(fi>>t){
		g:;
		if(t.compare("Sense")==0){
			fi>>t;
			flag=0;
		}
		while(flag==0){
			fi>>t;//got our first word.
			while(t[t.length()-1]!=','){
				if(t.compare(word)!=0 && t.compare("=>")!=0 ) {
					ww+=t+" ";
				}
				if(!(fi>>t)){
					if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
						syns.push_back(ww);
					}
					ww="";
					goto end;
				}
		
				if(t.compare("=>")==0){
					if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
						syns.push_back(ww);
					}
					ww="";
					flag=1;
					goto g;
				}
			}
			if(!flag){
				string te =t.substr(0,t.length()-1);
				if(te.compare(word)!=0 && te.compare("=")!=0){
					ww+=te;
				}
			}
			if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
				syns.push_back(ww);
				ww="";
			}
		
		}
	}
	end:;
	fi.close();
	
	//now inserting like deriv after '=>'
	ifstream fi2;
	s="cat temp.txt|grep '=>' >t.txt";
	system(s.c_str());
	fi2.open("t.txt");
	flag=1;

	while(getline(fi2,t)){
		g2:;
		ww="";
		stringstream ss;
		ss<<t;
		ss>>t2;
		if(t2.compare("=>")==0){
			flag=0;
		}
		while(flag==0){
			ss>>t2;//got our first word.
		
			while(t2[t2.length()-1]!=','){
				if(t2.compare(word)!=0) {
					ww+=t2+" ";
				}
				if(!(ss>>t2)){
					if(ww.compare(word)!=0 && ww.compare("")!=0){
						syns.push_back(ww);
					}
					ww="";
					goto end2;
				}
			}
			if(t2[t2.length()-1]==','){
				t2 =t2.substr(0,t2.length()-1);
				ww+=t2;
			}
			
			if(ww.compare(word)!=0 && ww.compare("")!=0 && ww[0]>=97){
					syns.push_back(ww);
					ww="";
			}	
		}
		end2:;
	}
	//removing all erronous data
	for(i=0;i<syns.size();++i){
		for(j=0;j<syns[i].length();++j){
			if(syns[i][j]==' '){
				continue;
			}
			if(syns[i][j]=='(' || (syns[i][j]<97)){
				t=syns[i];
				syns[i]=t.substr(0,j);
			}
		}
	}
	sort(syns.begin(),syns.end());
	vector<string> ::iterator it;
	it=unique(syns.begin(),syns.end());
	syns.resize(it - syns.begin());
}
