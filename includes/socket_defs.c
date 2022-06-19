#include "socket_defs.h"

int createSocket(int fd){
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!fd){
        perror("Error al crear socket");
        exit(-1);
    }
	return fd;
}


int configureServerSocket(int fd, struct sock_addr_in *addr){
    
    int r;
	int option = 1;
	
	r = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
	if (r < 0){
		perror("Error en setsockopt");
		exit(-1);
	}

    //Configuración de dirección del socket servidor.
	(*addr).sin_family = AF_INET;
	(*addr).sin_port = htons(PORT);
	(*addr).sin_addr.s_addr = INADDR_ANY; //Cualquier dirección.
	bzero((*addr).sin_zero,8); //Llenar los ceros.

    r = bind(fd, (struct sockaddr*) addr, sizeof(*addr));
	if (r < 0){
		perror("Error en bind");
		exit(-1);
	}

	return fd;
}


void configureClientSocket(struct sock_addr_in *addr, char *ip_addr){

    (*addr).sin_family = AF_INET;
	//Conexión con el servidor.
	(*addr).sin_port = htons(PORT);
	inet_pton(AF_INET, ip_addr, &(*addr).sin_addr);
	//Convierte la dirección a binario y la asigna al atributo del struct.
}


int setSocketToListen(int fd){
    
    int r;

    //Se establece como socket pasivo.
	r = listen(fd, BACKLOG);
	if (r < 0){
		perror("Error en listen");
		exit(-1);
	}

	return fd;
}


int connectSocket(int fd, struct sock_addr_in *addr){
    
    int r;

    r = connect(fd, (struct sockaddr*)addr, sizeof(*addr));
	if (r < 0){
		perror("Error en connect");
		exit(-1);
	}

	return fd;
}