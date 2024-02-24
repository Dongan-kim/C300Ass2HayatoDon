#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include "manager.h"
#include "receive.h"
#include "send.h"
#include "write.h"
#include "read.h"
#include "list.h"

int remote_port; // for the other person or machine or whatever it is
int local_port;	 // your own port
struct sockaddr_in remote_ip;

int main(int argc, char *argv[])
{
	// Argument for running program will be
	// ./s-talk (local port) (remote ip address) (remote port)

	if (argc != 4)
	{
		printf("Incorrect arguments: check: ./s-talk (user listening port) (remote ip address) (remote port)\n");
		return -1;
	}
	printf("Welcome to s-talk\nStart typing to chat\nType '!' to exit program\n\n");

	local_port = atoi(argv[1]);

	struct addrinfo *remoteAddress;
	// struct addrinfo *current;

	int addr_check;
	struct addrinfo hint;
	memset(&hint, 0, sizeof(struct addrinfo));

	addr_check = getaddrinfo(argv[2], argv[3], &hint, &remoteAddress);
	if (addr_check != 0)
	{
		printf("Remote ip address you input is invalid\nExiting program\n");
		return -1;
	}

	// list for receiving
	List *in = List_create();
	// list for sending
	List *out = List_create();

	if (in == NULL || out == NULL)
	{
		printf("main.c: Error detected, assigning in/out list Failed\nExiting program\n");
		return -1;
	}

	Manager_add_port(local_port); // Add locla port

	// Pass the out list to threads that want to use them
	Writer_init(out);
	Sender_init(out, &remoteAddress);

	// Pass the in list to threads that want to use them
	Receiver_init(in);
	Reader_init(in);

	// will be called when exiting the program.
	Manager_exit();

	return 0;
}