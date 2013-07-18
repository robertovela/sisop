#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSG_DISP 0
#define SPAZIO_DISP 1
#define NUM_PROD 1
#define NUM_CONS 1


void Wait_Sem(int, int );
void Signal_Sem (int, int );

void Produttore(long *,int);
void Consumatore(long *,int);

#endif
