#include "../includes/defs.h"

void resetValues(int *origen, int *destino, int *hora);
void getData(int fd, int *origen, int *destino, int *hora);
double search(int origen, int destino, int hora);
void sendData(int fd, double data);

int main(){

    int fd;
    double mean;
    int origen, destino, hora;

    resetValues(&origen, &destino, &hora);

    if (mkfifoat(AT_FDCWD, FIFO_FILE, 0666) == -1){
        perror("Error al crear tubería nombrada en search.c");
        unlink(FIFO_FILE);
        exit(-1);
    };

    fd = open(FIFO_FILE, O_RDWR);
    if (!fd){
        perror("Error al abrir tubería en search.c.");
        exit(-1);
    }

    getData(fd, &origen, &destino, &hora);
    mean = search(origen, destino, hora);
    sendData(fd, mean);

    resetValues(&origen, &destino, &hora);
    
    unlink(FIFO_FILE);
    return 0;
}

void resetValues(int *origen, int *destino, int *hora){
    
    *origen = -1;
    *destino = -1;
    *hora = -1;
}

void getData(int fd, int *origen, int *destino, int *hora){

    int *data = NULL;
    int r;

    while(1){
        r = read(fd, data, 3*sizeof(int));

        if (r == -1){
            perror("Error al leer en server.c.");
            exit(-1);
        }else if (r > 0){
            origen = data;
            destino = data + 1;
            hora = data + 2;
            break;
        }
    }
}

double search(int origen, int destino, int hora){

    int index;
    double value;

    index = hash(origen, destino, hora);

	FILE* regs = fopen(DATA_BIN, "rb");
	if (!regs){
		perror("Error al abrir DATA_BIN.");
		exit(-1);
	}
	
	fseek(regs, index*sizeof(double), SEEK_SET);
	fread(&value, sizeof(double), 1, regs);

	fclose(regs);
	rewind(regs);

	return value;
}

void sendData(int fd, double data){

    write(fd, &data, sizeof(double));

}