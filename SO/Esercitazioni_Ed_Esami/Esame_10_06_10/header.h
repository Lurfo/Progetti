//Uso un monitor signal and continue
#ifndef HEADER_H 
#define HEADER_H

#include "monitor_signal_continue.h"

//Definizione delle variabili condition da utilizzare, una per i produttori ed una per i consumatori
#define VC_Scrittori 0
#define VC_Lettori 1

//Numero delle VC
#define NUM_VC 2

//Numero di letture e scritture
#define NUM_SCRITTURE 20
#define NUM_LETTURE 10


//Impostazione della struct
typedef struct{

    int temperatura;
    
    unsigned int umidità;

    unsigned short pioggia;

    //Devo definire anche le variabili di controllo
    //una tiene conto del numero di lettori
    //l'altra tiene conto del numero di scrittori 
    int numLettori; 
    int numScrittori;


    //Nella struttura, devo anche definire il costrutto monitor
    Monitor m;


}MeteoM;

void meteo(MeteoM *m); 
void utenti(MeteoM *m);

void scrittura(MeteoM *m, int *temp, unsigned int *umid, unsigned short *piog); 
void lettura(MeteoM *m, int *temp, unsigned int *umid, unsigned short *piog);


#endif