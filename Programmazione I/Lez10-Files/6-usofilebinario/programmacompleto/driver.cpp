//genere un driver in grado di poter sfruttare un file binario per poter gestire dei conti 
#include "accounts.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using std::cin; 
using std::cout; 
using std::endl; 
enum class Choice{NEW=1, UPDATE, DELETE, PRINT, STAMPO, MODIFICA, ALL, END};

int numeroconto();
Choice scelta();
void mostro(std::ostream&, const Account&);
void elimino(std::fstream&);
void aggiungo(std::fstream&);
void modifico(std::fstream&);
void salvataggio(std::fstream&);
void stampo(std::fstream&);
void modificotutto(std::fstream&);
void tutto(std::fstream&);


int main(){
    //Vado ad prire il file che mi serve per salvare gli elementi!
    //Il file che inserisco qui dentro è quello è completamente riempito con degli elementi vuoti!
    //In questo modo mi posso muovere tra tutti gli elementi vuoti e verificare se ci sono elementi riempiti o meno!
    //Solo in questo modo possiamo implementare determinate funzioni come quella di nuovo inserimento o di eliminazione!
    std::fstream primo{"prova.dat", std::ios::in | std::ios::out | std::ios::binary};

    if(!primo){
        std::cerr<<"Non posso aprire il file\n";
        exit(EXIT_FAILURE);
    }

   Choice scelt; 
   

    while((scelt=scelta())!=Choice::END){
        switch (scelt){
        case Choice::NEW:
           
            aggiungo(primo);

            break;

        case Choice::UPDATE:
            modifico(primo);
            break;

        case Choice::DELETE:
            elimino(primo);
            break;

        case Choice::PRINT:
            salvataggio(primo);
            break;

        case Choice::STAMPO:
            stampo(primo);
            break;

        case Choice::MODIFICA:
            modificotutto(primo);
            break;

        case Choice::ALL:
            tutto(primo);
            break;
        
        default:
            std::cerr<<"La scelta che hai definito non è valida!\n";
            break;
        }



        //Questa funzione che  è stata qui definita risulta essere molto importante, poichè abbiamo che il puntatore di End of File, viene 
        //Modificato da determinate funzioni che abbiamo definito nel programma, di conseguenza è necessario riportarlo nuovamente all'inizio
        //In modo che il file, alla nuova chiamata di funzione, possa essere riletto nuovamente!

        //Se non fosse presenta questa istruzione sarebbe impossibile rileggere il file anna nuova chiamata, quindi non avremo possibilità di svolgere
        //dopo aver modificato la posizione dell'EoF, una nuova funzione sul file che abbiamo considerato inizialmente!
        primo.clear();

    }


}

int numeroconto(){
    int numero;
    do{
    cout<<"Insrisci un numero per il conto, che deve essere compreso tra 1 e 100!\n";
    cin>>numero; 
    }while(numero<1 && numero>100);

    return numero;    
}
Choice scelta(){
    int scelgo;
    cout<<"--------------------------------\n";
    cout<<"Dimmi cosa hai bisongo!\n";
    cout<<"[1] - Creo un nuovo contatto nel file!\n";
    cout<<"[2] - Modifico un contatto\n";
    cout<<"[3] - Elimino un contatto\n";
    cout<<"[4] - Salvo gli elementi in un file di testo\n";
    cout<<"[5] - Stampa gli elementi\n";
    cout<<"[6] - Modifica completamente un elemento\n";
    cout<<"[7] - Elimino tutto\n";
    cout<<"[8] - Termino il programma\n";
    cout<<"---------------------------------\n";
    cin>>scelgo;

    Choice scelgo2{static_cast<Choice>(scelgo)};
   
    return scelgo2;
}
void mostro(std::ostream& out, const Account& persona){
    out<<"-------------------------------\n";
    out<<"Hai selezionato l'account numero: "<<persona.getNum()<<"\n";
    out<<"Nome: "<<persona.getName()<<"\n";
    out<<"Cognome: "<<persona.getLast()<<"\n";
    out<<"Saldo: "<<persona.getBal()<<"€\n";
    out<<"----------------------------------\n";

}

void elimino(std::fstream& ingresso){
    int conto{numeroconto()};

    Account eliminabile; 

    ingresso.seekg((conto-1)*sizeof(Account));
    ingresso.read(reinterpret_cast<char*>(&eliminabile), sizeof(Account));

    if(eliminabile.getNum()!=0){
        char risp;
        mostro(cout, eliminabile);

        cout<<"Sei sicuro di voler procere con l'eliminazione?[y/n]\n";
        cin>>risp;

        while(risp!='y' && risp!='n'){
            std::cerr<<"Inserisci una risposta valida![y/n]\n";
            cin>>risp;
        }

        if(risp=='y'){
            
            cout<<"Elimino l'elemento!\n";

            //Per eliminare l'elemento definisco una classe vuota da inserire in quella posizione!

            Account vuoto{};

            ingresso.seekp((eliminabile.getNum()-1)*sizeof(Account));
            ingresso.write(reinterpret_cast<char*>(&vuoto), sizeof(Account));

            cout<<"Elemento Eliminato!\n";

        }

        else{
            cout<<"Non elimino l'elemento!\n";
            return;
        }

    }

    else{
        std::cerr<<"L'elemento che mi hai specificato è già vuoto!\n";
    }

}


void aggiungo(std::fstream& binario){
   

    if(!binario){
        std::cerr<<"Non posso aprire il file\n";
        exit(EXIT_FAILURE);
    }


    int numerAcc{numeroconto()};
  

    binario.seekg((numerAcc-1) * sizeof(Account));
 
    Account utente; 

    binario.read(reinterpret_cast<char*>(&utente), sizeof(Account));

    if(utente.getNum()==0){
        std::string nome;
        std::string cognome;
        double bilancio; 

        cout<<"Dimmi il nome\n";
        cin>>std::setw(15)>>nome;
        cout<<"Dimmi il cognome\n";
        cin>>std::setw(15)>>cognome;
        cout<<"Dimmi il saldo\n";
        cin>>bilancio;

        utente.setNum(numerAcc);
        utente.setName(nome);
        utente.setLast(cognome);
        utente.setBal(bilancio);

        binario.seekp((utente.getNum()-1)*sizeof(Account));
        binario.write(reinterpret_cast<char*>(&utente), sizeof(Account));
    }

    else{
        std::cerr<<"Esiste già un account con quel numero!\n";
    }


}
void modifico(std::fstream& ingresso){
    int conto=numeroconto(); 

    Account elemento; 

    ingresso.seekg((conto-1)*sizeof(Account));
    ingresso.read(reinterpret_cast<char*>(&elemento), sizeof(Account));

    if(elemento.getNum()!=0){

        mostro(cout,elemento);

        int operazione;
        cout<<"Dimmi quanto è stato aggiunto(+) o prelevato(-)\n";
        cin>>operazione; 

        int old=elemento.getBal();

        elemento.setBal(old+operazione);

        ingresso.seekp((conto-1)*sizeof(Account));
        ingresso.write(reinterpret_cast<char*>(&elemento), sizeof(Account));
    }

    else{
        std::cerr<<"Qui non esiste alcun conto che posso andare a modificare!\n";
    }

}




void salvataggio(std::fstream& ingresso){

    //Salvo gli elementi in binario all'interno di un file di testo!
    std::ofstream salvo{"conti.txt", std::ios::out};

    if(!salvo){
        std::cerr<<"Non posso aprire il file"<<endl;
        exit(EXIT_FAILURE);
    }

    //Definisco una classe che mi serve per andare ad inserire gli elementi al suo interno 
    Account elemento{}; 
    
    //Riposiziono il puntatore all'inizio, in modo che tutti gli elementi vengano salvati
    ingresso.seekg(0);
    ingresso.read(reinterpret_cast<char*>(&elemento), sizeof(Account));

    while(!(ingresso.eof())){
        //Faccio in modo di salvare solo gli elementi che sono stati effettivamente specificati e non altri elementi!
        if(elemento.getNum()!=0){
            mostro(salvo, elemento);//salvo<<elemento.getNum()<<" "<<elemento.getName()<<" "<<elemento.getLast()<<" "<<elemento.getBal()<<endl;
        }

        ingresso.read(reinterpret_cast<char*>(&elemento), sizeof(Account));


    }

    salvo.close();

}

void tutto(std::fstream& ingresso){
    char risp;
    cout<<"Sei sicuro di eliminare tutti gli elementi presenti nella memoria?[y/n]\n";
    cin>>risp;

    while(risp!='y' && risp!='n'){
        std::cerr<<"Inserisci una risposta valida![y/n]\n";
        cin>>risp;
    }

    if(risp=='y'){
        cout<<"Elimino tutti gli elementi!\n";
        
        //Creo un account vuoto!
        Account vuoto{}; 

        //Posiziono il puntatore all'inizio!
        ingresso.seekp(0);

        for(int i=0; i<100; i++ ){
            ingresso.write(reinterpret_cast<char*>(&vuoto), sizeof(Account));
        }

        cout<<"Dati eliminati!\n";

    }

    else{
        cout<<"Tono al menù\n";
    }
}



void stampo(std::fstream& ingresso){
    
    ingresso.seekg(0);

    Account elemento;

    ingresso.read(reinterpret_cast<char*>(&elemento), sizeof(Account));
    
    while(!(ingresso.eof())){

        if(elemento.getNum()!=0){
          mostro(cout, elemento);
        }

        ingresso.read(reinterpret_cast<char*>(&elemento), sizeof(Account));
    
    }   

}


void modificotutto(std::fstream& ingresso){
    cout<<"Modifica di un elemento!\n";

    int conto{numeroconto()};

    Account elemento; 

    ingresso.seekg((conto-1)*sizeof(Account));
    ingresso.read(reinterpret_cast<char*>(&elemento), sizeof(Account));

    if(elemento.getNum()!=0){
        cout<<"Dimmi i nuovi dati!\n";

        string nome, cognome;
        double bilancio;

        cout<<"Dimmi il nome:\n";
        cin>>nome;
        cout<<"Dimmi il cognome\n";
        cin>>cognome;
        cout<<"Dimmi il saldo\n";
        cin>>bilancio;

        elemento.setName(nome);
        elemento.setLast(cognome);
        elemento.setBal(bilancio);

        ingresso.seekp((conto-1)*sizeof(Account));
        ingresso.write(reinterpret_cast<char*>(&elemento), sizeof(Account));
    }

    else{
        std::cerr<<"Il numero non è associato e nessun conto!\n";
    }
    
}
