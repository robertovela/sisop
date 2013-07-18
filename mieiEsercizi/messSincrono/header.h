#ifndef HEADER_H
#define HEADER_H

#define REQUEST_TO_SEND 0
#define OK_TO_SEND 1
#define MESSAGGIO 2

#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

typedef struct {
	long tipo;
	char msg[40];
} messaggio;

#endif
