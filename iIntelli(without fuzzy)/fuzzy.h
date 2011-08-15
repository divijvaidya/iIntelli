/* 
 * File:   fuzzy.h
 * Author: Divij
 *
 * Created on April 26, 2011, 3:22 AM
 */

#ifndef FUZZY_H
#define	FUZZY_H

#include "Definitions.h"
#define K 2

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


#endif	/* FUZZY_H */

