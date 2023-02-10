//Vado a generare un programma molto semplice che inserisce all'interno del file,  valori di un account e mostra a video quelli richiesti dall'utente!
#include <iostream>
#include <string>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin; 
using std::endl;
using std::string;

int request();
void inserisco(ofstream&);
void mostro(int, string&, string&, double);
bool damostrare(int, double);

int main(){
    string nome, cognome; 
    int numero, choise; 
    double guadagno; 

    ofstream inserimento;
    ifstream lettura;

    choise=request();

    while(choise!=4){

        switch(choise){
            case 0: 
                //Ipotizziamo che ci sia un caso in cui l'utente scegli di inserire all'interno del file tutti i conti!
                cout<<"Andiamo ad inserie gli elementi all'interno del file!\n";
                inserimento.open("conti.txt", std::ios::app);

                if(!inserimento){
                    std::cerr<<"Guarda che non posso aprire il file!"<<endl;
                }

                while(cin>>numero >>nome >>cognome >>guadagno){
                    inserimento<<numero<<" "<<nome<<" "<<cognome<<" "<<guadagno<<endl;
                }

                inserimento.close();

                cin.ignore(1000, '\n');
                cin.clear();
            

                goto avanti;


                break;

            case 1: 
                cout<<"Ti mostro i conti che hanno un saldo negativo\n";

                break;

            case 2: 
                
                cout<<"Ti mostro gli elementi che hanno saldo positivo!\n";
                break;

            case 3: 
                cout<<"Ti mostro i conti che hanno saldo nullo\n";

                break;
        }


        //Andiamo quindi a verificare quali elementi dobbiamo mostrare o meno!

        //Apriamo il file in lettura 
        lettura.open("conti.txt", std::ios::in);

        //Verifica che il file di lettura sia stato aperto correttamente
        if(!lettura){
            std::cerr<<"Guarda che così non riesco ad aprire il file che mi chiedi\n";
        }

        //Inserisco i dati contenuti nel file all'interno delle variabili
        while(lettura >>numero >>nome >>cognome >>guadagno){
            //Verifico quali di queste variabili deve essere visionata o meno
            if(damostrare(choise, guadagno)){
                //Faccio visionare il conto richiesto
                mostro(numero, nome, cognome, guadagno);
            }
        }

        lettura.close();

      avanti:  choise=request();

    }

    cout<<"Chiusura del programma!\n";

}

//Specifico la funzione che ha il compito di chiedere all'utente la scelta da compiere
int request(){
    int richiedo; 
    
    cout<<"Menù iniziale, digitare uno dei seguenti valori\n";
    cout<<"[0]-Inserimento dei dati\n[1]- Visionare conti con saldo negativo\n[2]-Visionare conti con saldo positivo\n[3]-Visionare conti con saldo nullo\n[4]-Chiuso il programma\n";

    do{


        cin.ignore();
        cin.clear();
        cin>>richiedo; 

        if(richiedo<0 or richiedo>4){
            cout<<"Guarda che così non va eh\n";
        }

    }while(richiedo<0 || richiedo>4);

    return richiedo;
}

bool damostrare(int scelta, double saldo){
    if(scelta==1 && saldo<0){
        return true;
    }

    else if(scelta==2 && saldo>0){
        return true;
    }

    else if(scelta==3 && saldo==0){
        return true;
    }

    else 
        return false;
}

void mostro(int numero, string& nome, string& cognome, double saldo){
    cout<<"Conto numero: "<<numero<<";\nIntestato a: "<<nome<<" "<<cognome<<"\nSaldo: "<<saldo<<"€\n";
    cout<<"--------------------------------------------------\n";
}



