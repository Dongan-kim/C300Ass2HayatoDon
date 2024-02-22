#ifndef SEND_H
#define SEND_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "manager.h"
#include "list.h"
#include "send.h"
#include "write.h"

void* Sender(void* unused);
void Sender_init(List* list, struct addrinfo** remote_addr);
void Sender_shutdown(void);

#endif