#include "../includes/defs.h"

void resetValues(int *origen, int *destino, int *hora);
void getValues(int fd, int *origen, int *destino, int *hora);
double search(int origen, int destino, int hora);
void sendData(int fd, double data);

/*
478,627,0,1145.57,523.7,1069.37,1.4
477,637,0,1163.38,250.21,1138.78,1.23
451,897,0,844.3,274.23,812.05,1.3
951,151,12,865.02,371.3,789.38,1.55
493,477,0,964.23,263.0,937.34,1.25
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

        //Verifica si el cliente presionó "Salir".
        if (origen == -2 && destino == -2 && hora == -2){
            break;
        }

        mean = search(origen, destino, hora);
        sendData(fd, mean);
        resetValues(&origen, &destino, &hora);
    }
    
    close(fd);
    unlink(FIFO_FILE);
    return 0;
}

void resetValues(int *origen, int *destino, int *hora){

    printf("Reiniciando datos...\n");
    *origen = -1;
    *destino = -1;
    *hora = -1;
}

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

void sendData(int fd, double data){

    printf("Enviando valor...\n");

    write(fd, &data, sizeof(double));

    printf("Valor enviado con éxito!\n");
}