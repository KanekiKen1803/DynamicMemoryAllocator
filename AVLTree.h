// Class for AVL Trees
//Few functions would be inherited from BSTree
#ifndef av
#define av
#include"BSTree.h"


class AVLTree: public BSTree{
    private:
    AVLTree* left =nullptr;
    AVLTree *right = nullptr;   //These are the children nodes
    AVLTree * parent = nullptr;
    int height;

    AVLTree *getRoot(){
        if(this->parent == nullptr){
            return this->right;
        }
        else{
            return this->parent->getRoot();
        }
    }

    bool checkh(){
        int lheight = -1;
        int rheight = -1;
        if(this->left != nullptr){
            lheight = this->left->height;
        }
        if(this->right != nullptr){
            rheight = this->right->height;
        }
        if(rheight > lheight){
            if(rheight > lheight + 1){
                return false;
               
            }
             this->height = rheight+1;
             return true;
        }
        else{
            if(lheight > rheight + 1){
                return false;
            }
            this->height = lheight +1;
            return true;
        }

    }

    AVLTree *balance(AVLTree *wrong, AVLTree *child, AVLTree *gchild){
        AVLTree *nroot;

        
        if(child == wrong->left){

            //ll rotation
            if(gchild == child->left){
                child->parent = wrong ->parent;
                if(wrong->parent->left == wrong){
                    wrong->parent->left = child;
                }
                else{
                    wrong->parent->right = child;
                }
                wrong->left = child->right;
                if(wrong->left != nullptr){
                    wrong->left->parent = wrong;
                }
                child->right =wrong;
                wrong->parent = child;
                nroot = child;

            }

            //lr rotation
            else{
                gchild->parent = wrong->parent;
                if(wrong->parent->left == wrong){
                    wrong->parent->left = gchild;
                }
                else{
                    wrong->parent->right = gchild;
                }

                wrong->left = gchild->right;
                if(wrong->left != nullptr){
                    wrong->left->parent = wrong;
                }
                child->right = gchild->left;
                if(gchild->left != nullptr){
                    gchild->left->parent =child;
                }

                gchild->left =child;
                child->parent =gchild;
                gchild->right = wrong;
                wrong->parent = gchild;

                nroot = gchild;

            }


        }
        else{
            //rl rotation
            if(gchild ==child->left){
                gchild->parent =wrong->parent;
                if(wrong->parent->left ==wrong){
                    wrong->parent->left = gchild;
                }
                else{
                    wrong->parent->right = gchild;
                }

                wrong->right = gchild->left;
                if(wrong->right!= nullptr){
                    wrong->right->parent = wrong;
                }
                child->left = gchild->right;
                if(gchild->right!=nullptr){
                    gchild->right->parent = child;
                }

                gchild->left = child;
                child->parent = gchild;

                gchild->left = wrong;
                wrong->parent = gchild;
                nroot =gchild;

            }

            //rr rotation
            else{
                child->parent = wrong->parent;
                if(wrong->parent->left == wrong){
                    wrong->parent->left = child;
                }
                else{
                    wrong->parent->right = child;
                }

                wrong->right = child->left;
                if(wrong->right!=nullptr){
                    wrong->right->parent = wrong;
                }

                child->left = wrong;
                wrong->parent = child;

                nroot = child;

            }

        }
        wrong->checkh();
        child->checkh();
        gchild->checkh();
        return nroot;
    }

    void DeleteNode(){
        if(this->parent == nullptr){
            return ;
        }
        if(this->left == nullptr && this ->right == nullptr){
            if(this->parent->left == this){
                this->parent->left = nullptr;
            }
            if(this->parent->right == this){
                this->parent->right = nullptr;
            }
            this->left = nullptr;
            this->right =nullptr;
        }
        else if(this->left == nullptr){
            this->right->parent = this->parent;
            if(this->parent->left ==this){
                this->parent->left= this->right;
            }
            if(this->parent->right == this){
                this->parent->right = this->right;
            }
            this->right = nullptr;
        }
        else if(this->right == nullptr){
            this->left->parent = this->parent;
            if(this->parent->left == this){
                this->parent->left = this->left;
            }
            if(this->parent->right== this){
                this->parent->right = this->left;
            }
            this->left=nullptr;
        }

        //check height imbalance and settle them
        if(this->left == nullptr || this->right == nullptr){
            this->height = -1;
            AVLTree *wrong = this->parent;
            AVLTree *child =nullptr;
            AVLTree *gchild =nullptr;
            bool wrongfound;
            while(wrong ->parent!= nullptr){
                wrongfound =  !wrong->checkh();
                if(wrongfound){
                    int lheight = -1;
                    int rheight = -1;
                    if(wrong->left !=nullptr){
                        lheight =wrong->left->height;
                    }
                    if(wrong->right != nullptr){
                        rheight= wrong->right->height;
                    }
                    if(lheight>=rheight){
                        child = wrong->left;
                    }
                    else{
                        child = wrong->right;
                    }

                    int lgheight = -1;
                    int rgheight = -1;
                    if(child->left!= nullptr){
                        lgheight= child->left->height;
                    }
                    if(child->right!=nullptr){
                        rgheight = child->right->height;
                    }
                    if(lgheight >= rgheight){
                        gchild = child->left;
                    }
                    else{
                        gchild =child->right;
                    }
                    wrong = this->balance(wrong, child, gchild);
                }
                wrong = wrong->parent;
            }
            return;
        }
        AVLTree *t = this->right;
        while(t!= nullptr && t->left!= nullptr){
            t=t->left;
        }
        AVLTree *p = new AVLTree(t->address, t->size, t->key);
        p->left = this->left;
        p->right = this->right;
        p->parent = this->parent;
        p->left->parent = p;
        p->right->parent = p;
        if(p->parent->left == this){
            p->parent->left = p;
        }
        else{
            p->parent->right =p;
        }
        t->DeleteNode();
    }

    int getHeight(AVLTree *t){
        if(t==nullptr){
            return -1;
        }
            int lheight =-1;
            int rheight = -1;
            if(t->left!= nullptr){
                lheight = t->left->height;
            }
            if(t->right!= nullptr){
                rheight = t->right->height;
            }
            if(this->getHeight(t->left)==-2|| this->getHeight(t->right)==-2){
                return -2;
            }
            if(lheight>rheight){
                if(t->height != lheight + 1 || lheight>rheight+1){
                    return -2;
                }
            }
            else{
                if(t->height!=rheight+1 || rheight>lheight+1){
                    return -2;
                }
            }
            return t->height;
        }
    


   public:
   AVLTree(): BSTree(){}
   AVLTree(int address, int size, int key):BSTree(address,size,key){
       this->height = 0;
   }
   AVLTree *Insert(int address, int size, int key){
       AVLTree *t = this->getRoot();

       //empty tree
       if(t== nullptr){
           AVLTree *node = new AVLTree(address,size,key);
           node->parent = this;
           this->right = node;
           return node;
       }
       int dir;
       while(t!=nullptr && (t->left !=nullptr || t->right != nullptr)){
           if(t->key<key){
               dir = 1; //means right dir
           }
           else if(t->key>key){
               dir = 0; // means left dir
           }
           else{
               if(t->address<address){
                   dir = 1;
               }
               else{
                   dir = 0;
               }
           }

           //insertion based on direction
           if(dir==0){
               if(t->left != nullptr){
                   t=t->left;
               }
               else{
                   break;
               }
           }
           else{
               if(t->right !=nullptr){
                   t=t->right;

               }
               else{
                   break;
               }
           }
       }
       AVLTree *node = new AVLTree(address,size,key);
       node->parent =t;
       if(t->key >key){
           t->left = node;
       }
       else if(t->key<key){
           t->right = node;
       }
       else{
           if(t->address<address){
               t->right = node;
           }
           else{
               t->left = node;

           }
       }

       //height balancing
       AVLTree *wrong = node->parent->parent;
       AVLTree *child = node->parent;
       if(child->height<1){
           child->height = 1;
       }
       AVLTree *gchild = node;
       bool wrongfound = false;
       while(!wrongfound && wrong->parent!=nullptr){
           wrongfound = !wrong->checkh();
           if(wrongfound){
               wrong = this->balance(wrong,child, gchild);
               wrongfound = true;
           }
           gchild = child;
       child = wrong;
       wrong= wrong->parent;
       }
       
        return node;
   }

   bool Delete(Dictionary *d){
       AVLTree *t =this->getRoot();
       while(t!= nullptr){
           if(t->key< d->key){
               t= t->right;
           }
           else if(t->key>d->key){
               t =t ->left;
           }
           else{
               if(t->address<d->address){
                   t = t->right;
               }
               else if(t->address> d->address){
                   t = t->left;
               }
               else{
                   if(t->size==d->size){
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

   AVLTree *Find(int k, bool exact){
       AVLTree *t = this->getRoot();
       AVLTree *notenode = nullptr;   //e for exact
       AVLTree *enode = nullptr;
       while(t!= nullptr){
           if(t->key<k){
               t=t->right;
           }
           else{
               if(t->key == k){
                   enode = t;
               }
               else{
                   notenode =t;
               }
               t= t->left;
           }

       }
       if(!exact){
           if(enode == nullptr){
               return notenode;
           }

       }
       if(enode == nullptr){
           return nullptr;
       }
       return enode;
   }

   AVLTree *getFirst(){
       AVLTree *t = this->getRoot();
       while(t!= nullptr && t->left==nullptr){
           t= t->left;
       }
       return t;
   }

   AVLTree *getNext(){
       if(this->parent == nullptr){
           return nullptr;
       }
       if(this->right!= nullptr){
           AVLTree *t = this->right;
           while(t->left!= nullptr){
               t=t->left;
           }
           return t;
       }
       else{
           AVLTree *t= this;
           while(t!=nullptr && t->parent!=nullptr && t->parent->left !=t){
               t = t->parent;
           }
           if(t->parent==nullptr){
               return nullptr;
           }
           else{
               return t->parent;
           }
       }
   }
   

   bool sanity(){
       if(!BSTree::sanity()){
           return false;
       }
       if(this->getRoot()!=nullptr){
           if(this->getHeight(this->getRoot())==-2){
               return false;
           }
       }
       return true;
   }

};
#endif