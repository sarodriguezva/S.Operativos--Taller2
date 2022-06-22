# S.Operativos--Taller2
Taller 2 de Sistemas Operativos.

Autores:
Santiago Rodríguez Vallejo - 1001066037 - sarodriguezva@unal.edu.co

Cristhian David Mora Uribe - 1233494036 - cdmorau@unal.edu.co

Javier Esteban Pacavita Galindo - 1015478836 - jpacavita@unal.edu.co


Manual de uso:
1) Crear una carpeta "files" y poner dentro el archivo de Uber con el nombre "data.csv".
2) Abrir un terminal en la carpeta del proyecto. (Terminal 1)
3) Abrir un terminal en la carpeta ./bin. (Terminal 2)
4) En el Terminal 1, ejecutar el comando make.
    El comando generará internamente el archivo en disco de medias de viaje.
    Una vez hecho esto ejecutará el servicio de búsqueda a la escucha de datos de entrada provenientes del servidor.
5) Esperar hasta ver el mensaje "Obteniendo Data...".
6) En el Terminal 2, ejecutar el comando ./server
    El comando configurará internamente el servidor y lo pondrá a la escucha de conexiones con clientes.
7) Esperar hasta ver el mensaje "Esperando petición del cliente...".

8) Abrir un terminal en la carpeta del proyecto por cada cliente nuevo que se desea conectar. (Terminal n).

9) En el Terminal n, ejecutar el comando ./client
10) Esperar a ver el menú de opciones.
11) Puede utilizar la interfaz libremente, con la siguiene guía:
    La interfaz muestra 5 posibles opciones,
    1. Ingresar origen.
    2. Ingresar destino.
    3. Ingresar hora.
    4. Buscar tiempo de viaje medio
    5. Salir.

El sistema tratará cada opción que elija a la vez.
Entre las opciones 1 y 3 pedirá que ingrese los valores que desea como origen, destino y hora de viaje correspondientes para realizar la búsqueda en el sistema. De no cargar algún dato, este internamente será tratado como cero (0).

Una vez cargados los 3 datos, puede proceder a realizar la búsqueda de su valor deseado al seleccionar la opción 4.
Al seleccionar esta opción se imprimirá en pantalla el valor correspondiente al viaje medio según sus datos.

Al seleccionar la opción 5, se terminará la sesión en su cliente.

Notas:

    * HASTA 32 CLIENTES PUEDEN CONECTARSE A LA VEZ EN EL SISTEMA.
    
    * El servidor imprimirá los registros de búsquedas hechos por cada cliente durante su tiempo de servicio.

12) Una vez terminada la ejecución del proyecto, se recomienda terminar a mano los programas de los Terminales 1 y 2 para evitar el consumo de recursos en segundo plano.