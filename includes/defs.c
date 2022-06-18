#include "defs.h"


/*
Función de hasheo del valor promedio de viaje de un registro.
Importante para la generación de tabla hash
y para el servicio de búsqueda.
*/
int hash(int origen, int destino, int hora){
    return (origen-1)+1160*(destino-1)+1160*1160*(hora);
}