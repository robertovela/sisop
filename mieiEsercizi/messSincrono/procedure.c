#include "header.h"

static int queue1,queue2;

void inizializza(){
	queue1 = msgget(IPC_PRIVATE,IPC_CREAT | 0664);
	queue2 = msgget(IPC_PRIVATE,IPC_CREAT | 0664);
}

void destroy(){
	msgctl(queue1,IPC_RMID,0);
	msgctl(queue2,IPC_RMID,0);
}

void invia(messaggio *m,int queue){
	messaggio m1,m2;
	m1.tipo = REQUEST_TO_SEND;
	strcpy(m1.msg,"Richiesta di invio");
	msgsnd(&queue1,&m1,sizeof(messaggio)-sizeof(long),0); //REQUEST_TO_SEND - l'ultimo par può essere 0 o IPC_NOWAIT
	msgrcv(&queue2,&m2,sizeof(messaggio)-sizeof(long),OK_TO_SEND,0); 
	
	m->tipo=MESSAGGIO;

	msgsnd(queue,m,sizeof(messaggio)-sizeof(long),0);
}

void ricevi(char *testo,int queue){
	messaggio m1,m2;
	msgrcv(&queue1,&m1,sizeof(messaggio)-sizeof(long),REQUEST_TO_SEND,0);
	m2.tipo = OK_TO_SEND;
	strcpy(m1.msg,"Richiesta invio ricevuta");
	msgsnd(&queue2,&m2,sizeof(messaggio)-sizeof(long),0);
	msgrcv(queue,m,sizeof(messaggio)-sizeof(long),MESSAGGIO,0);

}

void produttore(int queue,char* testo){
	messaggio m;
	m.tipo = MESSAGGIO;
	strcpy(m.msg,testo);
	invia(m,queue);

}
