#ifndef ESAME 
#define ESAME
#define FTOK_QUEUE_SEND_PATH "."
#define FTOK_QUEUE_SEND_ID 'a'
#define FTOK_QUEUE_RECEIVE_PATH "."
#define FTOK_QUEUE_RECEIVE_ID 'b'
#define N 3
#include <sys/types.h>

//come si usa msgsnd?

typedef struct{
	long type;
	pid_t pid;
	int op1;
	int op2;

} Messaggio;

typedef struct{
	long type;
	int result;
} Risposta;

typedef struct{
	Messaggio msgBuf[N];
	pthread_mutex_t mutex;
	pthread_cond_t okProd;
	pthread_cond_t okCons;
	int testa;
	int coda;

} Buffer;

#endif
