
#include "Geeks.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
using std::string;
using std::vector;
using std::list;
using std::cin;
using std::cout;

template <typename T>
int partition (vector <T> &A, int p, int q);

template <typename T>
void quickSort(vector<T> &A, int p, int r){
    if(p<r)
    {
        int q=partition(A,p,r);
        quickSort(A,p,q);
        quickSort(A,q+1,r);
    }
}

template <typename T>
void swap(vector <T>&A, int x, int y) {
    T temp=A[x];
    A[x]=A[y];
    A[y]=temp;
}

template <typename T>
int partition(vector<T> &A, int p, int r)
{
    T x=A[p];
    int i=p-1;
    int j=r+1;

    while(true)
    {
        do
            j=j-1;
        while(*x< *A[j]);
        do
            i=i+1;
         while (*A[i] <*x);
         if (i<j)
         swap(A,i,j);
         else
         return j;
        
    }
}


int main()
{
    Geeks g1("NA349M",20.7,2);
    Geeks g2("NA567",50.6,3);
    Projects p1(1020,"Fiat ", 20.7 , 30 , 06,2021);
    Projects p2(2021,"Apple", 20.8, 12 , 05,2021);
    Projects p3(1130,"Samsung",30.4,30,05,2011);


    vector<Geeks*> gk;
    gk.push_back(&g1);
    gk.push_back(&g2);
    
    vector<Projects*> bib;
    bib.push_back(&p1);
    bib.push_back(&p2);
    bib.push_back(&p3);

    cout<<" - Stampa delle informazioni richieste . . ."<<"\n";

    cout<<"List of Fantaware geeks: "<<"\n";
    for(int j=0;j<gk.size();j++)
    cout<<gk[j]->toString()<<"\n";

    cout<<"List of Fantaware projects: "<<"\n";
    for(int i=0; i<bib.size(); i++)
    cout<<bib[i]->toString()<<"\n";

    cout<<"Elenco assegnazioni dei progetti: "<<"\n";
    p1.assign_geek(p1,g1);
    p2.assign_geek(p2,g1);
    p2.assign_geek(p2,g2);


}