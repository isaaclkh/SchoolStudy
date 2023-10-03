//On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: 임건호 Section: 01 Student Number: 21800612
//  stack.cpp
//  Created by idebtor@gmail.com on December 12, 2018.
/*
* Description:	This program implements a stack using singly-linked list
* without a head structure and without sentinel nodes. It simply links
* node to node. The caller is responsible for maintaining the the first
* node (head) of the list. Most functions need the first node to work
* with the list and returns the first node of the list since it may be
* changed inside of the functions.
*/
#include <iomanip>
#include "stack.h"

// removes all the nodes from the list (which are destroyed),
// and leaving the container nullptr or its size to 0.
pNode clear(pNode p) {
	if (empty(p)) return nullptr;
	DPRINT(cout << "clear: ";);

    //cout << "your code here\n";
    while(p != nullptr){
        pNode x = p;
        p = p->next;
        delete x;
    }
	cout << "\n\tAll things are cleared.\n";
	return nullptr;
}

// returns the number of nodes in the list.
int size(pNode p) {
	if (empty(p)) return 0;
	int count = 0;
    
    pNode pp = p;
	//cout << "your code here\n";
    while (!empty(pp)) {
        count++;
        pp = pp -> next;
    }
	return count;
}

// returns true if the list is empty or no nodes.
// To remove all the nodes of a list, see clear().
bool empty(pNode p) {
	return p == nullptr;
}

// inserts a new node with val at the beginning of the list.
// This effectively increases the list size by N
pNode push(pNode hp, int val, int N) {
	DPRINT(cout << ">push val=" << val << " N="<< N << endl;);

	//cout << "your code here\n";
    if(N==1){
        if(empty(hp)){
            pNode x = new Node{val, nullptr};
            return x;
        }
        pNode node = new Node{val, hp};
        return node;
    }
    
    else{
        for(int i=0; i<N; i++){

            if(empty(hp)){
                pNode x = new Node {i, nullptr};
                hp = x;
            }
            
            else{
                pNode x = new Node{i, hp};
                hp = x;
            }
        }
        return hp;
    }

	DPRINT(cout << "<push size=" << size(hp) << endl;);
	return hp;
}

// removes the first node in the list and returns the new first node.
// This destroys the removed node, effectively reduces its size by N.
pNode pop(pNode hp, int N) {
	DPRINT(cout << ">pop size=" << size(hp) << " N="<< N << endl;);
	
    if (empty(hp)) return nullptr;

	//cout << "your code here\n";
    if(N==1){
        pNode x = hp;
        hp = hp->next;
        delete x;
    }
    
    else{
        for(int i=0; i<N; i++){
            if (empty(hp)) return nullptr;
            pNode x = hp;
            hp = hp -> next;
            delete x;
        }
    }

	DPRINT(cout << "<pop size=" << size(hp) << endl;);
	return hp;
}

// returns the first node in the list. This does not destroy the node.
pNode top(pNode hp) {
	DPRINT(cout << ">top size=" << size(hp) << endl;);
	if (empty(hp)) return nullptr;

    //cout << "your code here\n";
	return hp;
}

// shows the values of all the nodes in the list if all is true or
// the list size is less than or equal to pmax * 2. If there are more than
// (pmax * 2) nodes, then it shows only pmax number of nodes from
// the beginning and the end in the list.
void show(pNode hp, bool all, int pmax) {
	DPRINT(cout << "show(" << size(hp) << ")\n";);
    
    int count=0;
    pNode temphp = hp;
    int sizing = size(hp)-20;
	
    if (empty(hp)) {
		cout << "\n\tThe list is empty.\n";
		return;
	}
	//cout << "your code here\n";
    
    if(all && size(hp)>pmax*2){
        for(int i=0; i<pmax; i++){
            cout << temphp->item;
            cout << "->";
            temphp = temphp->next;
        }
        
        cout<<endl;
        temphp = pop(temphp, sizing);
        cout<< "...lesft out..."<<endl;
        
        for(int j=0; j<pmax; j++){
            cout << temphp->item;
            if(j!=pmax-1)cout << "->";
            temphp = temphp->next;
        }
    }
    
    else{
        while (temphp!= nullptr) {
            count++;
            cout << temphp->item;
            temphp = temphp->next;
            if(count%10==0) cout<<endl;
            if(count+1 != size(hp)) cout << "->";
        }
    }
}
