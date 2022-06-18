#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT    8000
#define BACKLOG 32

void createSocket(int fd);
void configureServerSocket(int fd, struct sock_addr_in stct);
void configureClientSocket(int fd, struct sock_addr_in stct, char *ip_addr);
void setSocketToListen(int fd);
void connectSocket(int fd, struct sock_addr_in stct);

struct sock_addr_in {
	short sin_family; //ejemplo AF_INET
	unsigned short sin_port; //ejemplo htons(3490)
	struct in_addr sin_addr; //Ver estructura abajo
	char sin_zero[8] //ceros.
};

struct in_addr {
	unsigned long s_addr; //Cargar con inet_aton()
};