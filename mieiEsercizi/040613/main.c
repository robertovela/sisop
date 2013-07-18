#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

//NOTA: esistono alcuni thread che non sono joinable: modalità detached. Alla fine nei nostri thread non ci sarà la join

int main(){
/*Alloco le risorse, ho bisogno di due code di messaggi che vengono utilizzate dal programma Server e da quello Cliente usufruiscono.*/
	
	int i;		//indice for delle fork
	pid_t pid;
	int status;	//serve per la wait alla fine
	int idSend, idRecieve;
	key_t key_send, key_recieve;
	
	key_send = ftok(FTOK_QUEUE_SEND_PATH, FTOK_QUEUE_SEND_ID); 
	key_recieve = ftok(FTOK_QUEUE_RECIEVER_PATH, FTOK_QUEUE_SEND_ID);
	idSend = msgget( key_send , IPC_CREAT | 0664);
	idRecieve = msgget( key_recieve , IPC_CREAT | 0664);
	//Creo i processi tramite 4 fork
	for(i=0;i<4;i++){
		pid = fork();
		if(pid==0){//figlio
			if(i<3){
				//exec CLIENT			
			}else{
				//exec SERVER			
			}
		}
	}
	//se uscito dal for sono il padre perche nell'exec viene sostituito tutto il codice mentre se sono fuori dal for

	
	for(i=0; i<3; i++)
	

}
