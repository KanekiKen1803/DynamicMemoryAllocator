
#ifndef mem
#define mem
#include<stdint.h>
#include"BSTree.h"
#include"DLL.h"
#include"AVLTree.h"

class DynamicMem{
    public:

    const int M=1000000;    //Total number of memory addresses
    int8_t *Memory;        //Pointer to the the 8bit Memory array

    Dictionary *freeBlk=nullptr;     //Free blocks dictionary     
    Dictionary *allocBlk=nullptr;    //Allocated dictionary
    int type;               //Type of dictionary: 1-DLL, 2-BSTree, 3-AVLTree

    DynamicMem(){           //Default Constructor
        DynamicMem(M,1);
    }
    DynamicMem(int size){   //Default Constructor in case size is given
        DynamicMem(size,1);
    }
    DynamicMem(int size, int dict_type){ //fully parametrised constructor

        Memory = new int8_t[size]; //Dynamic allocation of Memory array of 8bit integer data type
        type = dict_type;

        if(type == 1){
            //Initialising the Head and Tail Pointers
            freeBlk = new List();
            allocBlk = new List();

            //Initially free list has only one block with all memory
            freeBlk->Insert(0,size,size);
        }
        else if (type == 2){
            //Initialising the Head and Tail Pointers
            freeBlk = new BSTree();
            allocBlk = new BSTree();

            // Initially free list has only one block with all the memory
            freeBlk->Insert(0, size, size);
            
        }
        else if(type ==3){
            freeBlk = new AVLTree();
            allocBlk = new AVLTree();

            // Initially free list has only one block with all the memory
            freeBlk->Insert(0, size, size);
            
        } 
    }

    //These functions will be defined in derived classes

    virtual int Allocate(int blockSize){
        return -1;
    };

    virtual int Free(int startAddr){
        return -1;
    }
    void Defragment(){
        return;
    }

};
#endif