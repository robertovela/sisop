#include "header.h"

int main(){
	int pid,id_buffer,mutex,num_processi,num_cons,num_prod,status,k;
	long *ptr_sh;
	key_t chiave_buf = ftok(".",1);
	key_t chiave_sem = ftok(".",2);
	
	num_processi = NUM_PROD + NUM_CONS;
	//richiesta del buffer
	id_buffer = shmget(chiave_buf,sizeof(long),IPC_CREAT|0664);
	printf(" id_buffer=%d \n",id_buffer);
     	ptr_sh=(long *) (shmat(id_buffer,0,0)); //void* shmat(int shmid,const void *shmaddr,int shmflg);
	//richiesta dei semafori ed inizializzazione
	mutex = semget(chiave_sem,2,IPC_CREAT|0664); //crea due sem con chiave_sem e permessi 664
	//imposta MSG_DISP a 0 (messaggio non disponibile)
	semctl(mutex,MSG_DISP,SETVAL,0); //sem_ctl
	//imposta SPAZIO_DISP a 1 (spazio e' disponibile)
	semctl(mutex,SPAZIO_DISP,SETVAL,1);
	
	pid = getpid();
	printf("Pid processo padre: %d \n",pid);
	
	for(k = 0 ; k<num_processi ; k++){
		pid = fork();
		if(pid == 0){ //e' figlio
			if(k == 0){ //e' produttore
	     			printf("sono il figlio produttore. Il mio pid %d \n",getpid());
       	     			sleep(1);
				Produttore(ptr_sh,mutex);
				printf("Sono uscito dalla produzione.\n");		
			} else{
				printf("sono il figlio consumatore. Il mio pid %d \n",getpid());
       	     			sleep(2);				
				Consumatore(ptr_sh,mutex);		
				printf("Sono uscito dal consumo. \n");	
			}
			_exit(0);
		}
	}
	
	//solo il padre arriva qui e fa la wait?? o la wait la devono fare tutti i processi?
	for(k=0;k<num_processi;k++){
		pid = wait(&status); //passo un riferimento ad int alla wait. Quando il proc termina, mi dice con che stato.
		printf("Il processo %d e' terminato con lo stato %d \n",pid,status);
	}
	
	shmctl(id_buffer,IPC_RMID,0); //rimuovi buffer
     	semctl(mutex,0,IPC_RMID); //rimuovi semaforo mutex
	
	return 0;
}
