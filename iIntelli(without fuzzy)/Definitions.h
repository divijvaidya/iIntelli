/* 
 * File:   Definitions.h
 * Author: Divij
 *
 * Created on 27 March, 2011, 12:35 PM
 */

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <fstream>
#include <bits/stl_vector.h>

using namespace std;

class word;
class edge;


#define ST_WEIGHT 8
#define NN_WEIGHT 8
#define SNN_WEIGHT 6
#define SA_WEIGHT 3
#define KEY_WEIGHT 10
#define HYN_WEIGHT 7
#define SYN_WEIGHT 9
#define DERI_WEIGHT 8
#define SLOPE 0.7

//#include "fuzzy.h"
#include "priorityq.h"
#include "word.h"
#include "edge.h"

//===============Global Declarations=========================//
map<string,word> database;
vector <string> hype; //contains hyponyms
vector <string> deri;//contains derived words
vector <string> syns;// contains synonyms

//===========================================================//

#include "wordnet.h"


#endif	/* DEFINITIONS_H */

