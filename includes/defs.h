#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define DATA_CSV    "../files/data.csv"
#define DATA_BIN    "../bin/data.bin"
#define FIFO_FILE   "../files/myfifo"
#define LOG_FILE    "../files/log.txt"
#define SIZE_HASH   32294400

typedef struct viaje {
    int origen;
    int destino;
    int hora;
    double media;
} viaje;

int hash(int origen, int destino, int hora);
void getTimeStamp();