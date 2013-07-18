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

#define VUOTO 2
#define PIENO 3
#define IN_USO 4
#define MUTEXP 0
#define MUTEXC 1
#define PROD 0
#define CONS 1
#define DIM 4
#define NUM_PROD 1
#define NUM_CONS 1

typedef long msg;

void init_stato(int *); //imposta tutti gli elementi del buffer a VUOTO
int RichiestaP (int*,int,int); //wait sui produttori, cerca l'indice del primo VUOTO e lo ritorna, setta stato=IN_USO
void Produzione(int,msg,msg *); //scrive nel buffer
void RilascioP (int,int*,int); //sblocca un consumatore, setta la casella=PIENO
int RichiestaC (int*,int,int);
msg Consumo(int,msg *);
void RilascioC(int,int*,int);

void Wait_Sem(int, int );
void Signal_Sem (int, int );

void Produttore(msg *,int *,int,int);
void Consumatore(msg *,int *,int,int);

#endif
