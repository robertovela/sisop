/*
	shellRoberto.c
	programma di simulazione BASH
	Roberto Vela
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]){
	char *host,*pwd,*user,*command,*pch;
	char input[50];
	char *argomenti[20]; //vettore di puntatori alle stringhe
	int pid,st,i;
	user = getenv("USER");
	host = getenv("HOSTNAME");
	pwd = getenv("PWD");
	while(1){
		printf("%s@%s %s $ ",user,host,pwd);
		gets(input); //prende gli spazi
		if(!strcmp(input,"exit"))
			exit(0);
		command = input; //provvisorio
		pid = fork();
		if(pid == -1){
			fprintf(stderr,"fork() fallita!\n");
			return -1;
		}
		if(pid == 0){
			//printf("sono il figlio\n");
			//command = strtok(input," ");
			//execl("/bin/ls","ls",NULL);
			pch = strtok(input," \n");
			i=0;
			while(pch != NULL){
				pch=strtok(NULL," \n");
				argomenti[i]=pch;
				i++;
			}
			argomenti[i]=NULL;
			execvp(argomenti[0],argomenti);
			//execlp(command,"",(char*)NULL);
			fprintf(stderr,"exec fallita!");
			//execlp(command,(char*)0);
		}
		if(pid > 0){
			//printf("sono il papa'\n");
			wait(&st);
		}
	}
	return 0;
}
