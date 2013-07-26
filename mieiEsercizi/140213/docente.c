//funzione docente

#include "header.h"
void aggiorna_data(int id_sem,variabile * var,char * data){
	Wait_Sem(id_sem,APPELLO);
	var->dataProssimoAppello = data;
	Signal_Sem(id_sem,APPELLO);	
	sleep(3);
	Wait_Sem(id_sem,PRENOTATI);
	printf("<%d> Numero prenotati prima dell'azzeramento: %d\n",getpid(),(var->numPrenotati));
	var->numPrenotati = 0;	
	Signal_Sem(id_sem,PRENOTATI);
	
}

int main(){
	int i,id_sem,id_var;
	variabile* var;
	key_t sem_chiave = ftok(FTOK_SEM_PATH,FTOK_SEM_ID);
	key_t var_chiave = ftok(FTOK_VAR_PATH,FTOK_VAR_ID);
	id_sem = semget(sem_chiave,2,IPC_CREAT|0664);
	id_var = shmget(var_chiave,sizeof(char*)+sizeof(int),IPC_CREAT|0664);
	var = (variabile*) (shmat(id_var,0,0));
	var->dataProssimoAppello = "00/00/0000";
	printf("<%d> Sono il docente! Ho inizializzato la stringa a %s\n",getpid(),var->dataProssimoAppello);
	aggiorna_data(id_sem,var,"05/07/2013");
	aggiorna_data(id_sem,var,"17/07/2013");
	aggiorna_data(id_sem,var,"01/08/2013");
	return 0;
}


