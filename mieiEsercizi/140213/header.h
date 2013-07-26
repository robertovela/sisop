#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

#define FTOK_SEM_PATH "."
#define FTOK_SEM_ID 'a'
#define FTOK_VAR_PATH "."
#define FTOK_VAR_ID 'b'
#define PRENOTATI 1
#define APPELLO 0

typedef struct{
	char * dataProssimoAppello;
	int numPrenotati;
} variabile;



void Wait_Sem(int,int);
void Signal_Sem(int,int);


#endif
