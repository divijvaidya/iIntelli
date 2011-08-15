#ifndef DATABASE_H
#define	DATABASE_H
#include "Definitions.h"

void loaddb()
{
	ifstream ifile;
	ifile.open("database.bin");
	word kk;
	edge e;
	int i,j,n;
	string s,s1;
	stringstream sstr;
	
	while(ifile>>s1){
		s=s1;
		ifile>>n;
		word k ;
		for(i=0;i<n;i++) {
			edge et;
			for(j=0;j<6;j++) {
				switch(j) {
					case 0:
						ifile>>et.firstWord.key;
						break;
					case 1:
						ifile>>et.secondWord.key;
						break;
					case 2:
						ifile>>et.weight;
						break;
					case 3:	
						ifile>>et.slope;
						break;
					case 4:
						ifile>>et.topic;
						break;
					case 5:
						ifile>>et.relation;
						break;
				}
			}
			k.connections.push_back(et);
		}
		database[s]=k;
	}
	ifile.close();
}
void writedb()
{
	ofstream ofile("database.bin");
	map<string,word> :: iterator il;
	for(il=database.begin();il!=database.end();++il){
		word k ;
		string s;
		s= il->first;
		k=il->second;
		ofile<<s<<"\n";
		ofile<<k.connections.size()<<"\n";
		int t= k.connections.size();
		int j=0;
		while(t--){
			edge et;
			et = k.connections[j];
			j++;
			ofile<<et.firstWord.key<<"\n";
			ofile<<et.secondWord.key<<"\n";
			ofile<<et.weight<<"\n";
			ofile<<et.slope<<"\n";
			ofile<<et.topic<<"\n";
			ofile<<et.relation<<"\n";
		}
	}
	ofile.close();
}
#endif	/* DATABASE_H */
