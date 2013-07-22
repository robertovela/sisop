/* Implementazione del monitor signal and return */

#include "monitor.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

//funzioni di utilità private alla libreria monitor

static void Wait_Sem(int,int);
static void Signal_Sem(int,int);
static int Queue_Sem(int,int); //restituisce il numero di processi in attesa su quel semaforo

/* Implementazioni ----------------------------------------*/

void init_monitor(Monitor *m,int num_var){
	int i;
 	m->num_var_cond = num_var;
	m->mutex = semget(IPC_PRIVATE,1,IPC_CREAT|0664);
	m->id_conds = semget(IPC_PRIVATE,num_var,IPC_CREAT|0664);
	semctl(m->mutex,0,SETVAL,1); //inizializzo il mutex a 1
	for(i=0;i<num_var;i++)
		semctl(m->id_conds,i,SETVAL,0);
	m->id_shared=shmget(IPC_PRIVATE,num_var*sizeof(int),IPC_CREAT|0664);
	m->cond_counts=(int*) (shmat(m->id_shared,0,0));
	for(i=0;i<num_var;i++)
		m->cond_counts[i]=0;
	printf("Monitor inizializzao con %d condition variables! \n",num_var);
}

void enter_monitor(Monitor * m){
	printf("<%d> Tentativo di ingresso nel monitor...\t",getpid());
	Wait_Sem(m->mutex,0);
	printf("<%d> entrato nel monitor.\n",getpid());

}

void leave_monitor(Monitor * m){
	printf("<%d> Uscito dal monitor.\n",getpid());
	Signal_Sem(m->mutex,0);
}


void remove_monitor(Monitor * m){
	int i;	
	semctl(m->mutex,0,IPC_RMID);
	shmctl(m->id_shared,IPC_RMID,0);	
	semctl(m->id_conds,m->num_var_cond,IPC_RMID);
	printf("\n Il monitor e' stato rimosso! Bravissimissimo! \n",getpid());
}


void wait_condition(Monitor * m,int id_var){
	printf("<%d> -Monitor- invocata la wait sulla condition numero %d\n", getpid(), id_var);
	m->cond_counts[id_var] = m->cond_counts[id_var] + 1;
	Signal_Sem(m->mutex,0);
	Wait_Sem(m->id_conds,id_var);
	m->cond_counts[id_var] = m->cond_counts[id_var] + 1;
}


void signal_condition(Monitor * m,int id_var){
	 printf("<%d> -Monitor- tentativo di signal; n.ro proc. in attesa sulla cond. n. %d = %d\n", getpid(), id_var,m->cond_counts[id_var]);	
	if(m->cond_counts[id_var]>0){
		printf("<%d> -Monitor- invocata la signal sulla condition numero %d\n", getpid(), id_var);
		Signal_Sem(m->id_conds,id_var);
	}
	else{
		 printf("<%d> -Monitor- invocata la signal sul mutex \n", getpid());		
		Signal_Sem(m->mutex,0);
	}
}

/* Implementazione delle funzioni semaforiche ---------- */

void Wait_Sem(int id_sem,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flg = 0; //0 oppure IPC_NOWAIT/IPC_UNDO
	sem_buf.sem_op = -1;
	semop(id_sem,&sem_buf,1);
}

void Signal_Sem(int id_sem,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 1;
	semop(id_sem,&sem_buf,1);
}

int Queue_Sem(int id_sem,int numsem){
	return (semctl(id_sem,numsem,GETNCNT,NULL));
}























