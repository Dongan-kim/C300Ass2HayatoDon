#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "manager.h"
#include "list.h"
#include "receive.h"
#include "read.h"

List *list_for_in;
static pthread_t read_thread;

// Ctor for Reader includeing setting up message format, specifing terminating logic of the reader
void *Reader(void *unused)
{
	while (1)
	{
		Receiver_signal();
		const char *message_tag = "Message received : ";
		char *msg = List_first(list_for_in);
		fputs(message_tag, stdout);
		fputs(msg, stdout);
		fflush(stdout);
		if (*(msg) == '!')
		{
			// If user type '!' it will be shutdown
			printf("\nThanks for using s-talk! See you soon\n");
			Manager_shutdown();
		}
		else
		{
			free(msg);
			Manager_remove(list_for_in);
		}
	}
}

// Init function for reader
void Reader_init(List *list)
{
	list_for_in = list;
	pthread_create(&read_thread, NULL, Reader, NULL);
}

// terminating function for reader
void Reader_shutdown(void)
{
	pthread_cancel(read_thread);
	pthread_join(read_thread, NULL);
}