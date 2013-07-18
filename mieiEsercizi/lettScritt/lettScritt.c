#include "header.h"
/*
	Lettori/scrittori con starvation di entrambi
	Crea tanti processi, a volte non termina.
	Dove va la wait(&status)?
*/
int main(){
	printf("Buongiorno!\n");
	srand(time(NULL)); //inizializzazione rand
	int mutex,id_buf,k,pid,status;	
	key_t key_mutex = IPC_PRIVATE;
	key_t key_buf = IPC_PRIVATE;
	buffer *buf;	
	int num_processi = NUMLET + NUMSCRIT;
	mutex = semget(key_mutex,4,IPC_CREAT | 0664);
	semctl(mutex,MUTEX,SETVAL,1);
	semctl(mutex,MUTEX_S,SETVAL,1);
	semctl(mutex,MUTEX_L,SETVAL,1);
	semctl(mutex,SYNCH,SETVAL,1);
	id_buf = shmget(key_buf,sizeof(buffer),IPC_CREAT|0664); //nei mesg. controllare sizeof!
	buf = (buffer *) (shmat(id_buf,0,0));
	buf->msg = 0;
	buf->num_scrittori = 0;
	buf->num_lettori = 0;	
	printf("[DEBUG] Ho finito le init\n");	
	for(k=0;k<2;k++){
		pid = fork();
		if(pid == 0){ //se figlio
			printf("k: %d \n",k);			
			if((k%2)==0){
				printf("Scrittore \n");
				inizio_scrittura(buf,mutex); //passo il punt al buffer ed il vettore di semafori
				buf->msg = rand()%10;
				printf("E' stato scritto il valore %d \n",buf->msg);
				fine_scrittura(buf,mutex);			
			}
			else{
				printf("Lettore \n");
				inizio_lettura(buf,mutex);
				printf("Il valore letto e': %d \n",buf->msg);
				fine_scrittura(buf,mutex);
			}	
		}
		if(pid == -1){
			printf("ERRORE!!\n");
			exit(0);
		}
	}
	for(k=0;k<2;k++){
		pid = wait(&status);
		printf("Il processo %d e' morto con stato %d \n",getpid(),status);
	}	
	shmctl(id_buf,IPC_RMID,0);
	printf("Ho fatto la shmctl\n");
	semctl(mutex,IPC_RMID,0);
	exit(0);
}
