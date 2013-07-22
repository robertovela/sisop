#include "header.h"

int main(){
	int id_shared;
	msg* mess;
	key_t chiave;
	cond* conditions;
	Monitor mio_Monitor;
	id_shared = semget(chiave,sizeof(cond)+sizeof(msg),IPC_CREAT|0664);
	mess=(msg*) (shmat(id_shared,0,0));
	conditions = (cond*) (mess+1); //??
	conditions -> ok_produzione = 1;
	conditions -> ok_consumo = 0;
	init_monitor(&mio_Monitor,NUM_CONDITIONS);
	return 1;
}
