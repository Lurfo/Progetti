#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int pid, st;
	char *c= (char *) malloc (15);
	strcpy(c,"Ciao Mondo");
	printf(" Indirizzo var c = %p\n ", c);	
	printf("Indirizzo del puntatore %p\n", &c);
	pid=fork(); 
		
	if (pid==-1){
		fprintf(stderr, "generazione del processo fallita");
		return -1;
	}
	if  (pid==0){
			
	 	printf("\nSono il processo figlio\n");
		printf("Mio PID: %d\n",getpid());
		printf("PID di mio padre: %d\n\n",getppid());
		strcpy(c,"Ciao Figlio");
		printf(" Valore (figlio) c = %s\n ", c);	
		printf(" Indirizzo var c = %p\n ", c);	
		printf("Indirizzo del puntatore %p\n", &c);

		//sleep(20);
		_exit(3);
	}
	else if (pid>0){
		wait(NULL);
		printf("\nSono il processo padre\n");
		printf("Mio PID: %d\n",getpid());
		printf("PID di mio padre: %d\n\n",getppid());
		printf(" Valore (padre) c = %s\n ", c);
		printf(" Indirizzo var c = %p\n ", c);
		printf("Indirizzo del puntatore %p\n", &c);
	

		//sleep(10);
		/*wait(&st);
		printf("il figlio %d ha terminato l'esecuzione ",pid);
		if ((char)st==0)
			printf("con stato: %d\n\n",st>>8);
		else
			printf("involontariamente!\n\n");
		*/
	}


	return 0;
}
	 	

