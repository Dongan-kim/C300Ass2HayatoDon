#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "manager.h"
#include "list.h"
#include "receive.h"
#include "send.h"
#include "write.h"
#include "read.h"

// Manager deals with nodes creation/deletion/management
// so this is a manager class that can be used from anywhere in the program to deal with logistics such as initiating/closing the program.

static pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t port_mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t node_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t node_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t remove_mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t main_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t main_mutex = PTHREAD_MUTEX_INITIALIZER;

bool socketFlag;
int local_port;

struct sockaddr_in sinNew; // Socket for localhost
int socket_container;	   // Socket container for threads to use

// Registering port
void Manager_add_port(int x)
{
	local_port = x;
}

// Managers binding sockets to send/receive message through UDP
int Manager_Getsocket()
{
	pthread_mutex_lock(&port_mutex);
	{
		if (!socketFlag)
		{
			socket_container = socket(PF_INET, SOCK_DGRAM, 0);

			memset(&sinNew, 0, sizeof(sinNew));
			sinNew.sin_addr.s_addr = htonl(INADDR_ANY);
			sinNew.sin_port = htons(local_port);

			if (bind(socket_container, (struct sockaddr *)&sinNew, sizeof(sinNew)) < 0)
			{
				printf("manager.c: Error detected: Binding socket failed.\n");
				Manager_shutdown();
			}
			socketFlag = 1;
		}
	}
	pthread_mutex_unlock(&port_mutex);
	return socket_container;
}

// The function monitors if no more than one thread is trying to access a pool of nodes
int Manager_append(List *list, void *item)
{
	int result = 0;
	pthread_mutex_lock(&list_mutex);
	{
		if (List_append(list, item) == -1)
		{
			result = -1;
		}
	}
	pthread_mutex_unlock(&list_mutex);

	return result;
}

// Threads needs to wait until a free node is available
void Manager_wait(void)
{
	pthread_mutex_lock(&node_mutex);
	{
		pthread_cond_wait(&node_cond, &node_mutex);
	}
	pthread_mutex_unlock(&node_mutex);
}

// Deals with removing nodes. therefore another responsibility of this function is to signal free node
void Manager_remove(List *list)
{
	pthread_mutex_lock(&remove_mutex);
	{
		List_remove(list);
		pthread_cond_signal(&node_cond);
	}
	pthread_mutex_unlock(&remove_mutex);
}

// send signals to finish the program
void Manager_shutdown(void)
{
	pthread_mutex_lock(&main_mutex);
	{
		pthread_cond_signal(&main_cond);
	}
	pthread_mutex_unlock(&main_mutex);
}

// Deals with finishing/terminating the program
void Manager_exit(void)
{
	pthread_mutex_lock(&main_mutex);
	{
		pthread_cond_wait(&main_cond, &main_mutex);
	}
	pthread_mutex_unlock(&main_mutex);

	printf("S-talk progarm exiting\n");
	Sender_shutdown();
	Reader_shutdown();
	Writer_shutdown();
	Receiver_shutdown();
	pthread_mutex_destroy(&main_mutex);
	pthread_mutex_destroy(&list_mutex);
	pthread_mutex_destroy(&port_mutex);
	pthread_mutex_destroy(&node_mutex);
	pthread_mutex_destroy(&remove_mutex);
	pthread_cond_destroy(&main_cond);
	pthread_cond_destroy(&node_cond);
}