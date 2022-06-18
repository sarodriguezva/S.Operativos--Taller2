#include "defs.h"

int hash(int origen, int destino, int hora){
    return (origen-1)+1160*(destino-1)+1160*1160*(hora);
}