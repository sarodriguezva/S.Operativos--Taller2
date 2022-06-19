all: restart server client save search clean run
SRC_DIR    = ./src/
BIN_DIR    = ./bin/
OBJ_DIR    = ./obj/
INC_DIR    = ./includes/
F_DIR      = ./files/

#Generar Server
server: server.o defs.o socket_defs.o
	gcc -Wall -o $(BIN_DIR)server server.o defs.o socket_defs.o

server.o: $(SRC_DIR)server.c
	gcc -Wall -c $(SRC_DIR)server.c


#Generar Client
client: client.o defs.o socket_defs.o
	gcc -Wall -o $(BIN_DIR)client client.o defs.o socket_defs.o

client.o: $(SRC_DIR)client.c
	gcc -Wall -c $(SRC_DIR)client.c


#Generar Save
save: save.o defs.o socket_defs.o
	gcc -Wall -o $(BIN_DIR)save save.o defs.o socket_defs.o

save.o: $(SRC_DIR)save.c
	gcc -Wall -c $(SRC_DIR)save.c


#Generar Search
search: search.o defs.o socket_defs.o
	gcc -Wall -o $(BIN_DIR)search search.o defs.o socket_defs.o

search.o: $(SRC_DIR)search.c
	gcc -Wall -c $(SRC_DIR)search.c


#Generar Defs
defs.o: $(INC_DIR)defs.c
	gcc -Wall -c $(INC_DIR)defs.c

#Generar SocketDefs
socket_defs.o: $(INC_DIR)socket_defs.c
	gcc -Wall -c $(INC_DIR)socket_defs.c


#Mover los archivos *.o a la carpeta ./obj
clean:
	mv *o $(OBJ_DIR)


#Eliminar los archivos *.o
restart:
	rm -f -r $(OBJ_DIR)*o

run: 
	chmod 777 bashScript.sh
	./bashScript.sh