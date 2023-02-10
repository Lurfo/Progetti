#include <iostream>
#include <string>
#include "invoice.h"

using std::cout;
using std::cin;
using std::endl;
using std::string; 

void mostramitutto(Invoice ricevuta, std::string paese){

     cout<<"Numero Prodotto: "<<ricevuta.getNumb()<<endl;
        cout<<"Descrizione Prodotto: "<<ricevuta.getDesc()<<endl;
        cout<<"Pezzi: "<<ricevuta.getQuant()<<", Prezzo/unità: "<<ricevuta.getPrice()<<"€"<<endl;
        cout<<"Imposta: "<<ricevuta.getVAT()*100<<"%"<<", Paese di residenza: "<<paese<<"\n";
        cout<<"Prezzo finale: "<<ricevuta.getInvoiceAmount()<<"€\n";
        cout<<"Applicato uno sconto del: "<<ricevuta.getDisc()*100<<"%"<<endl;
}

int main(){
    //Dichiaro le variabili necessarie al programma
    char risp;
    string numero, descr, paese;
    int prezzo{0}, quant{0}; 
    double  vat{0}, sconto{0};

    //Dichiaro l'oggetto ricevuta e lo inizializzo
    Invoice ricevuta{"2FJFJ132","Carta",12, 1200};

     if(paese==""){
        paese="Non Dichiarato";
    }

    mostramitutto(ricevuta, paese);

    //Chiedo conferma sull'esattezza dei dati
    cout<<"E' esatta?[y/n]\n";
    cin>>risp; 
    cin.ignore(100,'\n');

    //Se i dati sono errati procedo con il modificarli
    if(risp=='n'){
        
        //Inserimento numero e descrizione del prodotto
        cout<<"Inseriamo i dati corretti\n";
        cout<<"Dimmi il codice del prodotto\n";
        getline(cin, numero);
        
        cout<<"Dimmi la descrizione del prodotto\n";
        getline(cin, descr);
        
          //Salvataggio dei dati
            cout<<"--------------------------------------------"<<endl;
            cout<<"Salvo i dati inseriti\n";
            ricevuta.setPartNumb(numero);
            ricevuta.setPartDesc(descr);
            cout<<"--------------------------------------------"<<endl;

        //Inserimento del prezzo e della quantità
        cout<<"Dimmi il prezzo della merce\n";
        cin>>prezzo;
        cout<<"Dimmi la quantità\n";
        cin>>quant;
        cin.ignore(100, '\n');

            //Salvataggio dei dati
            cout<<"-------------------------------"<<endl;
            cout<<"Salvo i dati\n";
            ricevuta.setPrice(prezzo);
            ricevuta.setQuant(quant);
            cout<<"--------------------------------"<<endl;

        //Inserimento dell'imposta, tramite scelta del paese di residenza
        cout<<"Imposta paese di residenza (per il calcolo delle imposte)\n";
        cout<<"Italia IVA=22%\nIrlanda IVA=23%\nGermania IVA=19%\nFrancia IVA=20%\n";
        cout<<"(E' possibile effettuare l'acquisto solo nei paesi di cui sopra)\n";
        cout<<"Puoi lasciare incompleto il campo\n";
        cout<<"Non modificherai l'imposta di base pari a: "<<ricevuta.getVAT()*100<<"%"<<endl;
        getline(cin, paese);

        if(paese==""){
            cout<<"In questo modo non hai insetito alcuna residenza!\n";
        }
        

        else{
            //Controllo del paese inserito
            while (paese!="Italia" and paese!="Irlanda" and paese!="Germania" and paese!="Francia"){
                cout<<"Inserire una località valida!\n";
                getline(cin,paese);     
            }

                //Inserimento dell'imposta
                if(paese=="Italia"){
                    vat=0.22;
                }
                else if(paese=="Irlanda"){
                    vat=0.23;
                }
                else if(paese=="Germania"){
                    vat=0.19;
                }

                else if(paese=="Francia"){
                    vat=123;
                }
        }

        //Inserimento dello sconto
        cout<<"Inserire lo sconto in %: ";
        cin>>sconto; 
        cout<<endl;

            //Salvataggio imposta e sconto
            cout<<"------------------------------------"<<endl;
            cout<<"Salvo i dati inseriti\n";
            ricevuta.setVAT(vat);
            ricevuta.setDisc(sconto);
            cout<<"------------------------------------"<<endl;

        cout<<"Operazione completata!"<<endl;

    }
    
    cout<<"Vuoi controllare la ricevuta finale?[y/n]"<<endl;
    cin>>risp;

    if(risp=='y'){
            mostramitutto(ricevuta, paese);     
    }
}
