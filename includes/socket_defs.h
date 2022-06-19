#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

#define PORT    8000
#define BACKLOG 32

struct sock_addr_in {
	short sin_family; //ejemplo AF_INET
	unsigned short sin_port; //ejemplo htons(3490)
	struct in_addr sin_addr; //Ver estructura abajo
	char sin_zero[8]; //ceros.
};

int createSocket(int fd);
int configureServerSocket(int fd, struct sock_addr_in *addr);
void configureClientSocket(struct sock_addr_in *addr, char *ip_addr);
int setSocketToListen(int fd);
int connectSocket(int fd, struct sock_addr_in *addr);