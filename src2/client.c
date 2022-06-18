#include "defs.h"

int main(){
    int client_fd;
    int r;
    struct sock_addr_in server;
    char buffer[200];

    //Rutinas de inicialización socket cliente.
    createSocket(client_fd);
    configureClientSocket(client_fd, server, "192.168.0.4");
    connectSocket(client_fd, server);

    //Recibir mensaje del servidor.
    r = recv(client_fd, buffer, 10, 0);
	if (r < 0){
		perror("Error en recv");
		exit(-1);
	}

	//Imprime el mensaje recibido en buffer.
	buffer[r] = 0;
	printf("\n Mensaje: %s", buffer);
	
	//Cierra conexión.
	close(client_fd);
    return 0;
}