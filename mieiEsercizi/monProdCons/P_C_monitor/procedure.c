#include "header.h"

void InizioConsumo(Monitor * m,cond * c){
	printf("<%d> InizioConsumo \n",getpid());	
	enter_monitor(m);
	if (! c->ok_consumo ) wait_condition(m,OK_CONSUMO);
}
void FineConsumo(Monitor * m,cond * c){
	printf("<%d> FineConsumo \n",getpid());
	c->ok_produzione = 1;
	c->ok_consumo = 0;
	signal_condition(m,OK_PRODUZIONE);
	
}
void InizioProduzione(Monitor * m,cond * c){
	printf("<%d> InizioProduzione \n",getpid());
	enter_monitor(m);
	if (! ok->produzione ) wait_condition(m,OK_PRODUZIONE);
}
void FineProduzione(Monitor * m,cond * c){
	printf("<%d> FineProduzione \n",getpid());
	c->ok_produzione = 0;
	c->ok_consumo = 1;
	signal_condition(m,OK_CONSUMO);
}
void Produttore(Monitor * m,cond * c,msg * mess){
	InzioProduzione(m,c);
	struct timeval t1;
	struct timezone t2;
	gettimeofday(&t1,&t2);
	msg val = t1.tv_usec;
	*mess = val;
	printf("<%d> Valore prodotto=%d \n",getpid(),*mess);
	FineProduzione(m,c);	
}

void Consumatore(Monitor * m,cond * c,msg * mess){
	InizioConsumo(m,c);
	printf("<%d> Valore Consumato = <%d> \n",getpid(), *mess);
	*mess = 0;
	FineConsumo(m,c);
}
