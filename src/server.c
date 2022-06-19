//Servidor encargado de gestionar peticiones del cliente con el servicio de búsqueda en otro proceso.

#include "../includes/defs.h"
#include "../includes/socket_defs.h"

void processClient(int client_fd);
void receiveDataFromClient(int client_fd, int *origen, int *destino, int *hora);
double search(int origen, int destino, int hora);
void stop();

int main(){
    int server_fd, client_fd;
    struct sock_addr_in address;
    int addrlen = sizeof(address);

    printf("Inicializando servidor...\n");

    //Rutinas de inicialización de socket servidor.
    server_fd = createSocket(server_fd);
    server_fd = configureServerSocket(server_fd, &address);
    server_fd = setSocketToListen(server_fd);

    printf("Servidor configurado con éxito!...\n");
    printf("Esperando petición de cliente...\n");

    //Trae una conexión de la pila como socket.
	client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	if (!client_fd){
		perror("Error al aceptar conexión");
		exit(-1);
	}

    printf("Conexión con cliente recibida!...\n");

	processClient(client_fd);

    printf("Cerrando servidor...\n");
	//Cierra conexión.
	shutdown(server_fd, SHUT_RDWR);

    return 0;
}

void processClient(int client_fd){

	int origen, destino, hora;
	double tiempo_viaje;

	while (1){
		receiveDataFromClient(client_fd, &origen, &destino, &hora);

		if (origen == -2 && destino == -2 && hora == -2){
			break;
		}

		printf("Datos recibidos por teclado: \n");
		printf("Origen: \t%d\n", origen);
		printf("Destino: \t%d\n", destino);
		printf("Hora: \t\t%d\n\n", hora);

		tiempo_viaje = search(origen, destino, hora);

		send(client_fd, &tiempo_viaje, sizeof(double), 0);
	}

	//Cierra conexión
    printf("Desconectando cliente...\n");
	close(client_fd);
	stop();
    printf("Cliente desconectado!\n");
}

void receiveDataFromClient(int client_fd, int *origen, int *destino, int *hora){

	recv(client_fd, origen, sizeof(int), 0);
	recv(client_fd, destino, sizeof(int), 0);
	recv(client_fd, hora, sizeof(int), 0);
}


/*
Función que envía los datos ingresados por el cliente
al servicio (proceso) de búsqueda en tabla hash.

Comunicación mediante tubería nombrada (FIFO).
Espera a que el servicio regrese el valor requerido y lo retorna.
*/
double search(int origen, int destino, int hora){

    int fd, r;
    double value;

    fd = open(FIFO_FILE, O_RDWR);
    if (!fd){
        perror("Error al abrir tubería en server.c.");
        exit(-1);
    }

    printf("Enviando datos...\n");

    write(fd, &origen, sizeof(int));
    write(fd, &destino, sizeof(int));
    write(fd, &hora, sizeof(int));

    printf("Datos enviados con éxito!\n");

    while(1){
        printf("Esperando respuesta...\n");
        r = read(fd, &value, sizeof(double));

        if (r == -1){
            perror("Error al leer en server.c.");
            exit(-1);
        }else if (r > 0){
            break;
        }
    }

    close(fd);

    return value;
}


/*
Función encargada de gestionar el cierre de cliente y servicio de búsqueda al tiempo.
Para ello, envía valores de cerrado mediante una tubería nombrada (FIFO)
al otro proceso.
*/
void stop(){

    int fd;
    int closeflag = -2;

    fd = open(FIFO_FILE, O_RDWR);
    if (!fd){
        perror("Error al abrir tubería en server.c.");
        exit(-1);
    }

    printf("Cerrando sesión...\n");

    write(fd, &closeflag, sizeof(int));
    write(fd, &closeflag, sizeof(int));
    write(fd, &closeflag, sizeof(int));

    close(fd);
}