//funzione studente

#include "header.h"

int main(){
	int i,id_sem,id_var;
	variabile* var;
	key_t sem_chiave = ftok(FTOK_SEM_PATH,FTOK_SEM_ID);
	key_t var_chiave = ftok(FTOK_VAR_PATH,FTOK_VAR_ID);
	id_sem = semget(sem_chiave,2,IPC_CREAT|0664);
	id_var = shmget(var_chiave,sizeof(char*)+sizeof(int),IPC_CREAT|0664);
	var = (variabile*) (shmat(id_var,0,0));
	printf("<%d> Sono lo studente!\n",getpid());
	
	//sleep(rand() % 9);
	sleep(5);
	Wait_Sem(id_sem,APPELLO);
	Wait_Sem(id_sem,PRENOTATI);
	(var->numPrenotati)++;	
	printf("<%d> Mi prenoto per l'appello del: %s. Nuovo numero prenotati: %d\n",getpid(),(var->dataProssimoAppello),(var->numPrenotati));
	Signal_Sem(id_sem,PRENOTATI);
	Signal_Sem(id_sem,APPELLO);
	return 0;
}
