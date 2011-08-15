/* 
 * File:   word.h
 * Author: Divij
 *
 * Created on 18 April, 2011, 9:44 PM
 */

#ifndef WORD_H
#define	WORD_H
#include "Definitions.h"
#ifdef	__cplusplus
extern "C" {
#endif
class word{
public:
    string key;
    vector<edge> connections;

    word(){
	key="";
    }
};



#ifdef	__cplusplus
}
#endif

#endif	/* WORD_H */

