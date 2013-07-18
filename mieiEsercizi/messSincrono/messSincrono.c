#include "header.h"

int main(){
	int k,status,queue;
	pid_t pid;
	queue=msgget(IPC_PRIVATE,IPC_CREAT|0664);
	inizializza();
	
	pid = fork();
	if(pid == 0){
		printf("sono il produttore. Il mio pid e' %d \n",getpid());
		sleep(1);
		produttore(queue,"ciao bello!");
		_exit(0);	
	}
	else {
		pid = fork();
		if(pid == 0){
			printf("sono il figlio consumatore. Il mio pid e' %d",getpid());
			sleep(1);
			consumatore(queue);
			_exit(0);
		}	
	}
	

	for(k=0;k<2;
	distruggi();
}
