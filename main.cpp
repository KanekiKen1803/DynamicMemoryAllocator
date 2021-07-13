#include<iostream>
#include"AVLTree.h"
#include"DMem.h"
#include<fstream>


using namespace std;

int main(){
    int method;
    cout<<"Enter 3 for DoubleLinkedList type Dictionary"<<endl;
    cout<<"Enter 2 for BSTree type Dictionary"<<endl;
    cout<<"Enter 1 for AVLTree type dictionary"<<endl;
    cin>>method;
    ifstream infile;
    infile.open("input.txt");

    int n; //number of test cases
    int count =0;
    infile>>n;
    while(n--){
        int size;
        infile>>size;
        DMem *object = new DMem(size, method);
        int t;
        infile>>t;
        while (t--){
            count++;
            string command;
            infile>>command;
            int arg;
            infile>>arg;
            int result = -5;
            
            if(command == "Allocate"){
                result = object->Allocate(arg);
            }
            if(command == "Free"){
                result = object->Free(arg);
            }
            if(command == "Defragment"){
                object->Defragment();
            }
            
            if(result!= -5){
                cout<<result<<endl;
            }
        }
        

    }
    infile.close();
    int t;
    cout<<"Enter 0 to exit"<<endl;
    cin>>t;
    return 0;
}