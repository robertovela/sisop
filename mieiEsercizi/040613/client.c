#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"
#include <time.h>

#define TIPO_MESSAGGIO 1;

void inviaRichiesta(int);


int main(){
/*Alloco le risorse, ho bisogno di due code di messaggi che vengono utilizzate dal programma Server e da quello Cliente usufruiscono.*/
	
	int i;		//indice for delle fork
	pid_t pid;
	int status;	//serve per la wait alla fine
	int idSend, idRecieve;
	key_t key_send, key_recieve;
	
	key_send = ftok(FTOK_QUEUE_SEND_PATH, FTOK_QUEUE_SEND_ID); 
	key_recieve = ftok(FTOK_QUEUE_RECIEVER_PATH, FTOK_QUEUE_SEND_ID);
	idSend = msgget( key_send , IPC_CREAT | 0);
	idRecieve = msgget( key_recieve , IPC_CREAT | 0);
	
	srand(time(NULL)); //genera numeri pseudocasuali

	inviaRichiesta( id_send );
}


void inviaRichiesta(int id){
	int i;	
	Messaggio msg;
	msg.type = TIPO_MESSAGGIO;
	msg.pid = getpid();	
	for (i = 0; i < 5 ; i++){
		msg.op1 = rand()%11;
		msg.op2 = rand()%11;
		msgsnd( id_s, &msg , sizeof(Messaggio)-sizeof(long), 0); //0 dice che la send è asincrona
		sleep(1);
		msgrcv( id_r, &msg , sizeof(Messaggio)-sizeof(long), 0);
	}
}
