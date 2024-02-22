#ifndef READ_H
#define READ_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "manager.h"
#include "list.h"
#include "receive.h"
#include "read.h"

void* Reader(void* unused);
void Reader_init(List* list);
void Reader_shutdown(void);

#endif