//This is Dynamic Memory Allocator class 2
//will be used to simulate allocation using Dictionary based on BSTree and AVL Trees
//Defragmentor is implemented

#include "DMem.h"
class DMem2: public DMem{
    public:
    DMem2(): DMem(){}

    DMem2(int size): DMem(size){}

    DMem2(int size, int dict_type): DMem(size,dict_type){}

    
};
