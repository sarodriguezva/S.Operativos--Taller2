//Servidor encargado de gestionar peticiones del cliente con el servicio de búsqueda en otro proceso.

#include "../includes/defs.h"

void loadData();
void getValue(int *ptr, char *message, int min, int max);
double search(int origen, int destino, int hora);
void stop();


/*
Función que muestra interfaz al cliente.
Pide una opción y gestionar las funciones de acuerdo a su elección.
*/

int showInterface(int *origen, int *destino, int *hora, double *tiempo_viaje){
    
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
        showInterface(origen, destino, hora, tiempo_viaje);
        break;

    case 2:
        getValue(destino, "Ingrese ID del Destino: ", 1, 1160);
        showInterface(origen, destino, hora, tiempo_viaje);
        break;

    case 3:
        getValue(hora, "Ingrese Hora del Día: ", 0, 23);
        showInterface(origen, destino, hora, tiempo_viaje);
        break;

    case 4:
        printf("Datos recibidos: \n");
        printf("Origen: \t%d\n", *origen);
        printf("Destino: \t%d\n", *destino);
        printf("Hora: \t\t%d\n\n", *hora);

        *tiempo_viaje = search(*origen, *destino, *hora);

        printf("Resultado de búsqueda. Tiempo medio de viaje: \t%.2f\n\n", *tiempo_viaje);

        printf("Presione una tecla para continuar...\n\n");
        
        char c;
        scanf("%c", &c);

        showInterface(origen, destino, hora, tiempo_viaje);
        break;

    case 5:
        stop();
        printf("Adios!\n");
        break;

    default:
        printf("\nError! ingrese un dato válido.\n");
        showInterface(origen, destino, hora, tiempo_viaje);
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


/*
Función principal.
Crea las variables de interés y muestra la interfaz.
*/
int main(){

    int origen, destino, hora;
    double tiempo_viaje;

    showInterface(&origen, &destino, &hora, &tiempo_viaje);

    return 0;
}