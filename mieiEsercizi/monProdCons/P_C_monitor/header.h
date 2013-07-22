#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include "../monitor/monitor.h"

enum VAR_CONDITIONS {OK_PRODUZIONE,OK_CONSUMO};

typedef long msg;

typedef struct{
	int ok_produzione;
	int ok_consumo;
} cond;

#define NUM_CONDITIONS	2 //numero di var cond da dare nell'init del monitor

void Consumatore(Monitor *,cond *,msg *);
void Produttore(Monitor *,cond *,msg *);

void InizioConsumo(Monitor *,cond *); 
void FineConsumo(Monitor *,cond *);
void InizioProduzione(Monitor *,cond *);
void FineProduzione(Monitor *,cond *);

