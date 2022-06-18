//Servicio de búsqueda en el archivo "data.csv"

#include "../includes/defs.h"

void resetValues(int *origen, int *destino, int *hora);
void getValues(int fd, int *origen, int *destino, int *hora);
double search(int origen, int destino, int hora);
void sendData(int fd, double data);

/*
Valores de búsqueda a probar.
src-dst-hr-avg
478, 627, 0, 1145.57
477, 637, 0, 1163.38
451, 897, 0, 844.3
951, 151, 12, 865.02
493, 477, 0, 964.23
*/


/*
Función principal.
Crea la tubería nombrada (FIFO) de comunicación con el servidor.
Deja el programa a la espera de los datos por el cliente.
*/
int main(){

    int fd;
    double mean;
    int origen, destino, hora;

    resetValues(&origen, &destino, &hora);

    unlink(FIFO_FILE);

    remove(FIFO_FILE);

    if (mkfifoat(AT_FDCWD, FIFO_FILE, 0666) == -1){
        perror("Error al crear tubería nombrada en search.c");
        unlink(FIFO_FILE);
        exit(-1);
    };

    printf("FIFO creada exitosamente...\n");

    fd = open(FIFO_FILE, O_RDWR);
    if (!fd){
        perror("Error al abrir tubería en search.c.");
        exit(-1);
    }

    printf("FIFO abierta exitosamente...\n");

    while (1){
        getValues(fd, &origen, &destino, &hora);

        //Verifica si el cliente presionó "Salir" en la interfaz.
        if (origen == -2 && destino == -2 && hora == -2){
            break;
        }

        mean = search(origen, destino, hora);
        sendData(fd, mean);
        resetValues(&origen, &destino, &hora);
    }

    printf("Cerrando servicio de búsqueda...\n");
    
    close(fd);
    unlink(FIFO_FILE);
    return 0;
}


/*
Función que se encarga de reiniciar los valores
para poder capturar correctamente los datos que envíe el servidor.
Solo para efectos de debugging.
*/
void resetValues(int *origen, int *destino, int *hora){

    printf("Reiniciando datos...\n");
    *origen = -1;
    *destino = -1;
    *hora = -1;
}


/*
Función encargada de leer uno a uno los datos que envíe el servidor.
Imprime los datos recibidos a modo de registro.
*/
void getValues(int fd, int *origen, int *destino, int *hora){

    int r;

    printf("Obteniendo Data...\n");

    r = read(fd, origen, sizeof(int));
    
    if (r == -1){
        perror("Error al leer en server.c.");
        exit(-1);
    }

    r = read(fd, destino, sizeof(int));
    
    if (r == -1){
        perror("Error al leer en server.c.");
        exit(-1);
    }

    r = read(fd, hora, sizeof(int));
    
    if (r == -1){
        perror("Error al leer en server.c.");
        exit(-1);
    }

    printf("Data obtenida con éxito!\n");

    printf("Datos obtenidos:\n");
    printf("Origen: \t%d\n", *origen);
    printf("Destino: \t%d\n", *destino);
    printf("Hora: \t\t%d\n\n", *hora);
}


/*
Función encargada de la búsqueda en el archivo "data.csv"
de acuerdo a los valores recibidos por el servidor.
*/
double search(int origen, int destino, int hora){
    printf("Buscando valor...\n");
    int index;
    double value;

    index = hash(origen, destino, hora);
    printf("Indice encontrado! \t Indice: %d\n", index);

	FILE* regs = fopen(DATA_BIN, "rb");
	if (!regs){
		perror("Error al abrir DATA_BIN.");
		exit(-1);
	}

	printf("DATA_BIN abierto con éxito...\n");

	fseek(regs, index*sizeof(double), SEEK_SET);
	fread(&value, sizeof(double), 1, regs);

    printf("Valor encontrado! \t Valor: %.2f\n", value);

	fclose(regs);
	rewind(regs);

	return value;
}


/*
Función encargada de enviar el valor encontrado al servidor
mediante la tubería nombrada (FIFO).
*/
void sendData(int fd, double data){

    printf("Enviando valor...\n");

    write(fd, &data, sizeof(double));

    printf("Valor enviado con éxito!\n");
}