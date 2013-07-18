#include "header.h"

void inizio_scrittura(buffer * buf,int mutex){	
	wait_sem(mutex,MUTEX_S);//!!!!	
	buf->num_scrittori++;
	if(buf->num_scrittori == 1) //controllare se necessario
		wait_sem(mutex,SYNCH);
	signal_sem(mutex,MUTEX_S);
	wait_sem(mutex,MUTEX);
}
void fine_scrittura(buffer * buf,int mutex){
	signal_sem(mutex,MUTEX);
	wait_sem(mutex,MUTEX_S);
	buf->num_scrittori--;
	if(buf->num_scrittori == 0)
		signal_sem(mutex,SYNCH);
	signal_sem(mutex,MUTEX_S);
}
void inizio_lettura(buffer * buf,int mutex){
	wait_sem(mutex,MUTEX_L);
	buf->num_lettori++;
	signal_sem(mutex,MUTEX_L);
	wait_sem(mutex,SYNCH);
}
void fine_lettura(buffer * buf,int mutex){
	signal_sem(mutex,SYNCH);	
	wait_sem(mutex,MUTEX_L);	
	buf->num_lettori--;	
	signal_sem(mutex,MUTEX_L);
}

void wait_sem(int id_sem,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -1;
	semop(id_sem,&sem_buf,1); //vedere unsigned nsops che fa
}
void signal_sem(int id_sem,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 1;
	semop(id_sem,&sem_buf,1);
}
