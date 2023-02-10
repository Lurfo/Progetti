#include "container.h"
#include "box.h"
#include "box_giacenza.h"
#include <iostream>
#include <fstream>
#include <queue>

using std::string;
using std::queue;
using std::fstream;
using std::ios;
using std::cout; 
using std::cin; 
using std::endl; 

enum class choice{INS=1, LEGGO, COPY, SEE, CLEAR, DELETE, GIAC, DELETEGIAC, END};

choice scelgo();
void insert(fstream&); 
void leggoFile(fstream&);
void copio(fstream&, queue<Container*>&);
void vedo(queue<Container*>&);
void clear(queue<Container*>&, std::list<Box*>&);
//void inserimentoGiacenza(Container*, std::list<Box*>&);
void deleteFromQueue(queue<Container*>&);
void vedoGiac(std::list<Box*>&);
void rimuovoGiac(std::list<Box*>&);

int main(){
    //Definisco l'apertura del file!
    //Il file deve essere aperto sia in ingresso che in lettura!
    //Lo aprimo in modalità append, in modo che ogni volta non andiamo ad eliminare gli elementi che sono già presenti
    //al suo interno!
    fstream mioFile{"cont.txt", ios::in | ios::out};
   
    queue<Container*> coda;

    std::list<Box*> giacenza;

    char risp;

    choice scelta; 

    while((scelta=scelgo())!=choice::END){
        switch (scelta){
        case choice::INS:
            insert(mioFile);
            break;

        case choice::LEGGO: 
            leggoFile(mioFile);
            break;

        case choice::COPY:
            copio(mioFile, coda);
            break;
        
        case choice::SEE:
            vedo(coda);
            break;

        case choice::CLEAR:{
            clear(coda, giacenza);
        }
            break;
        
        case choice::DELETE:
            deleteFromQueue(coda);
            break;
        
        case choice::GIAC: 
            vedoGiac(giacenza);
            break;
        
        case choice::DELETEGIAC: 
            rimuovoGiac(giacenza);
            break;
        
        default:
            std::cerr<<"La scelta effettuata non è valida!\n";
            break;
        }

        mioFile.clear();

    }


}

choice scelgo(){
    int num; 
    cout<<"-----------------------------------\n";
    cout<<"[1] - Inserimento degli elementi nel file\n";
    cout<<"[2] - Lettura degli elementi che sono inseriti all'interno del file\n";
    cout<<"[3] - Copia degli elementi del file all'interno di una queue!\n";
    cout<<"[4] - Vedo tutti gli elementi che sono contenuti nella queue\n";
    cout<<"[5] - Vedo un elemento dalla queue\n";
    cout<<"[6] - Elimino il primo elemento dalla queue!\n";
    cout<<"[7] - Guardo gli elemeti che sono contenuti in giacenza!\n";
    cout<<"[8] - Elimino i pacchi contenuti in giacenza!\n";
    cout<<"[9] - Termino il programma!\n";
    cout<<"-----------------------------------\n";

    cin>>num; 

    choice scelta{static_cast<choice>(num)};

    return scelta;
}


void insert(fstream& file){

    //Definizione di tutti le variabili di cui ho bisogno per andarle ad inserire nel file!
    string id; 
    string paese; 
    string corrire; 

    string packId; 
    int peso; 
    int valore; 
    int dep;

    int num;
    char risp;

    cout<<"-----------------------------------\n";
    cout<<"Inserimento nel file\n"; 

    if(!file){
        std::cerr<<"Non riesco ad aprire il file!\n";
    }

    else{
        cout<<"Dimmi L'id del Container\n"; 
            cin>>id;
        
        cout<<"Paese di provenienza\n";
            cin>>paese; 
        
        cout<<"Corriere incaricato\n"; 
            cin>>corrire; 
        
        file<<id<<"\n"<<paese<<"\n"<<corrire<<"\n";

        cout<<"Dimmi il numero di elementi che sono presenti all'interno del container!\n";
            cin>>num;
        
        file<<num<<"\n";
        
        int i{0};

        while(i<num){
            cout<<"Inserimento dei pacchi nel container!\n";
            
            cout<<"Numero del pacco\n"; 
                cin>>packId; 
            
            cout<<"Peso del pacco\n"; 
                cin>>peso; 
            
            cout<<"Valore del pacco\n"; 
                cin>>valore; 

            cout<<"Bene deperibile? 1- si, 0 - no\n"; 
                cin>>dep;
            
            file<<packId<<"\n"<<peso<<"\n"<<valore<<"\n"<<dep<<"\n";
            i++;
        }

        file<<endl;

    }
}



void leggoFile(fstream& file){
    string id; 
    string paese; 
    string corrire; 

    string packId; 
    int peso; 
    int valore; 
    int dep;
    int num;

    

    cout<<"-----------------------------------\n";
    cout<<"Vado a leggere gli elementi che sono contenuti nel file!\n";

    if(!file){
        std::cerr<<"Non posso aprire il file!\n";
    }

    else{
      
        while((file>>id >>paese >>corrire>>num) && !file.eof()){
            cout<<"Container: "<<id<<"\n";
            cout<<"Provenienza: "<<paese<<"\n"; 
            cout<<"Spedico da: "<<corrire<<"\n";
            cout<<"Contenuto del container!\n";
            cout<<"Sono presenti: "<<num<<" pacchi:\n";

            for(int i=0; i<num; i++){
                file>>packId >>peso >>valore >>dep;
                cout<<"-----------------------------------\n";
                cout<<"Id pacco: "<<packId<<"\n";
                cout<<"Peso: "<<peso<<" kg\n";
                cout<<"Valore: "<<valore<<" €\n";
                cout<<"Deperibile: "<<((dep!=0) ? "Si":"No")<<"\n";
                cout<<"-----------------------------------\n";
            }
        }
    }

}

void copio(fstream& file, queue<Container*>& coda){
    
    string id; 
    string paese; 
    string corrire; 

    string packId; 
    int peso; 
    int valore; 
    int dep;

    int num;

    if(!file){
        std::cerr<<"Non riesco ad aprire il file\n";
    }

    else{
        
        cout<<"Copio gli elementi all'interno della coda\n";

        while((file>>id >>paese >>corrire>>num) && !file.eof()){

            Container* punt=new Container;

            punt->setIdCont(id); 
            punt->setState(paese);
            punt->setCarrier(corrire);

            for(int i=0; i<num; i++){
                file>>packId >>peso >>valore >>dep;
                punt->addPackage(packId, peso, valore, dep);
            }

            coda.push(punt);

        }

        cout<<"Copia conclusa, ci sono: "<<coda.size()<<" container in attesa\n";

    }

}

void vedo(queue<Container*> & coda){
    cout<<"Ti mostro tutti gli elementi che ci sono all'interno della coda\n";
    cout<<"Questa operazione rimuove tutti gli elementi!\n";

    Container* punt ;
    
    int i=coda.size();

    if(!coda.empty()){
        for(i; i>0; i--){
            punt=coda.front();
            cout<<punt->ToString();
            cout<<"---------------------\n";
            coda.pop();
        }
    }

    else{
        std::cerr<<"La corda ormai è vuota!\n";
    }

}

void deleteFromQueue(queue<Container*>& coda){
   
    if(!coda.empty()){
        coda.pop(); 
        cout<<"Nella lista restano: "<<coda.size()<<" elementi\n";
    }

    else{
        std::cerr<<"Guarda che la lista è vuota!\n";
    }

}

void clear(queue<Container*>& coda, std::list<Box*>& giac){
    //Specifica della funzione che ha il compito di andare a vedere il container che si trova al top della lista!

    Container* punt;

    if(!coda.empty()){
        punt=coda.front(); 

        cout<<"Ti mostro l'elemento che si trova all'inizio della lista!\n"; 
        cout<<punt->ToString(); 

        if(punt->getTotalValue()>100){
            cout<<"Ho visto che il container supera il valore totale massimo, vado quindi a rimuovere gli elementi che son sono deperibili\n"; 
              
              //Con un iterator vado a verificare tutti gli elementi che sono contenuti all'interno della classe Container 
            std::list<Box*>::const_iterator p(punt->pac.begin());
            
            Giacenza* pacch = new Giacenza; 

            for(p; p!=punt->pac.end(); ++p){
            
                 if(!(*p)->perish()){
                    
                    (*pacch).setIdCont(punt->getIdCont());
                    (*pacch).setId((*p)->getId());
                    (*pacch).setPerish(false); 
                    (*pacch).setValue((*p)->getValue());
                    (*pacch).setWeight((*p)->getWeight());

                    giac.push_front(pacch);

                    std::list<Box*>::const_iterator c=p;
                    --p;
                    delete *c;
                    punt->pac.erase(c);

                    
                    

                }

            }
            

        }


    }



    else{
        std::cerr<<"Gurda che la coda è vuota\n";
    }

    Giacenza* nuvo= new Giacenza;

    nuvo->setId("fkfjfkj");
    nuvo->setIdCont("fggjgj");
    nuvo->setPerish(1);
    nuvo->setValue(345);
    nuvo->setWeight(24566);

    giac.push_back(nuvo);
    

}

//void inserimentoGiacenza(Container* punt, std::list<Box*>& giac){}

void vedoGiac(std::list<Box*>& giac){
    cout<<"Andiamo a vedere gli elementi che sono contenuti nella lista di giacenza!\n"; 

    std::list<Box*>::iterator prov(giac.begin()); 

    for(prov; prov!=giac.end(); ++prov){
        cout<<(*prov)->toString();
    }

}

void rimuovoGiac(std::list<Box*>& giac){
    cout<<"Rimuovo un elemento che è contenuto all'interno della lista!\n"; 
    cout<<"Nella lista ci sono: "<<giac.size()<<" elementi\n";
      

    for(std::list<Box*>::const_iterator prov=giac.begin(); prov!=giac.end(); ++prov){
        

        if((*prov)->perish()==1){
            
            cout<<"Ho trovato l'elemento che ha come id: "<<(*prov)->getId()<<"\n";

            std::list<Box*>::const_iterator c=prov;            

            --prov;

            delete *c;
            giac.erase(c);
            
            cout<<"Elemento eliminato, adesso la lista ha come dimensione: "<<giac.size()<<"\n";
            
        }

    }


}
