#include "../includes/defs.h"
#include "../includes/socket_defs.h"

int showInterface(int fd, int *origen, int *destino, int *hora, double *tiempo_viaje);
void getValue(int *var, char *message, int min, int max);
void sendDataToServer(int fd, int *origen, int *destino, int *hora);

int main(){
    int client_fd;
    int r;
    struct sock_addr_in server;
    char buffer[200];

    //Rutinas de inicialización socket cliente.
    createSocket(client_fd);
    configureClientSocket(client_fd, server, "192.168.0.4");
    connectSocket(client_fd, server);

    int origen, destino, hora;
    double tiempo_viaje;

    showInterface(client_fd, &origen, &destino, &hora, &tiempo_viaje);
	
	//Cierra conexión.
	close(client_fd);
    return 0;
}


/*
Función que muestra interfaz al cliente.
Pide una opción y gestionar las funciones de acuerdo a su elección.
*/
int showInterface(int fd, int *origen, int *destino, int *hora, double *tiempo_viaje){
    
    int option;

    printf("Bienvenido\n");
    printf("1. Ingresar origen.\n");
    printf("2. Ingresar destino.\n");
    printf("3. Ingresar hora.\n");
    printf("4. Buscar tiempo de viaje medio.\n");
    printf("5. Salir.\n\n");
    printf("Elige una opción: ");

    fflush(stdin);

    scanf("%d", &option);

    system("clear");
    switch (option) {
    case 1:
        getValue(origen, "Ingrese ID del Origen: ", 1, 1160);
        showInterface(fd, origen, destino, hora, tiempo_viaje);
        break;

    case 2:
        getValue(destino, "Ingrese ID del Destino: ", 1, 1160);
        showInterface(fd, origen, destino, hora, tiempo_viaje);
        break;

    case 3:
        getValue(hora, "Ingrese Hora del Día: ", 0, 23);
        showInterface(fd, origen, destino, hora, tiempo_viaje);
        break;

    case 4:
        
        printf("Enviando datos al servidor...\n");
        sendDataToServer(fd, origen, destino, hora);

        recv(fd, tiempo_viaje, sizeof(double),0);

        printf("Resultado de búsqueda. Tiempo medio de viaje: \t%.2f\n\n", *tiempo_viaje);
        printf("Presione una tecla para continuar...\n\n");
        
        char c;
        scanf("%c", &c);

        showInterface(fd, origen, destino, hora, tiempo_viaje);
        break;

    case 5:
        int closeflag = -2;
        sendDataToServer(fd, &closeflag, &closeflag, &closeflag);
        printf("Adios!\n");
        break;

    default:
        printf("\nError! ingrese un dato válido.\n");
        showInterface(fd, origen, destino, hora, tiempo_viaje);
        break;
    }

    return 0;
}


/*
Función que gestiona la entrada por teclado de un dato por parte del cliente.
*/
void getValue(int *var, char *message, int min, int max){

    printf("%s", message);

    //Validar datos.

    scanf("%d", var);
    system("clear");

}

void sendDataToServer(int fd, int *origen, int *destino, int *hora){
    
    send(fd, origen, sizeof(int), 0);
    send(fd, destino, sizeof(int), 0);
    send(fd, hora, sizeof(int), 0);
}