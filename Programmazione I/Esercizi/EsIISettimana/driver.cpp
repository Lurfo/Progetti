#include "classes.h"
#include <iostream>
#include <vector>


using std::map;
using std::cout; 
using std::cin; 
using std::endl; 
using std::vector;
//Non devo andare a reincludere nuovamente la classe string, in quanto l'ho già dichiarata nel file classes
using std::string;

//Definizione della mappa!
//Tale mappa usa come key il puntatore ad un programmatore, contenuto all'interno del vettore, e come parametro da mostrare il totale delle ore settimanli
//Di ogni singolo progetto!
map<Programmer*, int> tabellaOrarioSettimanale;


//La funzione weekly_worked_hours, va ad impostare all'interno della mappa, in funzione di ogni programmatore, il valore totale di ore settimanali che ha lavorato!
void weekly_worked_hours(vector<Programmer>&);

//La funzione assign_geek, non fa altro che assegnare ad ogni progetto un programmatore e viceversa, in più essa va richiamare la funzione weekly_woorked_hours, per andare a
//tenere traccia del numero di ore che il programmatore passa su quel progetto settimanalmente!
void assign_geek(vector<Programmer>&, vector<Project>&);

//Signature della funzione che ha il compito di calcolare lo stipendio totale del programmatore!
void totalSalary(vector<Programmer>&);


int main(){
    //Comincio con la definizione di un vettore di programmatori!
    
    //Dichiaro un vettore di programatori!
    vector<Programmer> programmatori;

    //Specfico i due elementi che sono presenti all'interno della classe: 
    //Una stringa per l'id del programmatore
    string id; 
    //La paga oraria del programmatore
    int paga; 

    //Risposta per chiedere di inserire un nuovo progetto!
    char risp; 

    do{
        cout<<"Inserisci l'id del programatore\n"; 
            cin>>id;
        
        cout<<"Inserisci la paga oraria del programmatore\n"; 
            cin>>paga; 

        //Utilizzo il costruttore, senza andare a fare molteplici chiamate a funzione!
        Programmer prova(id, paga);

        programmatori.push_back(prova);

        cout<<"Inserire un nuovo programatore? [y/n]\n"; 
            cin>>risp; 

        cout<<"\n\n";

    }while(risp!='n');

    
    //Dopo l'inserimento dei programmatori vado a specificare i vari progetti

    //Definisco un vettore di progetti!
    vector<Project> progetti;

    //Definisco le varie variabili che mi occorrono per instanziare l'oggetto di tipo programmatore
    string id_prog; 
    string nome_prog; 

    int g, m, a;

    //Come sopra uso un ciclo while per andare ad inserire l'elemento all'interno del vettore!
    //Andando prima a specificare tutti gli elementi che devo andare ad inserire all'interno della classe!
        cout<<"************************************************\n\n";
    do{
        cout<<"Inserisci il nome del progetto\n"; 
            cin>>nome_prog; 
        
        cout<<"Inserisci l'id del progetto\n"; 
            cin>>id_prog; 
        
        //Devo anche specificare la data, ho infatti bisogno che ogni progetto contenga una data di consegna!
        cout<<"inserisci il giorno, il mese e l'anno per la scadenza\n"; 
            cin>>g >>m >>a;
        
        //Utilizzo il costruttore della classe Project per staniare il nuovo elemento
        //Dopo l'esecuzione del while esso verrà rimosso!
        Project progetto(id_prog, nome_prog, g, m, a);

        //Inserisco l'elemento nel vettore!
        progetti.push_back(progetto);
    
        cout<<"Inserire un nuovo progetto? [y/n]\n"; 
            cin>>risp;
        
        cout<<"\n\n";

    }while(risp!='n');

    /*
    cout<<"Ti faccio vedere sia i programmatori che hai inserito!\n"; 

    for(Programmer p: programmatori){
        cout<<p.toString();
        cout<<".........................\n";
    }

    cout<<"-----------------------------\n";

    cout<<"Ti faccio vedere i progetti\n"; 

    for(Project p: progetti){
        cout<<p.toString();
        cout<<".........................\n";
    }

    cout<<"-----------------------------\n";*/

    cout<<"A questo punto bisogna andare ad assegnare un programmatore ad ogni progetto!\n";

        assign_geek(programmatori, progetti);

    

    cout<<"Vado ad inserire all'interno della tabella l'orario complessivo settimanale per ogni lavoratore!\n";
        weekly_worked_hours(programmatori);

    cout<<"Andiamo quindi a vedere tutti i dati completi\n";

    for(int i=0; i<programmatori.size(); i++){
        cout<<"***********************************\n";
        cout<<programmatori[i].toString(); 
        cout<<programmatori[i].showProject();
        cout<<"Ore di lavoro totali: "<<tabellaOrarioSettimanale[&programmatori[i]]<<"\n";
    }

    cout<<"Desideri procedere con il pagamento?\n"; 
    cout<<"In questo modo verrano azzerate le ore che il programmatore ha svolto su ogni progetto\n";
        cin>>risp;

    if(risp=='y'){
        totalSalary(programmatori); 
        
        cout<<"Ti mostro il programmatore con il suo salario\n"; 

        for(int i=0; i!=programmatori.size(); i++){
            cout<<"\n********************************\n";
            cout<<programmatori[i].toString(); 
            cout<<"Totale stipendio: "<<programmatori[i].getStipendio()<<"€\n";
        }

    }

    else{
        cout<<"Termino il programma\n";
    }



}






//Funezione che assegna ad ogni progetto un programatore e viceversa
void assign_geek(vector<Programmer>& programmatori, vector<Project>& progetti){

    char risp;

    int ore;

    cout<<"Ti mostro i vari progetti e per ogni progetto puoi scegliere quale programmatore assegnargli!\n";

    //L'idea, scorro il vettore dei progetti, ad ogni progetto, mostro i programmatori, chiedo se deve essere assegnato o meno, altrimenti vado avanti!
    for(int i=0; i<progetti.size(); i++){
        cout<<"+++++++++++++++++++++++++++++++++++++++\n";
        cout<<"Stai considerando il progetto:\n"; 
        cout<<progetti[i].toString();

        cout<<"Scegli il programmatore da affidargli\n"; 

            //Ciclo che scorre il vettore dei programmatori
            for(int j=0; j<programmatori.size(); ++j){
                cout<<"-----------------------------\n";
                cout<<programmatori[j].toString(); 

                //Chiedo se il programmatore deve essere aggiunto alla lista dei programmatori di quel progetto!
                cout<<"Affidare questo programmatore al progetto? [y/n]\n"; 
                    cin>>risp; 

                if(risp=='y'){
                    //Aggiunt il programmatore alla lista dei programmatori del progetto
                    progetti[i].addProgrammers(programmatori[j]);
                    //Aggiungo il programma alla lista dei programmi del programmatore
                    programmatori[j].addProject(progetti[i]);

                    //Aggiungo il totale di ore settimanali che il programmatore deve svolgere per questo progetto!
                    cout<<"Quante ore settimanali, questo programmatore, impiega per il progetto?\n";
                        cin>>ore;
                    
                    while(ore>168){
                        cout<<"Non può impiegare tutte queste ore per lavorare su un singolo progetto!\n"; 
                            cin>>ore;
                    }
                    
                    //Sfrutto la funzione dell'oggetto che ha il compito di inserire quel valore in corrispondenza di quella chiave!
                    //La chiave resta sempre il puntatore al progetto!
                    programmatori[j].addHour(progetti[i], ore);
                    
                }   

                else{
                    cout<<"Ti mostro il prossimo!\n";
                } 
            
            }

        cout<<"\n\n";

    }

}


//Funzione che determina il valore delle ore totali in cui il programmatore ha lavorato
void weekly_worked_hours(vector<Programmer>& programmatori){
       
        int orario;

        //Andiamo a scorrere il vettore dei programmatori 
        for(int i=0; i<programmatori.size(); i++){
            //Vado a controllare il totale di lavoro per ogni programmatore
            orario=programmatori[i].totalHourOfWork();

            //Salvo il corrispettivo valore all'interno della mappa!
            tabellaOrarioSettimanale[&programmatori[i]]=orario;
        }

        
}

void totalSalary(vector<Programmer>& programmatori){
    int totale{0}; 

    //Con un ciclo for, imposto la ricerca degli elementi che sono presenti nel vettore!
    for (int i=0; i<programmatori.size(); i++){
        //Devo quindi andare a moltiplicare il valore della paga oraria per il totale di ore che il programmatore ha lavorato!
        totale=programmatori[i].getPaga()*tabellaOrarioSettimanale[&programmatori[i]];

        //Imposto poi tale valore all'interno dell'oggetto 
        programmatori[i].setStipendio(totale);

        //Vado poi a rimuovere le ore lavorative che ha svolto su ogni progetto!
        programmatori[i].azzero();
    }
}