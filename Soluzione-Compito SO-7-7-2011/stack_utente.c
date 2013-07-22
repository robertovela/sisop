#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void *Inserisci(void * s)
{

	int i;
	Elem v;

	for(i=0; i<4; i++) {
		v = rand() % 11;
		StackPush(s, v);
		printf("Inserimento: %d\n", v);
		sleep(1);
	}

	pthread_exit(NULL);
}


void *Preleva(void * s)
{

	int i;
	Elem v1, v2;

	for(i=0; i<10; i++) {
		v1=StackPop(s);
		printf("Prelievo: %d\n", v1);

		v2=StackPop(s);
		printf("Prelievo: %d\n", v2);

		printf("Somma: %d\n", v1+v2);

		sleep(3);
	}

	pthread_exit(NULL);

}


int main(int argc, char *argv[])
{

	pthread_t threads[6];
	pthread_attr_t attr;
	int rc;
	int i;

	srand(time(NULL));

	Stack * stack = (Stack *)malloc(sizeof(Stack));

	StackInit(stack, 4);



	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	for(i=0; i<5; i++) {
		pthread_create(&threads[i], NULL, Inserisci, (void *)stack);
	}

	pthread_create(&threads[5], NULL, Preleva, (void *)stack);


	for(i=0; i<6; i++) {
		pthread_join(threads[i], NULL);
	}


	StackRemove(stack);

}

