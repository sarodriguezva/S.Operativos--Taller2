#include "defs.h"

int main(){
    int server_fd, client_fd;
    int r;
    struct sock_addr_in server, client;
    socklen_t socklen;

    //Rutinas de inicialización de socket servidor.
    createSocket(server_fd);
    configureServerSocket(server_fd, server);
    setSocketToListen(server_fd);


    //Trae una conexión de la pila como socket.
	client_fd = accept(server_fd, (struct sockaddr*)&client, &socklen);
	if (!client_fd){
		perror("Error al aceptar conexión");
		exit(-1);
	}


	//Envía un mensaje al socket especificado.
	r = send(client_fd, "hola mundo", 10, 0);
	if (r < 0){
		perror("Error en send");
		exit(-1);
	}


	//Cierra conexiones.
	close(client_fd);
	close(server_fd);

    return 0;
}