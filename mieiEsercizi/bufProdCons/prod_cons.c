#include "header.h"

int main(){
	int pid,id_buffer,id_stato,sem,mutex,num_processi,num_cons,num_prod,status,k;
	msg *ptr_buf;
	int *ptr_stato;
	key_t chiave_buf = ftok(".",1);
	key_t chiave_stat = ftok(".",2);
	key_t chiave_sem = ftok(".",3);
	key_t chiave_mut = ftok(".",4);
	
	num_processi = NUM_PROD + NUM_CONS;
	//richiesta del buffer
	
	id_buffer = shmget(chiave_buf,DIM*sizeof(msg),IPC_CREAT|0664); //msg buffer[DIM];
	printf(" id_buffer=%d \n",id_buffer);
     	ptr_buf=(msg *) (shmat(id_buffer,0,0)); //void* shmat(int shmid,const void *shmaddr,int shmflg);
	
	id_stato = shmget(chiave_stat,DIM*sizeof(int),IPC_CREAT|0664); //int stato[DIM];
	printf(" id_stato=%d \n",id_stato);
	ptr_stato=(int *) (shmat(id_stato,0,0));	
	
	init_stato(ptr_stato); //inizializza tutti gli elementi a VUOTO
	//richiesta dei semafori ed inizializzazione
	sem = semget(chiave_sem,2,IPC_CREAT|0664); //crea due sem con chiave_sem e permessi 664
	mutex = semget(chiave_mut,2,IPC_CREAT|0664); //crea due mut con chiave_mut e permessi 664
	
	//mutex sulle variabili del produttore
	semctl(mutex,MUTEXP,SETVAL,1); 
	//mutex sulle variabili del consumatore
	semctl(mutex,MUTEXC,SETVAL,1);
	//PROD: spazio_disponibile	
	semctl(sem,PROD,SETVAL,NUM_PROD);
	//CONS: messaggio_disponibile
	semctl(sem,CONS,SETVAL,0);
	
	pid = getpid();
	printf("Pid processo padre: %d \n",pid);
	
	for(k = 0 ; k<num_processi ; k++){
		pid = fork();
		if(pid == 0){ //e' figlio
			if((k%2) == 0){ //e' produttore
	     			printf("k= %d sono il figlio produttore. Il mio pid %d \n",k,getpid());
       	     			sleep(1);
				stampa_stato(ptr_stato);
				stampa_buffer(ptr_buf);				
				
				Produttore(ptr_buf,ptr_stato,sem,mutex);

				stampa_stato(ptr_stato);
				stampa_buffer(ptr_buf);
				printf("Sono uscito dalla produzione.\n");		
			} else{
				printf("k= %d sono il figlio consumatore. Il mio pid %d \n",k,getpid());
       	     			sleep(2);
				stampa_stato(ptr_stato);
				stampa_buffer(ptr_buf);				
				
				Consumatore(ptr_buf,ptr_stato,sem,mutex);
				
				stampa_stato(ptr_stato);
				stampa_buffer(ptr_buf);		
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
	shmctl(id_stato,IPC_RMID,0); //rimuovi vettore di stato
     	semctl(mutex,0,IPC_RMID); //rimuovi semaforo mutex
	semctl(sem,0,IPC_RMID); //rimuovi semaforo sem
	
	return 0;
}
