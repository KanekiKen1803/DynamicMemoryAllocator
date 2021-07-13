//Peforms dynamic memory allocation
//Does not include Defragmentor


#include"DynamicMem.h"
class DMem: public DynamicMem{
    public:

    DMem(): DynamicMem(){}
    DMem(int size): DynamicMem(size){}
    DMem(int size, int dict_type):DynamicMem(size, dict_type){}

    int Allocate(int blockSize){
        
    
        Dictionary *t= freeBlk->Find(blockSize,false);
        /*if((type == 2 || type == 3) && t<(void*)0x1000 ){
            Defragment();
        t= freeBlk->Find(blockSize,false);
        }*/
            if(t==nullptr|| blockSize<=0){
                return -1;
            }
        
        freeBlk->Delete(t);
        if(t->size>blockSize){
            freeBlk->Insert(t->address+blockSize, t->size - blockSize, t->size-blockSize);
        }
        allocBlk->Insert(t->address,blockSize,t->address);
        return t->address;
    
    }
    int Free(int startAddr){
       
        Dictionary *t= allocBlk->Find(startAddr, true);
        if(t==nullptr){
            return -1;
        }
        allocBlk->Delete(t);
        freeBlk->Insert(t->address,t->size,t->size);
        return 0;
    }
    void Defragment(){
        if(this->type == 2){
            BSTree *adlist = new BSTree();
            if(this->freeBlk->getFirst() == nullptr){
                return;
            }
            for(Dictionary *t = this->freeBlk->getFirst(); t!=nullptr; t= t->getNext()){
                adlist->Insert(t->address,t->size,t->address);
        
            }
            Dictionary *prev = adlist->getFirst();

            for(Dictionary *t = adlist->getFirst()->getNext(); t!= nullptr; t=t->getNext()){
                if(prev->address + prev->size == prev->address){
                    freeBlk->Insert(prev->address, prev->size + t->size, prev->size + t->size);
                    BSTree *p= new BSTree(prev->address, prev->size, prev->size);
                    freeBlk->Delete(p);
                    BSTree *q = new BSTree(t->address,t->size,t->size);
                    freeBlk->Delete(q);

                    t->address = prev->address;
                    t->key = prev->address;
                    t->size = prev->size + t->size;
                    prev =t;
                }
                else{
                    prev =t;
                }
            }

            adlist = nullptr;
            return;
        }

        else if(this->type == 3){
            AVLTree *adlist = new AVLTree();
            if(this->freeBlk->getFirst()==nullptr){
                return;
            }
            for(Dictionary*d = this->freeBlk->getFirst();d!= nullptr ;d= d->getNext()){
                adlist->Insert(d->address,d->size,d->address);
            }
            Dictionary *prev = adlist->getFirst();
            for(Dictionary *t = adlist->getFirst()->getNext(); t!=nullptr; t=t->getNext()){
            if(t->address +prev->size == t->address){   
                freeBlk->Insert(prev->address,prev->size + t->size, prev->size + t->size);
                AVLTree *p = new AVLTree(prev->address, prev->size, prev->size);
                freeBlk->Delete(p);
                AVLTree *q= new AVLTree(t->address, t->size, t->size);
                freeBlk->Delete(q);

                t->address = prev->address;
                t->key = prev->address;
                t->size = prev->size +t->size;
                prev =t;
            }
            else{
                prev =t;
            }
        }
        adlist =nullptr;
        return;
        }
    }

};
