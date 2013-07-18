#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"
#include <time.h>
#include <pthread.h>
#define MAX 3
//il server instanzia un manager e due worker -> 3 threads

pthread_t threads[MAX]; 

int idSend, idRecieve;

void insertElem(Buffer* buf, Messaggio* msg){
	pthread_mutex_lock(&(buf->mutex));
	while( buf->count == N){ //il monitor dei thread è signal and continue
	
	}
}

void *manager( void* arg ){ //RIVEDERE PUNTATORI A FUNZIONE C
	Buffer* b;
	int rc;	
	Messaggio msg;
	b = (Buffer*) arg;
	while(1){
		rc = msgrcv( idRecieve , &msg, sizeof(Messaggio)-sizeof(long),1,IPC_NOWAIT);  //sizeof(long) è importante perchè il so vuole long
											//per fare la receive non bloccante metto ipc_nowait	
		if (rc > 0)
			insertElem();	
	}

}
int main(){
/*Alloco le risorse, ho bisogno di due code di messaggi che vengono utilizzate dal programma Server e da quello Cliente usufruiscono.*/
	
	int i;		//indice for delle fork
	pid_t pid;
	int status;	//serve per la wait alla fine
	key_t key_send, key_recieve;
	
	key_send = ftok(FTOK_QUEUE_SEND_PATH, FTOK_QUEUE_SEND_ID); 
	key_recieve = ftok(FTOK_QUEUE_RECIEVER_PATH, FTOK_QUEUE_SEND_ID);
	idSend = msgget( key_send , IPC_CREAT | 0);
	idRecieve = msgget( key_recieve , IPC_CREAT | 0);

}
