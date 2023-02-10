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

	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
	Wait_Sem(ds_sem, MUTEX_P);

	int tempocasuale = rand() % 5+0;

//Il cliente dapprima aspetta un tempo casuale da 0 a 5 secondi con sleep
	printf("Il tempo d'attesa e' %d\n", tempocasuale);
	sleep(tempocasuale);

	int numerop= rand() % 4+1;
	printf("Cliente: voglio prenotare %d posti \n",numerop);
	
	if(numerop<*contposti){
		for(int i=0;i<numerop;i++){
		while(indice<=posti && p->stato[indice]!=POSTO_LIBERO){
			indice++;
		}
		p->stato[indice]==POSTO_INAGGIORNAMENTO;
		*contposti=*contposti-1;
	}
    }
	else{
		printf("Disponibilita' esaurita!\n");
	}
	 
	Signal_Sem(ds_sem,MUTEX_P);
	sleep(1);
	for(int i=0;i<posti;i++){
			if( p->stato[i]=POSTO_INAGGIORNAMENTO){

			p->stato[i]=POSTO_OCCUPATO;
			p->id_cliente[i]=getpid();
	
	}
	}

	Signal_Sem(ds_sem,POSTO_DISPONIBILE);
}


void visualizzatore(posto *p,int ds_sem){
	Wait_Sem(ds_sem,POSTO_DISPONIBILE);

	for(int i=0;i<posti;i++){
		if(p->stato[i]==POSTO_OCCUPATO){
			printf("Il posto numero %d e' occupato con pid: %d\n ", i , p->id_cliente[i]);
		}
		else{
			printf("Il posto numero %d risulta essere libero\n",i);			}
	}
		Signal_Sem(ds_sem,SPAZIO_DISPONIBILE);
}




















