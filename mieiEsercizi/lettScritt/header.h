#ifndef HEADER_H
#define HEADER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h> // vedere che fa
#include <stdio.h>
#include <stdlib.h> // vedere

#define MUTEX 	0 //mutua esclusione da parte degli scrittori
#define MUTEX_S 1 //mutex num_scrittori
#define MUTEX_L 2 //mutex num_lettori
#define SYNCH	3 //mutua esclusione fra scrittori/lettori
#define NUMLET 1
#define NUMSCRIT 1


typedef struct {	
	int msg;
	int num_lettori;
	int num_scrittori;
} buffer;


void inizio_scrittura(buffer *,int);
void fine_scrittura(buffer *,int);
void inizio_lettura(buffer *,int);
void fine_scrittura(buffer *,int);

void wait_sem(int,int);
void signal_sem(int,int);


#endif
