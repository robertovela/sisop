#include "header.h"

void init_stato(int * stato){
	int i;
	for(i=0;i<DIM;i++)
		stato[i]=VUOTO;
}

int RichiestaP (int*stato,int sem, int mutex){ //Richiesta di produzione. Ritorna l'indice del valore da produrre
	int i=0;
	Wait_Sem(sem,PROD);
	Wait_Sem(mutex,MUTEXP); //dove faccio questa signal?
	while(stato[i] != VUOTO)
		i++;	
	stato[i] = IN_USO;
	Signal_Sem(mutex,MUTEXP); //??
	return i;
}

void Produzione(int indice,msg messaggio,msg *buffer){
	buffer[indice] = messaggio;
}

void RilascioP(int indice,int*stato,int sem){
	stato[indice] = PIENO;
	Signal_Sem(sem,CONS); //avendo prodotto il dato, un consumatore può prenderlo
}

int RichiestaC(int*stato,int sem, int mutex){
	int i=0;
	Wait_Sem(sem,CONS);
	Wait_Sem(mutex,MUTEXC);
	while(stato[i] != PIENO)
		i++;
	stato[i] = IN_USO;
	Signal_Sem(mutex,MUTEXC); //??
	return i;
}

msg Consumo(int indice,msg * buffer){
	msg messaggio = buffer[indice];
	return messaggio;
}

void RilascioC(int indice,int*stato,int sem){
	stato[indice] = VUOTO;
	Signal_Sem(sem,PROD);

}


void Wait_Sem(int id_sem, int numsem){
	printf("Sono entrato nella wait pid= %d \n",getpid());
	struct sembuf sem_buf;
        sem_buf.sem_num=numsem; 
        sem_buf.sem_flg=0; //cosa sei??
        sem_buf.sem_op=-1; //operazione di wait?
        semop(id_sem,&sem_buf,1);   //semaforo rosso
	printf("Sto uscendo dalla wait.. pid= %d \n",getpid());
}

void Signal_Sem (int id_sem, int numsem){
	struct sembuf sem_buf;
        sem_buf.sem_num=numsem; 
        sem_buf.sem_flg=0; //cosa sei??
        sem_buf.sem_op=1; //operazione di signal?
        semop(id_sem,&sem_buf,1);   //semaforo rosso
}

void Produttore(msg * ptr_sh,int * stato,int sem,int mutex){ 
	msg val;
	int indice;	
	struct timeval t1;
    	struct timezone t2;
    	gettimeofday(&t1,&t2);
    	val=t1.tv_usec;	
	indice = RichiestaP(stato,sem,mutex); 
	Produzione(indice,val,ptr_sh); 
	RilascioP (indice,stato,sem);
	/*éprintf("Faccio la wait su SPAZIO_DISP pid= %d \n",getpid());
	Wait_Sem(mutex,SPAZIO_DISP);
	printf("Ora lo spazio e' disp pid= %d \n",getpid());
	*ptr_sh = val;//produzione
	printf("Figlio %d ha prodotto %ld. Valore semaforo SPAZIO_DISP = %d \n",getpid(),*ptr_sh,semctl(mutex,SPAZIO_DISP,GETVAL));
	printf("Faccio la signal su MSG_DISP pid= %d \n",getpid());
	Signal_Sem(mutex,MSG_DISP);//signal messaggio disponibile*/
}

void Consumatore(msg * ptr_sh,int * stato,int sem,int mutex){
	msg val;
	int indice;
	indice = RichiestaC(stato,sem,mutex);
	val = Consumo(indice,ptr_sh);
	RilascioC(indice,stato,sem);	
	/*printf("Faccio la wait su MSG_DISP pid= %d \n",getpid());
	Wait_Sem(mutex,MSG_DISP);//wait messaggio disponibile
	val = *ptr_sh;//consumo
	*ptr_sh = 0;
	printf("Figlio %d ha consumato %ld. Valore semaforo MSG_DISP = %d \n",getpid(),val,semctl(mutex,MSG_DISP,GETVAL));
	printf("Faccio la signal su SPAZIO_DISP pid= %d \n",getpid());
	Signal_Sem(mutex,SPAZIO_DISP);//signal spazio disponibile*/
}
