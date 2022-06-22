#include "../includes/defs.h"
#include "../includes/socket_defs.h"

int showInterface(int *fd, int *origen, int *destino, int *hora, double *tiempo_viaje);
void getValue(int *var, char *message, int min, int max);
void sendDataToServer(int fd, int *origen, int *destino, int *hora);


/*
Función Principal.
Crea y configura el socket de conexión del cliente con el servidor (local).
Una vez logrado, muestra la interfaz al cliente.
*/
int main(){
    int client_fd = -1;
    struct sock_addr_in server;

    printf("Inicializando cliente...\n");

    //Rutinas de inicialización socket cliente.
    client_fd = createSocket(client_fd);
    configureClientSocket(&server, "127.0.0.1");
    client_fd = connectSocket(client_fd, &server);

    printf("Cliente configurado con éxito!...\n\n");

    int origen, destino, hora;
    double tiempo_viaje;

    showInterface(&client_fd, &origen, &destino, &hora, &tiempo_viaje);
	
    printf("Cerrando sesión...\n");
	//Cierra conexión.
	close(client_fd);
    return 0;
}


/*
Función que muestra interfaz al cliente.
Pide una opción y gestionar las funciones de acuerdo a su elección.
*/
int showInterface(int *fd, int *origen, int *destino, int *hora, double *tiempo_viaje){
    
    int option;
    int closeflag = -2;

    printf("Bienvenido\n");
    printf("1. Ingresar origen.\n");
    printf("2. Ingresar destino.\n");
    printf("3. Ingresar hora.\n");
    printf("4. Buscar tiempo de viaje medio.\n");
    printf("5. Salir.\n\n");
    printf("Elige una opción: ");

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
        sendDataToServer(*fd, origen, destino, hora);

        printf("Datos enviados exitosamente!\n");
        printf("Esperando respuesta de servidor...\n");

        recv(*fd, tiempo_viaje, sizeof(double),0);

        printf("Resultado de búsqueda. Tiempo medio de viaje: \t%.2f\n\n", *tiempo_viaje);

        showInterface(fd, origen, destino, hora, tiempo_viaje);
        break;

    case 5:
        sendDataToServer(*fd, &closeflag, &closeflag, &closeflag);
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


/*
Función que envía los 3 datos cargados por el cliente al servidor,
por medio del descriptor del socket de conexión.
*/
void sendDataToServer(int fd, int *origen, int *destino, int *hora){

    send(fd, origen, sizeof(int), 0);
    send(fd, destino, sizeof(int), 0);
    send(fd, hora, sizeof(int), 0);
}