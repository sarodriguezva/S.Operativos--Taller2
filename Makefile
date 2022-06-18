all: restart server save search clean run
SRC_DIR    = ./src/
BIN_DIR    = ./bin/
OBJ_DIR    = ./obj/
INC_DIR    = ./includes/
F_DIR      = ./files/

#Generar Server
server: server.o defs.o
	gcc -Wall -o $(BIN_DIR)server server.o defs.o

server.o: $(SRC_DIR)server.c
	gcc -Wall -c $(SRC_DIR)server.c


#Generar Save
save: save.o defs.o
	gcc -Wall -o $(BIN_DIR)save save.o defs.o

save.o: $(SRC_DIR)save.c
	gcc -Wall -c $(SRC_DIR)save.c


#Generar Search
search: search.o defs.o
	gcc -Wall -o $(BIN_DIR)search search.o defs.o

search.o: $(SRC_DIR)search.c
	gcc -Wall -c $(SRC_DIR)search.c


#Generar Defs
defs.o: $(INC_DIR)defs.c
	gcc -Wall -c $(INC_DIR)defs.c


clean:
	mv *o $(OBJ_DIR)

restart:
	rm -f -r $(OBJ_DIR)*o

run: 
	chmod 777 bashScript.sh
	./bashScript.sh