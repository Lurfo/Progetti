#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"

int main(){
	int status;
	key_t chiave1=IPC_PRIVATE; 
	int ds_shm1 = shmget(chiave1, sizeof(posto), IPC_CREAT|IPC_EXCL|0664);
	printf("Ottenuto descrittore\n");
	if(ds_shm1<0) { perror("Shm error!"); exit(1); }

	posto *p;

	p= (posto *) shmat(ds_shm1,NULL,0);
	printf("Ottenuto indirizzo\n");
	for(int i=0;i<posti;i++){
		p->stato[i]=POSTO_LIBERO;
		printf("I posti sono liberi, %d\n", i+1);
	}

	printf("Dopo il for\n");

	key_t chiave2=IPC_PRIVATE;

	int ds_shm2= shmget(chiave2, sizeof(int), IPC_CREAT|0664);

	if(ds_shm2<0) { perror("Shm error!"); exit(1); }

	int *contposti;
	contposti=(int *) shmat(ds_shm2,NULL,0);

	*contposti=posti;

	printf("Ho ottenuto i posti\n");

	key_t chiavesem=IPC_PRIVATE;

	int ds_sem=semget(chiavesem,3,IPC_CREAT|0064);

	if(ds_sem<0) { perror("Sem error!"); exit(1); }

	semctl(ds_sem,SPAZIO_DISPONIBILE,SETVAL, posti);
	semctl(ds_sem,POSTO_DISPONIBILE,SETVAL,0);
	semctl(ds_sem,MUTEX_P,SETVAL,1);
	
	printf("Dopo i semafori\n");


	for(int i=0;i<NUM_CONSUMATORI;i++){
		int pid=fork();

		if(pid==0){

			printf("Inizio figlio visualizzatore PID %d\n",getpid());

			srand(getpid()*time(NULL));
			visualizzatore(p, ds_sem);

			exit(1);
		}
	}


	for(int i=0;i<NUM_PRODUTTORI;i++){
		int pid=fork();

		if(pid==0){

			printf("Inizio figlio cliente PID %d \n",getpid());

			srand(getpid()*time(NULL));
			cliente(contposti,p,ds_sem);

			exit(1);
		}
	}

	for(int i=0; i<NUM_PROCESSI;i++){
		int pid=wait(&status);
		if(pid==-1)
			perror("ERRORE!");
		else
			printf("Figlio numero %d e' morto con status %d\n",pid,status);
	}

	shmctl(ds_shm1,IPC_RMID,NULL);
	shmctl(ds_shm2,IPC_RMID,NULL);
	semctl(ds_sem,0,IPC_RMID);

	return 0;
}
