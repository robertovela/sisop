#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(){
	//Funzione di sistema che pulisce la console 
	system("clear");
	char stringa[256],*token,*programma[256];
	int uscita = 1;//Variabile utile all'uscita dalla simulazione della shell
	int i,pid;
	printf("------------------ SIMULZIONE SHELL MAURIZIO --------------------------\n");
	printf("------------------ PID SHELL SIMULATA %d ----------------------------\n",getpid());
	printf("-----------------------------------------------------------------------\n");
	while(uscita == 1){
			printf("MyComandLine >> ");
			gets(stringa);//Catturo la stringa di caratteri con spazi
			if (strcmp(stringa,"exit")==0) uscita=0;//Verifica la condizione di uscita
			else{			
				//Utile per ricominciare a riempire il vettore dalla posizione iniziale				
				i=0;
				//Utilizzo la funzione strtok per spezzare in base ai caratteri spazio e 					// \n la stringa precedentemente inserita, cosi da evidenziare i 					// paramentri				
				token = strtok(stringa," \n");		 
				while(token != NULL){
							//Copio nella stringa programma i puntatori della stringa precedentemente 								// analizzata senza delimitatori
							programma[i] = token;
							//Scrivendo in questo modo strtok il puntatore token passa alla prossima 								// sottostringa dopo il delimitatore
							token = strtok (NULL," \n");
                					i++;
             					}		
             			programma[i]=NULL;
				pid = fork();
				if (pid == -1) printf("ERRORE NELLA CREAZIONE DEL PROCESSO \n");
				if (pid == 0){
						//Con programma[0] passo a execvp il nome del programma, mentre con programma tutti i 							//paramentri necessari alla sua esecuzione
						execvp(programma[0], programma);
						perror("COMANDO NON TROVATO");
						_exit(0);
					}
				if (pid > 0) {
						wait((int)&pid);
					}
				}
			}		
	return 0;
}
