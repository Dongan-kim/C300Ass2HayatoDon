#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "manager.h"
#include "list.h"
#include "receive.h"
#include "read.h"

List* list_for_in;
static pthread_t read_thread;

void* Reader(void* unused){
	while(1){
		Receiver_signal();
		const char* intro = "[Message]: ";
		char* msg = List_first(list_for_in);
		fputs(intro, stdout);
		fputs(msg, stdout);
		fflush(stdout);
		if (*(msg) == 'S' && *(msg + 2) == '\0') {
			// If user type 'S' it will be shutdown
			Manager_shutdown();
		}else {
			free(msg);
			Manager_remove(list_for_in);
		}
	}
}

void Reader_init(List* list){
	list_for_in = list;
	pthread_create(&read_thread, NULL, Reader, NULL);
}

void Reader_shutdown(void) {
	pthread_cancel(read_thread);
	pthread_join(read_thread, NULL);
}