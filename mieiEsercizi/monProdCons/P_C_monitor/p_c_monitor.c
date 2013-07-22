#include "header.h"

int main(){
	int id_shared,k,pid,num_processi,status;
	num_processi = 10;
	msg* mess;
	key_t chiave;
	cond* conditions;
	Monitor mio_Monitor;
	id_shared = shmget(chiave,sizeof(cond)+sizeof(msg),IPC_CREAT|0664);
	mess=(msg*) (shmat(id_shared,0,0));
	conditions = (cond*) (mess+1); //Il puntatore alla condizione si trova dopo quello per il messaggio
	conditions -> ok_produzione = 1;
	conditions -> ok_consumo = 0;

	init_monitor(&mio_Monitor,NUM_CONDITIONS); //#define NUM_CONDITIONS 2

//generazione di processi produttori e consumatori
	for(k=0;k<num_processi;k++){
		pid = fork();
		if(pid == 0){
			if((k%2)==0){
				printf("Sono il figlio Produttore, pid= %d \n",getpid());
				sleep(1);
				Produttore(&mio_Monitor,conditions,mess);
			}
			else{
				Consumatore(&mio_Monitor,conditions,mess);
				sleep(5);		
			}
			exit(0);		
		}//if(pid==0)	
	}//for

	for(k=0;k<num_processi;k++){
		pid=wait(&status);
		if(pid==-1)
			perror("errore");
		else
			printf("Figlio num %d e\' morto con stato %d \n",pid,status);
	}
	remove_monitor(&mio_Monitor);
	shmctl(id_shared,IPC_RMID,0);
	return 1;
}
