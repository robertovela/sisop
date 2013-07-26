//funzione padre

#include "header.h"

int main(){
	int pid,status,i,id_sem,id_var;
	key_t sem_chiave = ftok(FTOK_SEM_PATH,FTOK_SEM_ID);
	key_t var_chiave = ftok(FTOK_VAR_PATH,FTOK_VAR_ID);
	id_sem = semget(sem_chiave,2,IPC_CREAT|0664);
	semctl(id_sem,APPELLO,SETVAL,1);
	semctl(id_sem,PRENOTATI,SETVAL,1);
	id_var = shmget(var_chiave,sizeof(char*)+sizeof(int),IPC_CREAT|0664);
	for(i=0;i<11;i++){
		pid = fork();		
		if(pid == 0){
			if(i == 0){			
				printf("Creo un docente...\n");
				execlp("./docente",NULL);//docente		
			}
			else{
				printf("Creo uno studente...\n");
				execlp("./studente",NULL);//studente
			}
		}
	}
	for(i=0;i<11;i++){
		pid = wait(&status);
	}
	return 0;
}
