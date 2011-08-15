/* 
 * File:   priorityqq.h
 * Author: Divij
 *
 * Created on 18 April, 2011, 9:41 PM
 */

#ifndef PRIORITYQQ_H
#define	PRIORITYQQ_H

#include "Definitions.h"

using namespace std;

class node{
public:
	string sentence;
	f_number* weight;
};

class priorityq{
public:
    vector<node> heap;
    void add(string,double,double);
    void heapify(int);
    void buildHeap();
    node top();
    void remove();
};


void priorityq::add(string sen, double newweight,double newslope)
{
    node n;
    n.sentence=sen;
	f_number* node;
	node = new f_number;
	node->a = getntof(newweight);
	node->lambda = newslope; 
    n.weight=node;

    heap.push_back(n);
    buildHeap();
    return;
}

void priorityq::heapify(int index)
{
    int flag=0;
    /* Flag=1 would mean parent is the largest
     * Flag=2 would mean 2n element is largest
     * Flag=3 would mean 2n+1 element is largest
     */
    if((index*2+1)<heap.size() && (index*2+2)<heap.size()){
	if(heap[index].weight==compare(heap[index*2+1].weight,heap[index].weight) && heap[index].weight==compare(heap[index*2+2].weight,heap[index].weight)){
	    flag=1;
	}else if(heap[index*2+1].weight==compare(heap[index*2+1].weight,heap[index].weight) && heap[index*2+1].weight==compare(heap[index*2+1].weight,heap[index*2+2].weight)){
	    flag=2;
	}else if(heap[index*2+2].weight==compare(heap[index*2+2].weight,heap[index].weight) && heap[index*2+2].weight==compare(heap[index*2+2].weight,heap[index].weight)){
	    flag=3;
	}
    }else if((index*2+1)<heap.size()){
	if(heap[index].weight==compare(heap[index*2+1].weight,heap[index].weight)){
	    flag=1;
	}else{
	    flag=2;
	}
    }else if((index*2+2)<heap.size()){
	if(heap[index*2+2].weight==compare(heap[index*2+2].weight,heap[index].weight)){
	    flag=3;
	}else{
	    flag=1;
	}
    }

    if(flag==2){
	swap(heap[index],heap[index*2+1]);
	heapify(index*2+1);
    }else if(flag==3){
	swap(heap[index],heap[index*2+2]);
	heapify(index*2+2);
    }


    return;
}
void priorityq::buildHeap()
{
    //for(int i=pow(2.0,log(heap.size()*1.0))-1;i>-1;i--){
    for(int i=heap.size()-1;i>-1;i--){
	heapify(i);
    }
}

node priorityq::top()
{
    node n=heap[0];
    return n;
}

void priorityq::remove()
{
    swap(heap[0],heap[heap.size()-1]);
    heap.erase(heap.end());
    heapify(0);
}
#endif	/* PRIORITYQQ_H */

