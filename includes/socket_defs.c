#include "socket_defs.h"


void createSocket(int fd){
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!fd){
        perror("Error al crear socket");
        exit(-1);
    }
}


void configureServerSocket(int fd, struct sock_addr_in stct){
    
    int r;

    //Configuración de dirección del socket servidor.
	stct.sin_family = AF_INET;
	stct.sin_port = htons(PORT);
	stct.sin_addr.s_addr = INADDR_ANY; //Cualquier dirección.
	bzero(stct.sin_zero,8); //Llenar los ceros.

    r = bind(fd, (struct sockaddr*) &stct, sizeof(struct sockaddr));
	if (r < 0){
		perror("Error en bind");
		exit(-1);
	}
}


void configureClientSocket(int fd, struct sock_addr_in stct, char *ip_addr){

    stct.sin_family = AF_INET;
	//Conexión con el servidor.
	stct.sin_port = htons(PORT);
	inet_aton(ip_addr, &stct.sin_addr);
	//Convierte la dirección a binario y la asigna al atributo del struct.
}


void setSocketToListen(int fd){
    
    int r;

    //Se establece como socket pasivo.
	r = listen(fd, BACKLOG);
	if (r < 0){
		perror("Error en listen");
		exit(-1);
	}
}


void connectSocket(int fd, struct sock_addr_in stct){
    
    int r;

    r = connect(fd, (struct sockaddr*)&stct, (socklen_t) sizeof(struct sockaddr));
	if (r < 0){
		perror("Error en connect");
		exit(-1);
	}
}