#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"

void cliente(int *contposti , posto *p, int ds_sem){

	int indice=0;

	int tempocasuale = rand() % 5+0;

//Il cliente dapprima aspetta un tempo casuale da 0 a 5 secondi con sleep
	printf("Il tempo d'attesa e' %d\n", tempocasuale);
	sleep(tempocasuale);

	int numposti= rand() % 4+1;
//Tentativo randomico di prentoazione 
	printf("Il cliente vuole prenotare %d\n posti",numposti);


	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
	
	Wait_Sem(ds_sem, MUTEX_P);
	
	if(numposti<*contposti){
	for(int i=0;i<numposti;i++){
		while(indice<=posti && p->stato[indice]!=POSTO_LIBERO){
		indice++;
		}
		p->stato[indice]==POSTO_INAGGIORNAMENTO;
		*contposti--;
	}
	}
	else{
		printf("Disponibilita' esaurita!");
	}

	Signal_Sem(ds_sem, MUTEX_P);

	sleep(1);

	for(int i=0;i<posti;i++){
		if(p->stato[i]==POSTO_INAGGIORNAMENTO){
			p->stato[i]=POSTO_OCCUPATO;
			p->id_cliente[i]=getpid();
		}
	}
	 
	Signal_Sem(ds_sem, POSTO_DISPONIBILE);
}


void visualizzatore(posto *p,int ds_sem){

	Wait_Sem(ds_sem,POSTO_DISPONIBILE);

	for(int i=0;i<posti;i++){
		if(p->stato[i]==POSTO_OCCUPATO){
			printf("Il posto numero %d e' occupato con pid: %d\n ", i , p->id_cliente[i]);
		}
		else{
			printf("Il posto numero %d risulta essere libero",i);			}
	}
		Signal_Sem(ds_sem,SPAZIO_DISPONIBILE);
}




















