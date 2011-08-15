#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include "Definitions.h"
#include "word.h"
#include "edge.h"
//#include "f_number.h"

using namespace std;

int main()
{
	ofstream ofile("database.bin");
	map<string,word> database;
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
			//ofile<<et.weight.lambda<<"\n";
			ofile<<et.topic<<"\n";
			ofile<<et.relation<<"\n";
		}
		//ofile<<"\n";
	}
	//now retrieving
	ofile.close();
	return 0;
}
