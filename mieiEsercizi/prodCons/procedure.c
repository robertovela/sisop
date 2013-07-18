#include "header.h"

void Wait_Sem(int id_sem, int numsem){
	printf("Sono entrato nella wait\n");
	struct sembuf sem_buf;
        sem_buf.sem_num=numsem; 
        sem_buf.sem_flg=0; //cosa sei??
        sem_buf.sem_op=-1; //operazione di wait?
        semop(id_sem,&sem_buf,1);   //semaforo rosso
	printf("Sto uscendo dalla wait..\n");
}

void Signal_Sem (int id_sem, int numsem){
	struct sembuf sem_buf;
        sem_buf.sem_num=numsem; 
        sem_buf.sem_flg=0; //cosa sei??
        sem_buf.sem_op=1; //operazione di signal?
        semop(id_sem,&sem_buf,1);   //semaforo rosso
}

void Produttore(long * ptr_sh,int mutex){ //cosa cambia fra long* ptr e long *ptr in c???
	long val;	
	struct timeval t1;
    	struct timezone t2;
    	gettimeofday(&t1,&t2);
    	val=t1.tv_usec;	
	printf("Faccio la wait su SPAZIO_DISP\n");
	Wait_Sem(mutex,SPAZIO_DISP);
	printf("Ora lo spazio e' disp\n");
	*ptr_sh = val;//produzione
	printf("Figlio %d ha prodotto %ld. Valore semaforo SPAZIO_DISP = %d \n",getpid(),*ptr_sh,semctl(mutex,SPAZIO_DISP,GETVAL));
	Signal_Sem(mutex,MSG_DISP);//signal messaggio disponibile
}

void Consumatore(long * ptr_sh,int mutex){
	long mess;	
	Wait_Sem(mutex,MSG_DISP);//wait messaggio disponibile
	mess = *ptr_sh;//consumo
	*ptr_sh = 0;
	printf("Figlio %d ha consumato %ld. Valore semaforo MSG_DISP = %d \n",getpid(),mess,semctl(mutex,MSG_DISP,GETVAL));
	Signal_Sem(mutex,SPAZIO_DISP);//signal spazio disponibile
}
