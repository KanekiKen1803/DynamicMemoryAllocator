// Class for implementing Dictionary using Double Linked List
#ifndef dll
#define dll
#include "Dictionary.h"

//Dictionary using Doubly Linked List (DLL)
class List: public Dictionary{
    private:
    List *next=nullptr;
    List *prev=nullptr;

    public:
    //Parameterised Constructor
    List(int address, int size, int key): Dictionary(address,size,key){}

    //Non Parametrised Constructor

    //initialising the head pointer
    List(): Dictionary(-1,-1,-1){
        next=nullptr;
        prev=nullptr;

        //initialsing the tail pointer
        List *tail = new List(-1,-1,-1);
        this->next=tail;
        tail->prev= this;
    }

    //overriding insert function
    List *Insert(int address, int size, int key){
    
        if(this==nullptr || next==nullptr){
            return nullptr;
        }
        List* t = new List(address,size,key);
        this->next->prev = t;
        t->next = this->next;
        this->next = t;
        t->prev = this;
        return t;
    }

    //overriding the Delete function

    bool Delete(Dictionary *d){
        if(d==nullptr){
            return false;
        }
        for(List *i= this->getFirst(); i!=nullptr; i=i->getNext()){
            if((i->address == d->address) && (i->size == d->size) && (i->key==d->key)){
                i->prev->next=i->next;
                i->next->prev = i->prev;
                i=nullptr;
                return true;
            }
        }
    }

    //overrinding the Find() function
    List *Find(int k, bool exact){
        for(List *i= this->getFirst(); i!=nullptr; i=i->getNext()){
            if(exact){
                if(i->key==k){
                    return i;
                }
               
            }
            else{
                if(i->key>=k){
                    return i;
                }
            }
        }
    }

    //overriding getFirst function
    List *getFirst(){
        if(this==nullptr){
            return nullptr;
        }
        if(this->prev==nullptr){
            if(this->next->next==nullptr){
                return nullptr;
            }
            else{
                return this->next;
            }
        }
        else{
            this->prev->getFirst();
        }
        
    }

    //overriding getNext function
    List *getNext(){
        if(this->next->next==nullptr){
            return nullptr;
        }
        else{
            return this->next;
        }
    }

    //overriding the sanity() function
    bool sanity(){

        //condition for null list
        if(this==nullptr){
            return true;
        }

        //condition for empty list
        if((this->getFirst()==nullptr)){
            //getfirst() would return null if current node is head pointer
            if(this->next->address!=-1 || this->next->key!=-1 || this->next->size!=-1){
                return false;
            }
        }

        //condition to check loop in the list
        List *slow=this->getFirst();
        List *fast=slow->getNext();
        for(; slow!=nullptr;slow=slow->getNext()){
            if(slow==fast){
                return false;
            }
            if(fast==nullptr){
                break;
            }
            fast=fast->getNext();
            if(fast==nullptr){
                break;
            }
            fast=fast->getNext();
        }

        //checking head pointers
        List *check=this->getFirst();
        if(check->prev->size!=-1||check->prev->address!=-1||check->prev->key!=-1||check->prev->prev!=nullptr){
            return false;
        }

        //checking next of current node is equal to prev of next node;
        for(check=check->prev;check->getNext()!=nullptr;check=check->getNext()){
            if(check->getNext()->prev!=check || check->prev->getNext()!=check){
                return false;
            }
        }

        //checking tail pointer
        if(check->key!=-1 || check->address!=-1 ||check->size!=-1 ||check->getNext()!=nullptr ){
            return false;
        }
    return true;
    }

};
#endif
