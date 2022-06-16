#include "../includes/defs.h"

void loadData();
void getValue(int *ptr, char *message[], int min, int max);
double search(int origen, int destino, int hora);

int showInterface(int *origen, int *destino, int *hora, double *tiempo_viaje){
    int option;

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
        main();
        break;

    case 2:
        getValue(destino, "Ingrese ID del Destino: ", 1, 1160);
        main();
        break;

    case 3:
        getValue(hora, "Ingrese Hora del Día: ", 0, 23);
        main();
        break;

    case 4:
        *tiempo_viaje = search(*origen, *destino, *hora);
        main();
        break;

    case 5:
        printf("Adios!");
        break;

    default:
        printf("\nError! ingrese un dato válido.\n");
        main();
        break;
    }

    return 0;
}

int hash(int origen, int destino, int hora){
    return (origen-1)+1160*(destino-1)+1160*1160*(hora);
}

void getValue(int *var, char *message[], int min, int max){

    printf("%s", message);

    //Validar datos.

    scanf("%d", var);

}

double search(int origen, int destino, int hora){
    //Función de buscar.
    return 0;
}

int main(){
    int origen, destino, hora;
    double tiempo_viaje;

    showInterface(&origen, &destino, &hora, &tiempo_viaje);

    return 0;
}