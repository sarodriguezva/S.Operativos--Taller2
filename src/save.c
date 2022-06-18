//Rutina de generación de archivo binario en disco duro para la búsqueda de registros.

#include "../includes/defs.h"


/*
Función encargada de generar el hasheo ordenado de los datos en el archivo.
*/
void loadArray(double* result_list, viaje tmp){
	char buffer[200];
    int h;

	FILE *data = fopen(DATA_CSV, "r");
	if (!data){
		perror("Error al abrir CSV.");
	}

    //Ignorar cabecera.
	fgets(buffer,200,data);
	
	while(!feof(data)){
		fscanf(data, "%d,%d,%d,%lf", &tmp.origen, &tmp.destino, &tmp.hora, &tmp.media);

		fgets(buffer,200,data);

		h = hash(tmp.origen, tmp.destino, tmp.hora);
		result_list[h] = tmp.media;
	}

	fclose(data);
}


/*
Función encargada de escribir en el archivo binario
cada valor promedio de viaje en el orden del hasheo.
*/
void loadBinFile(double* result_list){
	FILE *bin = fopen(DATA_BIN, "w+b");
	if (!bin){
		perror("Error al abrir el archivo binario.");
	}
	
	for(int i = 0; i <= SIZE_HASH; i++){
		fwrite(&result_list[i], sizeof(double), 1, bin);
	}

	fclose(bin);

    //Limpiar memoria.
	free(result_list);
}


/*
Función principal.
Genera la tabla hash de valores promedio de viaje en un archivo binario.
*/
int main(){
    viaje tmp;
    double *result_list;

    result_list = malloc(SIZE_HASH*sizeof(double));

    loadArray(result_list, tmp);

    loadBinFile(result_list);

    return 0;
}