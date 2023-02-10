//Definizione delle delle funionzioni che svolgono il ruolo di produttore e consumatore
#ifndef FUNCTION_H
#define FUNCTION_H

//IN QUESTO CASO VADO ANCHE A SPECIFICARE IL NUMERO DEL SEMAFORO TRAMITE UNA MACRO
#define SPAZIO_DISP 0 
#define MESSAGGIO_DISPONIBILE 1
  
//Le funzioni di produttore e consumatore prendono in ingresso il puntatore al buffer e l'id del semaforo!
void produttore(int* buffer, int semID);
void consumatore(int* buffer, int semID);

#endif