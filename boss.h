#ifndef BOSS_H
#define BOSS_H
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "list.h"
#include "receive.h"
#include "send.h"
#include "write.h"
#include "read.h"

void Boss_addLocalPort(int x);
int Manager_Getsocket();
int Manager_append(List* list, void* item);
void Manager_wait(void);
void Manager_remove(List* list);
void Manager_shutdown(void);
void Boss_exitSignal(void);

#endif