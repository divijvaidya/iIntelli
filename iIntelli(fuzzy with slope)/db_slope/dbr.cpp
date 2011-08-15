#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include <sstream>
#include<map>
#include "Definitions.h"
#include "word.h"
#include "edge.h"

using namespace std;

int main()
{
	//retrieving data from file
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
	
	map<string,word> :: iterator il;
	for(il=database.begin();il!=database.end();++il){
		word k ;
		string s;
		s= il->first;
		k=il->second;
		cout<<s<<"\n";
		cout<<k.connections.size()<<"\n";
		int t= k.connections.size();
		int j=0;
		while(t--){
			edge et;
			et = k.connections[j];
			j++;
			cout<<et.firstWord.key<<"\n";
			cout<<et.secondWord.key<<"\n";
			cout<<et.weight<<"\n";
			cout<<et.slope<<"\n";
			cout<<et.topic<<"\n";
			cout<<et.relation<<"\n";
		}
	}
	ifile.close();
	
	return 0;
}
