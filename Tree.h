//Defining the class Trees to be implemented in BSTrees and AVL Trees
//Uses Dictionary as the storage data structure
#ifndef tree
#define tree


#include"Dictionary.h"
class Tree: public Dictionary{
    private:
    Tree *left=nullptr;           //child nodes
    Tree *right=nullptr;          //child nodes
    Tree *parent=nullptr;         //parent node

    public:
    Tree(): Dictionary(-1,-1,-1){
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

    Tree(int address , int size, int key):Dictionary(address, size, key){
        this->left=nullptr;
        this->right = nullptr;
        this->parent=nullptr;
    }
    Tree *Insert(int address,int size, int key ){
        return nullptr;
    };

    bool Delete(Dictionary *d){
        return false;
    }

    Tree *Find(int key, bool exact){
        return nullptr;
    }

    Tree *getFirst(){
        return nullptr;
    }

    Tree *getNext(){
        return nullptr;
    }

    bool sanity(){
        return false;
    }

};
#endif