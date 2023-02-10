//Classe Ricevuta
#include <string>

class Invoice{
    private:

    //Zona riservata ai dati della ricevuta
        std::string partNumb;
        std::string partDesc;
        int quant;
        int price;
        double vat{0.20};
        double disc{0};

    public:

//Constructor per inizializzare i valori della ricevuta
         Invoice(std::string numb, std::string desc, int quant1, int prc):
        partNumb{numb}, partDesc{desc}, quant{quant1}, price{prc}{            
        }

//Funzioni per dati di ingresso:
//1) Funzione per il numero seriale
        void setPartNumb(std::string number){
            partNumb=number;
        }

//2)Funzione Descrizione del prodotto
        void setPartDesc(std::string desc){
            partDesc=desc;
        }

//3) Funzione Quantità
        void setQuant(int numbObj){
            if (numbObj>0)
            quant=numbObj;


        }

//4) Funzione Prezzo
        void setPrice(int prc){
            if (prc>0)
            price=prc;
        }

//5) Funzione Iva
        void setVAT(double iva){
            if(iva>0)
            vat=iva;

        }

//6) Funzione sconto
        void setDisc(double sconto){
            if(sconto>0)
            disc=sconto/100;
        }


//Funzioni che hanno il compito di prendere i dati
    std::string getNumb() const{
        return partNumb;
    }

    std::string getDesc() const{
        return partDesc;
    }

    int getQuant() const{
        return quant; 
    }
     int getPrice() const{
         return price;
     }

     double getVAT() const{
         return vat;
     }

    double getDisc() const{
        return disc;
    }

//Fuzione che restituisce il valore completo della ricevuta

    double getInvoiceAmount(){
        double result{0};

        result=quant*price*(1+vat);
        result=result-disc*result;
        return result;
    }




};