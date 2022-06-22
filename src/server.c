//Servidor encargado de gestionar peticiones del cliente con el servicio de búsqueda en otro proceso.
#include <pthread.h>

#include "../includes/defs.h"
#include "../includes/socket_defs.h"

struct thread_args{
    int *fd;
    struct sock_addr_in address;
};

void * processClient(void *pclient_fd);
void receiveDataFromClient(int client_fd, int *origen, int *destino, int *hora);
double search(int origen, int destino, int hora);
void printLog(struct sock_addr_in address, int origen, int destino, int hora, double tiempo_viaje);
void stop();


/*
Función Principal.
Encargada de definir y configurar el socket de servidor.
Queda a la espera de clientes entrantes a la red.
Cuando llega un cliente, el sistema lo trata con un hilo nuevo,
de forma que haya concurrencia de clientes.
*/
int main(){
    int server_fd = -1, client_fd = -1;
    struct sock_addr_in address;
    int addrlen = sizeof(address);

    printf("Inicializando servidor...\n");

    //Rutinas de inicialización de socket servidor.
    server_fd = createSocket(server_fd);
    server_fd = configureServerSocket(server_fd, &address);
    server_fd = setSocketToListen(server_fd);

    printf("Servidor configurado con éxito!...\n");

    while(1){
        printf("Esperando petición de cliente...\n");

        //Trae una conexión de la pila como socket.
        client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (!client_fd){
            perror("Error al aceptar conexión");
            exit(-1);
        }

        printf("Conexión con cliente recibida!...\n");

        //Creación de hilo para cliente individual.
        pthread_t tid;

        //Paso de argumentos para la función.
        struct thread_args *args = malloc(sizeof(struct thread_args));
        args->fd = &client_fd;
        args->address = address;
        
        pthread_create(&tid, NULL, processClient, args);
    }

    printf("Cerrando servidor...\n");
	
    //Cierra conexión.
	shutdown(server_fd, SHUT_RDWR);
    stop();

    return 0;
}


/*
Función encargada de tratar a un solo cliente.
Queda a la espera por los datos que envíe el cliente.
Una vez recibidos, gestiona la búsqueda del valor correspondiente,
al recibir dicho dato del servicio, lo devuelve por socket al cliente.
Si el cliente decide salir, se maneja su desconexión.
*/
void * processClient(void *_args){
    //Inyección de argumentos por el hilo.
    struct thread_args *args = (struct thread_args *) _args;
    int client_fd = *(args->fd);
    struct sock_addr_in address = args->address;
    free(args);
    
	int origen, destino, hora;
	double tiempo_viaje;

	while (1){
		receiveDataFromClient(client_fd, &origen, &destino, &hora);

        //Si el cliente decide salir, se reciben 3 flags con valor -2.
		if (origen == -2 && destino == -2 && hora == -2){
			break;
		}

        //Comunicación con el servicio de búsqueda.
		tiempo_viaje = search(origen, destino, hora);

		send(client_fd, &tiempo_viaje, sizeof(double), 0);
        printLog(address, origen, destino, hora, tiempo_viaje);
	}

	//Cierra conexión
	close(client_fd);
    printf("Cliente desconectado!\n");
    pthread_exit(NULL);
    return NULL;
}


/*
Función que recibe los datos del cliente por medio del descriptor de su socket de conexíón.
Carga los 3 datos de interés uno a uno.s
*/
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

    write(fd, &origen, sizeof(int));
    write(fd, &destino, sizeof(int));
    write(fd, &hora, sizeof(int));

    while(1){
        r = read(fd, &value, sizeof(double));

        if (r == -1){
            perror("Error al leer en server.c.");
            exit(-1);
        }else if (r > 0 || r == EOF){
            break;
        }
    }

    close(fd);
    return value;
}


void printLog(struct sock_addr_in address, int origen, int destino, int hora, double tiempo_viaje){
    getTimeStamp();
    printf("Cliente [%s] [%.2f - %d - %d]\n", 
        inet_ntoa(address.sin_addr), tiempo_viaje, origen, destino);
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