//Andiamo a creare la funzione che ha lo scopo di individuare la lunghezza della lcs
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

template <typename prova>
const prova& max(const prova& uno, const prova& due){
    return(uno>due) ? uno:due;
}


int lcs(std::string a, std::string b, int lunga, int lungb){
     if(lunga==0 or lungb==0){
         return 0;
     }

   else if(a[lunga-1] == b[lungb-1])
        return 1+lcs(a, b, lunga-1, lungb-1);

    else 
        return max(lcs(a,b,lunga-1, lungb), lcs(a,b,lunga,lungb-1));
 }


int main(){
     std::string uno;
     std::string due;

    cout<<"Dimmi la prima cosa\n";
     getline(cin, uno);

     cout<<"Dimmi la seconda cosa\n";
     getline(cin, due);

    cout<<"La lunghezza massima della stringa che mi hai dato è:  "<<lcs(uno, due, uno.length(), due.length())<<" caratteri"<<endl;

 }


