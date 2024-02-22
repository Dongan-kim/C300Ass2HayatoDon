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

static List *list_for_out;
static pthread_t send_thread;
struct addrinfo *sin_Remote_addr; // who you send to

// Ctor for sender
void *Sender(void *unused)
{
	while (1)
	{
		Writer_signal(); // wait for the signal
		int socket_container = Manager_Getsocket();
		char *msg = List_first(list_for_out);
		int msgLength = strlen(msg);

		if (sendto(socket_container, msg, msgLength + 1, 0, sin_Remote_addr->ai_addr, sin_Remote_addr->ai_addrlen) == -1)
		{
			printf("send.c: Error detected. Sending message failed.n");
		}

		if (*(msg) == '!')
		{
			// If user type '!' it will be shutdown
			Manager_shutdown();
		}
		else
		{
			free(msg);
			Manager_remove(list_for_out);
		}
	}
}

// sender init function
void Sender_init(List *list, struct addrinfo **remote_addr)
{
	list_for_out = list;
	sin_Remote_addr = *remote_addr;
	pthread_create(&send_thread,
				   NULL,   // Attributes (its almost always NULL)
				   Sender, // Function
				   NULL);  // Arguments
}

// free sender
void Sender_shutdown(void)
{
	pthread_cancel(send_thread);
	pthread_join(send_thread, NULL);
	free(sin_Remote_addr);
}