#ifndef WRITE_H
#define WRITE_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "boss.h"
#include "write.h"
#include "list.h"

void* Writer(void* unused);
void Writer_init(List* list);
void Writer_signal(void);
void Writer_free(void* msg);
void Writer_shutdown(void);

#endif