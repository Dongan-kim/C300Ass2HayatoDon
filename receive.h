#ifndef RECEIVE_H
#define RECEIVE_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "boss.h"
#include "list.h"
#include "receive.h"

void* Receiver(void* unused);
void Receiver_signal(void);
void Receiver_free(void* msg);
void Receiver_init(List* list);
void Receiver_shutdown(void);

#endif