#include <stdio.h>
#include <stdlib.h>

#define DATA_CSV    "../files/data.csv"
#define DATA_BIN    "../bin/data.bin"
#define SIZE_HASH   32294400

typedef struct viaje {
    int origen;
    int destino;
    int hora;
    double media;
} viaje;