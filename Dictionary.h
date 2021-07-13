// Defining the default class Dictionary
#ifndef dict
#define dict

class Dictionary{
    public:
    int key=0;
    int address=0;
    int size=0;

     Dictionary(){
        key=0;
        address=0;
        size=0;
    }

    Dictionary(int address, int size, int key){
        this->key = key;
        this->address = address;
        this->size = size;
    }


// These functions will be defined in derived classes in accordance to the method deployed 
    virtual Dictionary *Insert(int address, int size, int key)=0;
    virtual bool Delete(Dictionary *d)=0;
    virtual Dictionary *Find(int k, bool exact)=0;
    virtual Dictionary *getFirst()=0;
    virtual Dictionary *getNext()=0;
    virtual bool sanity()=0;

};
#endif