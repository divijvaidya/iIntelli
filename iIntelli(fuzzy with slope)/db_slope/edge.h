/* 
 * File:   edge.h
 * Author: Divij
 *
 * Created on 18 April, 2011, 9:48 PM
 */

#ifndef EDGE_H
#define	EDGE_H
#include "Definitions.h"
class edge{
public:

	double weight;
	double slope;

    /*Weight given to the edges as per relations
     * This is defined in macros
     */
    string relation;
    /*Relations are defined as:
     * ST: Same type as determined by pos tagger
     * NN: Noun-Noun relationship as deteremined by stanford parser
     * SNN: Noun in the same sentence as the word
     * SA: Adjective in the same sentence as the word
     * HYN: Hyponym as obtained from wordnet
     * SYN: Synonym as obtained from wordnet
     * DERI: Derivative as obtained from wordnet
     */
    string topic;

    word firstWord;
    word secondWord;
};

#endif	/* EDGE_H */

