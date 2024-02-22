#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "boss.h"
#include "write.h"
#include "list.h"

List* list_for_out;
//Synchronization
static pthread_cond_t condVar_out = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex_out = PTHREAD_MUTEX_INITIALIZER;
static pthread_t write_thread;

void* Writer(void* unused) {
	while(1) {
		char buffer[1024];
		fgets(buffer, 1024, stdin);
		int receiveLength = strlen(buffer);

	while(1) {
		char* msg = (char*)malloc(receiveLength + 1);
		strcpy(msg, buffer);
		if (Manager_append(list_for_out, msg) == -1) {
			printf("Error: Message could't be added to the list\n");
			free(msg); 
			Manager_wait();
		}else {
			pthread_mutex_lock(&mutex_out);
			{
				pthread_cond_signal(&condVar_out);
			}
			pthread_mutex_unlock(&mutex_out);
			break;
		}
    }
	}
	return NULL;
}

void Writer_init(List* list){
	list_for_out = list;
	pthread_t write_thread;
	pthread_create(&write_thread, NULL, Writer, NULL);
}

//send_thread waits until it is signaled
void Writer_signal(void) {
	pthread_mutex_lock(&mutex_out); 
	{
		pthread_cond_wait(&condVar_out, &mutex_out);
	}
	pthread_mutex_unlock(&mutex_out);
}

// if there are still messages left
void Writer_free(void* msg) {
	if (msg) {
		free(msg);
	}
}

void Writer_shutdown(void){
	List_free(list_for_out, &Writer_free);
	pthread_cancel(write_thread);
	pthread_join(write_thread, NULL);
	pthread_mutex_destroy(&mutex_out);
	pthread_cond_destroy(&condVar_out);
}