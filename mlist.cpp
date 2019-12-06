/******************************************************************************
Name: Alexander Hein
Email: heina@usc.edu
Description: The implementation file for the MList class.
*******************************************************************************/

#include <iostream>
#include "mlist.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//NOTE: There can only be at most 2 loops in this file
//------------------------------------------------------------------------------

//Constructor, construct an empty doubly linked list.
MList::MList(){
    ntop = NULL;
    nbottom = NULL;
}

//Destructor, properly clears and deallocates everything of current list.
//simply call the clear function if you have already implemented that.
MList::~MList(){
   clear();
}

//Note: RECURSION --- This function should be implemented using recursion.
//this function properly clears and deallocates everything of current list.
//there should be no loop in this function
void MList::clear(){
    //base cases
    if(isEmpty())
        return;
    if(ntop->nodeData->childList!=NULL){
        ntop->nodeData->childList->clear();
    }
    if(ntop->next==NULL){
        ntop=NULL;
        nbottom=NULL;
        return;
    }
    
    //delete top node
    Node * temp = ntop;
    ntop = temp->next;
    //delete temp->nodeData;
    delete temp;
    
    //delete next node
    clear();
}

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){
    if(ntop==NULL){
        return true;
    }
    else{
        return false;
    }
}

/*
	Add or insert a new node with d_item as its data at the top of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_top(Data* d_item){
    //create new node 
    Node* newNode = new Node;
    newNode->nodeData = d_item;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    //if empty set node as top and bottom
    if(isEmpty()){
        ntop = newNode;
        nbottom = newNode;
        return;
    }
    
    //insert newNode before ntop
    ntop->prev = newNode;
    newNode->next = ntop;
    ntop = newNode;   
}

/*
	Add or insert a new node with d_item as its data at the bottom of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_bottom(Data* d_item){
    //create new node and initialize to null
    Node* newNode = new Node;
    newNode->nodeData = d_item;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    //if empty set node as top and bottom
    if(isEmpty()){
        nbottom = newNode;
        ntop = newNode;
        return;
    }
    
    //insert newNode after nbottom
    nbottom->next = newNode;
    newNode->prev = nbottom;
    nbottom = newNode;  
}

/*
	Delete or remove the top node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_top(){
    if(isEmpty()){
        return;
    }
    Node* temp = ntop;
    ntop = temp->next;
    if(ntop==NULL){
        nbottom = NULL;
    }
    else{
        ntop->prev = NULL;
    }
    delete temp; 
}

/*
	Delete or remove the bottom node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_bottom(){
    if(isEmpty()){
        return;
    }
    Node* temp = new Node;
    temp = nbottom; 
    nbottom = temp->prev;
    if(nbottom==NULL){
        ntop = NULL;
    }
    else{
        nbottom->next = NULL;
    }
    delete temp;  
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Search a node in the list that has data with the same name as the parameter.
	If one is found, return the pointer to the node.
	If one is not found, return NULL.
*/
Node* MList::search(Node* start, string name){
    //base cases
    if(isEmpty()) 
        return NULL;
    else if(start==NULL)
        return NULL;
    else if(start->nodeData->name == name)
        return start; //if name is found, return start   
    start = search(start->next, name); //search will echo back the return value
    return start;
}


//Swapping node a with node b.
void MList::swapNode(Node* a, Node*b){
    if(ntop==nbottom){
        return;
    }
    
    //set temporary node for a
    Node *temp = new Node;
    
    temp->nodeData = a->nodeData;
    temp->next = a->next;
    temp->prev = a->prev;
    
    //if b is right after a
    if (a->next==b){
        //check if b is last node
        if(b->next) 
            b->next->prev = a;
        else
            nbottom = a;
        //check if a is first node
        if(a->prev) 
            a->prev->next = b;
        else
            ntop = b;
        
        //swap next and previous
        a->next = b->next;
        b->next = a;
        b->prev = a->prev;
        a->prev = b;
    }
    //if a is right after b
    else if (b->next==a){
        //check if a is last node
        if(a->next) 
            a->next->prev = b;
        else
            nbottom = b;
        //check if b is first node
        if(b->prev) 
            b->prev->next = a;
        else
            ntop = a;
        
        //swap next and previous
        b->next = a->next;
        a->next = b;
        a->prev = b->prev;
        b->prev = a;
    }
    //if b and a are at least one node apart
    else{
        //check if a is last node
        if(a->next)
            a->next->prev = b;
        else
            nbottom = b;
        //check if a is first node
        if(a->prev)
            a->prev->next = b;
        else
            ntop = b;
        //check if b is last node
        if(b->next)
            b->next->prev = a;
        else
            nbottom = a;
        //check if b is first node
        if(b->prev)
            b->prev->next = a;
        else
            ntop = a;
        
        //swap next and previous
        a->next = b->next;
        b->next = temp->next;
        a->prev = b->prev;
        b->prev = temp->prev;
    }
    
    delete temp;
}

/*
	This function PERMANENTLY deletes a node from the list given a pointer to that node.
	You can assume that the node exists in the list - no need to search for the node.
*/
void MList::deleteNode(Node* a){
    if(nbottom==a){
        pop_bottom();
        return;
    }
    else if(ntop==a){
        pop_top();
        return;
    }
    
    a->prev->next = a->next;
    a->next->prev = a->prev;
    
    delete a;
}

/*
	Unlike the delete function above, this function does NOT permanently delete the node.
	What you need to do at the last step is to set the node's prev and next pointers to NULL.
	Again, you can assume that the node exists in the list - no need to search for the node.
	Note: this function will be useful
        when we want to insert the given node later at another position after you remove it from the list.
*/
void MList::removeNode(Node* a){
    //if a is the top node or the only node in the list
    if(ntop==a){
        ntop = a->next;
        if(ntop==NULL){
            nbottom = NULL;
        }
        else{
            ntop->prev = NULL;
        }    
    }
    //if a is the bottom node
    else if(nbottom==a){
        nbottom = a->prev;
        nbottom->next = NULL;
    }
    //if a is somewhere in the middle
    else{
        a->prev->next = a->next;
        a->next->prev = a->prev;
    }
    a->next = NULL;
    a->prev = NULL;
}

/*
	Insert node a after node b.
	Note: b can be NULL, Q: what does that mean?
    otherwise, you can assume that b exists in the list.
*/
void MList::insertAfter(Node *a, Node* b){
    //only case when b is null is when inserting a at the top of the list
    if(b==NULL){
        if(isEmpty()){
            //safety measure if passed a node with prev and next values
            a->next = NULL;
            a->prev = NULL;
            
            //a is the only node in the set
            ntop = a;
            nbottom = a;
            return;
        }
        a->next = ntop;
        a->prev = NULL;
        a->next->prev = a;
        ntop = a;
    }
    //b is the bottom of the list
    else if (b->next==NULL){
        a->next = NULL;
        a->prev = b;
        a->prev->next=a;
        nbottom = a;
    }
    //b is somewhere in the middle
    else{
        a->next=b->next;
        b->next = a; 
        a->prev = b;
        a->next->prev = a;
    }
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement a SELECTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). if mode = true, sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number if mode = true
        3). if mode = false, sort by size in ascending order (low->high)
	You can search any online resources available to you (i.e. search 'selection sort')
	to understand the basic idea behind the selection sort algorithm.
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private
            see sortByNameSelection and sortBySizeSelection for the calls to this function
*/
void MList::sortSelection(Node* start, bool mode){
    //base cases
    if(isEmpty()) return;
    else if(start==NULL) return;
    
    Node * min = start;
    Node * curr = start;
    Node * next = start->next;
    
    //find min
    while(curr!=NULL){
        if(mode){
            if(curr->nodeData->name < min->nodeData->name){
                min = curr;
            }
        }
        else{
            if(curr->nodeData->size < min->nodeData->size){
                min = curr;
            }
        }
        curr = curr->next;
    }
    
    //swap min with start
    swapNode(start, min);
    
    //perform selection sort starting with the node that was initially after start
    sortSelection(next, mode);
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement an INSERTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). we are trying to sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number.
	You can search any online resources available to you (i.e. search 'insertion sort')
	to understand the basic idea behind the insertion sort algorithm.
	The gif from the wikipedia page of this algorithm is the easiest to understand in my opinion
	Link: https://en.wikipedia.org/wiki/Insertion_sort
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private, see sortByNameInsertion for the call to this function
*/
void MList::sortInsertion(Node* start){
    //base cases
    if(isEmpty()) return;
    else if(start == NULL) return;
    
    Node * previous = start->prev;
    Node * next = start->next;
    
    //loop until reaching the front end of the list
    while(previous!=NULL){
        if(start->nodeData->name < previous->nodeData->name){
            swapNode(previous, start);
            previous = start->prev;
        }
        else{
            break;
        }
    }
     
    //perform insertion sort starting at the next node in the list
    sortInsertion(next); 
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the top.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printBtT function for the call to this function.
    This function is private
*/
void MList::traverseToTop(Node* n, string delim){
    if(isEmpty())
        return;
    else if(n==NULL)
        return;
    
    if(n->nodeData->isFolder)
        cout << n->nodeData->name << delim;
    else
        cout << n->nodeData->name<< "(" << n->nodeData->size << ")" << delim;

    traverseToTop(n->prev, delim);
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the bottom.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printTtB function for the call to this function.
    This function is private
*/
void MList::traverseToBottom(Node* n,string delim){
    if(isEmpty())
        return;
    else if(n==NULL)
        return;
    
    if(n->nodeData->isFolder)
        cout << n->nodeData->name << delim;
    else
        cout << n->nodeData->name<< "(" << n->nodeData->size << ")" << delim;

    traverseToBottom(n->next, delim);   
}

//------------------------------------------------------------------------------
//FUNCTIONS BELOW ARE COMPLETE, PLEASE DON'T CHANGE ANYTHING HERE
//------------------------------------------------------------------------------

//getting the pointer to the top node.
Node* MList::top(){
	return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
	return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
	//create a temp pointer to hold bottom
	Node* tmp = nbottom;
	traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
	Node* tmp = ntop;
	traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
    bool mode = true;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
    bool mode = false;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
    Node *tmp = ntop;
    sortInsertion(tmp);
}