//Implementing Binary Search Tree using parent class Tree
#ifndef bs
#define bs

#include"Tree.h"
#include<iostream>
using namespace std;
class BSTree: public Tree{
    private:
    BSTree *left =nullptr;        //left child
    BSTree *right=nullptr;       //right child
    BSTree *parent=nullptr;      //parent node

    BSTree *getRoot(){
        if(this->parent == nullptr){
            return this->right;
        }
        else{
            return this->parent->getRoot();
        }
    }
    
    void DeleteNode(){
        if(this->left == nullptr && this->right == nullptr){
            if(this->parent->left == this){
                this->parent->left=nullptr;
            }
            if(this->parent->right == this){
                this->parent->right=nullptr;
            }
            this->left =nullptr;
            this->right =nullptr;
            return;
        }
        if(this->left==nullptr){
            this->right->parent=this->parent;
            if(this->parent->left== this){
                this->parent->left= this->right;
            }
            if(this->parent->right == this){
                this->parent->right = this->right;
            }
            this->right = nullptr;
            return;
        }
        else if(this->right == nullptr){
            this->left->parent = this->parent;
            if(this->parent->left == this){
                this->parent->left = this->left;
            }
            if(this->parent->right ==this){ 
                this->parent->right = this->left;
            }
            this->left = nullptr;
            return;
        }

        BSTree *t = this->right;
        while(t!=nullptr && t->left!=nullptr){
            t= t->left;
        }
        BSTree *q = new BSTree(t->address, t->size, t->key);
        q->left = this->left;
        q->right = this->right;
        q->parent = this->parent;
        q->left->parent = q;
        q->right->parent = q;
        if(q->parent->left == this){
            q->parent->left = q;
        }
        else{
            q->parent->right = q;
        }
        t->DeleteNode();
    }
    bool check(BSTree *t, BSTree* visited){
        if(t == nullptr){
            return true;
        }
        if(visited->Find(t->address, true) == nullptr){
            visited->Insert(t->address,t->size, t->address);
                return (check(t->left, visited) && check(t->right, visited));

        }
        else{
            return false;
        }
        
    }

    public:

    BSTree(): Tree(){}

    BSTree(int address, int size, int key): Tree(address,size,key) {}

    BSTree *Insert(int address,int size, int key ){
        BSTree *t= this->getRoot();

        if(t==nullptr){
            BSTree *node = new BSTree(address,size,key);
            node->parent =this;
            this->right= node;
            return node;
        }
        int dir; //will give directions
        while(t!=nullptr && (t->left !=nullptr || t->right != nullptr)){
            if(t->key<key){
                dir = 1;
            }
            else if(t->key>key){
                dir = 0;
            }
            else{
                if(t->address < address){
                    dir = 1;
                }
                else{
                    dir = 0;
                }
            }

            if(dir == 0){
                if(t->left != nullptr){
                    t = t->left;
                }
                else{
                    break;
                }
            }
            else{
                if(t->right != nullptr){
                    t=t->right;
                }
                else{
                    break;
                }
            }
        }
        BSTree *node = new BSTree(address, size, key);
        node->parent = t;
        if(t->key>key){
            t->left = node;
        }
        else if(t->key<key){
            t->right = node;
        }
        else{
            if(t->address < address){
                t->right = node;
            }
            else{
                t->left = node;
            }
        }
        return node;
    }

    bool Delete(Dictionary *d){
        BSTree *t = this->getRoot();
        while(t!=nullptr){
            if(t->key < d->key){
                t = t->right;
            }
            else if(t->key > d->key){
                t= t->left;
            }
            else{
                if(t->address < d->address){
                    t = t->right;
                }
                else if(t->address > d->address){
                    t=t->left;
                }
                else{
                    if(t->size == d->size){
                        t->DeleteNode();
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }

        }
        return false;
    }

    BSTree *Find(int key, bool exact){
        BSTree *t  = this->getRoot();
        BSTree *enode = nullptr;
        BSTree *node = nullptr;
        while(t!=nullptr){
            if(t->key<key){
                t=t->right;
            }
            else{
                if(t->key == key){
                    enode =t;
                }
                else{
                    node =t;
                }
                t=t->left;
            }
        }
        if(!exact){
            if(enode == nullptr){
                return node;
            }
        }
        if(enode == nullptr){
            return nullptr;
        }
        return enode;
    }

    BSTree *getFirst(){
      BSTree *t = this->getRoot();
      while(t!=nullptr && t->left!= nullptr){
          t=t->left;
      }
      return t;
    }

    BSTree *getNext(){
      if(this->parent == nullptr){
          return nullptr;
      }
      if(this->right!= nullptr){
          BSTree *t = this->right;
          while(t->left!= nullptr){
              t= t->left;
          }
          return t;
      }
      else{
          BSTree *t = this;
          while(t!=nullptr && t->parent != nullptr && t->parent->left!= t){
              t=t->parent;
          }
          if(t->parent == nullptr){
              return nullptr;
          }
          else{
              return t->parent;
          }
      }
    }

    bool sanity(){
       BSTree *t= this;
       if(t->parent = nullptr){
           if(!(t->left==nullptr && (t->address == -1 && t->size == -1 && t->key == -1))){
               return false;
           }
           else{
               if(t->right == nullptr){
                   return true;
               }
           }
       }

        //checking the cycle
        BSTree *fast = this->parent;
        BSTree *slow = this;
        while(fast!=nullptr && fast->parent!=nullptr && slow->parent!=nullptr){
            if(fast == slow){
                return false;
            }
            slow = slow->parent;
            fast = fast->parent;
            if(fast!=nullptr && fast->parent!=nullptr){
                fast= fast->parent;
            }
        }
        t=fast;
        if(t==nullptr){
            t=slow;
        }

        //checking the sanity of tail node
        if(t->parent == nullptr){
            if(!(t->address == -1 && t->size == -1 && t->key == -1)){
                //cout<<"1"<<endl;
                return false;
            }
            if(t->left!=nullptr){
                return false;
            }
        }

        BSTree *vis = new BSTree();

        if(!check(t->right, vis)){
            return false;
        }

        for(t= this->getFirst(); t->getNext(); t=t->getNext()){
            if(t->key > t->getNext()->key){
                //cout<<"2"<<endl;
                return false;

            }
            else if(t->key == t->getNext()->key){
                if(t->address > t->getNext()->address){
                    //cout<<"3"<<endl;
                    return false;
                }
            }
            if(t->left!=nullptr && t->left->parent != t){
                return false;
            }
            if(t->right!= nullptr && t->right->parent!= t){
                return false;
            }

            if(t->left!= nullptr && t->right !=nullptr){
                if(t->right ==t->left || t->left == t->parent || t->right == t->parent){
                    return false;
                }
            }
        }
        return true;
    }


};
#endif
