#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include <sstream>
#include<map>
#include "Definitions.h"
#include "word.h"
#include "edge.h"
#include "database.h"

using namespace std;

int main()
{

		word kk;
	kk.key ="m";
	edge e;
	e.weight = 2;
e.slope = 2;
//	e.weight.lambda = 2;
	e.relation= "NN";
	e.firstWord.key="ss";
	e.secondWord.key="si";
	e.topic="HCI";

	kk.connections.push_back(e);
	e.weight = 2;
e.slope = 2;
//	e.weight.lambda = 2;
	e.relation= "N";
	e.firstWord.key="s";
	e.secondWord.key="esi";
	e.topic="HCI2";
	kk.connections.push_back(e);
	
	database["fw"]=kk;



	kk.key ="m1";
	e.weight = 2;
e.slope = 2;
	//e.weight.lambda = 2;
	e.relation= "VBZ";
	e.firstWord.key="wss";
	e.secondWord.key="wwsi";
	e.topic="SCO1";
	kk.connections.clear();
	kk.connections.push_back(e);

	e.weight = 2;
e.slope = 2;
	//e.weight.lambda = 2;
	e.relation= "SN";
	e.firstWord.key="sll";
	e.secondWord.key="ei";
	e.topic="SCO2";

	kk.connections.push_back(e);
	e.weight = 2;
e.slope = 2;
	//e.weight.lambda = 2;
	e.relation= "BBN";
	e.firstWord.key="lop";
	e.secondWord.key="xx";
	e.topic="SCO3";

	kk.connections.push_back(e);


	database ["sw"]=kk;
	writedb();
/*
	loaddb();
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
	}*/
	return 0;
}
