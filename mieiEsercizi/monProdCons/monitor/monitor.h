/** Prototipi delle funzioni per la realizzazione del monitor (paradigma signal and return)*/

typedef struct{
	int mutex;
	int num_var_cond;
	int id_conds; //id del gruppo di semafori associato alle var cond.
	int *cond_counts; //numeri di elementi in coda alle var_cond
	int id_shared; //identificativo di memoria condivisa
} Monitor;


void init_monitor(Monitor *,int); //passo il monitor e numero di variabili condition
void enter_monitor(Monitor *);
void leave_monitor(Monitor *);
void remove_monitor(Monitor *);
void wait_condition(Monitor *,int); //passo il monitor e l'id della variabile condition da modificare
void signal_condition(Monitor *,int);

