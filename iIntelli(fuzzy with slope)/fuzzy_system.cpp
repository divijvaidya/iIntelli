/* All the fuzzy numbers defined in this program follow the sigmoidal member function.
 * Parameters which define such fuzzy numbers are " a " -> mean . ( Point where the membership value becomes 1/2 )
 * " lambda " would determine the slope of the function....
 *
 * To do:
 * 1) Perform addition of fuzzy numbers with different value of lamda....
 * 2) Perform comparison between fuzzy numbers...
 *
 * A partial solution to the first problem is implemented. But this requires the slopes of the sigmoids to be added in the form... lambda = lambda*k^i
 *
 */

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
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
#include <string>
#define K 2
using namespace std;

struct f_number{
	double a;
	double lambda;
};

double calculate_alpha(struct f_number* node,double x){		// Compute the membership value for any x value
	double result = 0.0;
	double denom = 1.0;
	double term = x - node->a;
	term = term*node->lambda;
	term = -term;
	denom = denom + exp(term);
	result = double(1/denom);
	return result;
}

struct f_number* fuzzy_addition(struct f_number* node,struct f_number* node1){		//Perform addition.. assumption that lambda is same for all
	struct f_number* result;
	result = new f_number;
	result->a = node->a + node1->a;
	result->lambda = node->lambda/2;
	return result;
}

struct f_number* diff_fuzzy_addition(struct f_number* node,struct f_number* node1){	//Perform addition... different lambda but in a G.P.
	struct f_number* result;
	result = new f_number;
	double a = double(1/node->lambda) + double(1/node1->lambda);
	result->lambda = double(1/a);
	double An = node->a + node1->a;
	double Gn = K + 2*K*K;
	Gn = double(Gn/(1 + K + K*K));
	Gn = 2 - Gn;
	Gn = Gn*log(K);
	double term = 1.0;
	term = term + double(1/K) + double(1/(K*K));
	Gn = Gn + term;
	Gn = Gn/result->lambda;
	double Bn = An - Gn;
	result->a = Bn;
	return result;
}

struct f_number* compare(struct f_number* node,struct f_number* node1){		//Performs comparison.... returns the larger fuzzy number
	double x = 0.0;
	x =((node->lambda*node->a) - (node1->lambda*node1->a));
	if(x == 0){
		return node;
	}
	if(node->lambda != node1->lambda){
		x = x/(node->lambda-node1->lambda);
	}else{
		if(node->a > node1->a ){
			return node;
		}else{
			return node1;
		}
	}
	double alpha = 0.0;
	alpha = calculate_alpha(node,x);
//	cout << alpha << "	" << x << endl;
	if(alpha <=0.5){
		double alpha1 = 0.0;
		double alpha2 = 0.0;
		x = x+0.1;
		alpha1 = calculate_alpha(node,x);
		alpha2 = calculate_alpha(node1,x);
	//	cout << alpha1 << "	" << alpha2 << endl;
		if(alpha1 > alpha2){
			return node;
		}else{
			return node1;
		}
	}else if(alpha >0.5){
		double alpha1 = 0.0;
		double alpha2 = 0.0;
		x = x - 0.1;
		alpha1 = calculate_alpha(node,x);
		alpha2 = calculate_alpha(node1,x);
		if(alpha1> alpha2){
			return node;
		}else{
			return node1;
		}
	}
}

int main()
{
	f_number* node;
	node = new f_number;
	node->a = 4.0;
	node->lambda = 0.7;
	double x = 2.0;
//	cout <<	calculate_alpha(node,x) << endl;
	f_number* node1;
	node1 = new f_number;
	node1->a = 8.0;
	node1->lambda = 0.7;
	struct f_number* add;
	add = new f_number;
	add = fuzzy_addition(node,node1);
//	cout << add->a << "	" << add->lambda << endl;
	struct f_number* new_add;
	new_add = new f_number;
	new_add = diff_fuzzy_addition(node,add);
//	cout << new_add->a << "	" << new_add->lambda << endl;
	struct f_number* comp;
	comp = new f_number;
	comp = compare(new_add,node1);
//	cout << comp->a << "	" << comp->lambda << endl;
	return 0;
}
