#include "defs.h"


/*
Función de hasheo del valor promedio de viaje de un registro.
Importante para la generación de tabla hash
y para el servicio de búsqueda.
*/
int hash(int origen, int destino, int hora){
    return (origen-1)+1160*(destino-1)+1160*1160*(hora);
}

void getTimeStamp(){
    int hours, minutes, seconds, day, month, year;
    time_t now;

    time(&now);

    struct tm *local = localtime(&now);
 
    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;
 
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    FILE *data = fopen(LOG_FILE, "a");
	if (!data){
		perror("Error al abrir CSV.");
	}
    fprintf(data,"[Fecha %d-%02d-%02d T%02d:%02d:%02d] ",
    year, month, day, hours, minutes, seconds);
    fclose(data);

}