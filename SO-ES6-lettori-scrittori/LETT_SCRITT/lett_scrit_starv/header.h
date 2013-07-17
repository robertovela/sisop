			/*----------HEADER FILE---------*/


#define DIM 16
#define NUM_VOLTE 3
#define SYNCH 0 //lettori e scrittori non possono accedere contemporaneamente alla risorsa
#define MUTEXS 1 //mutua esclusione variabile num scrittori
#define MUTEXL 2 //mutua esclusione variabile num lettori
#define MUTEX  3 //mutua esclusione fra gli scrittori

typedef long msg;

            
typedef struct {
 	  	 int numlettori;
 	  	 int numscrittori;
 	  	 msg messaggio;
} Buffer;



void Wait_Sem(int, int );   
void Signal_Sem (int, int );
void InizioLettura (int, Buffer*);
void FineLettura(int, Buffer*);
void InizioScrittura(int, Buffer*);
void FineScrittura(int, Buffer*);
void Lettore(int, Buffer*);
void Scrittore(int, Buffer*);
