/* Funciones a las que acceden el cliente y proveedor para interactuar con los recursos */
/* Programa principal del kernel*/ 

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/types.h>
# include <string.h>

# define IVA 0.16
# define GANANCIA 0.10
# define PERMISOS 0644

struct cliente{
    int id_cliente;
    char *nombre_cliente;
    char *contrasena;
};
typedef struct cliente CLIENTE;


void comprobarCatalogo(){
    /* Comprobamos primero la existencia del catalogo */
    FILE *catalogo;
    if(fopen("catalogo.txt", "r") == NULL){ // Comprueba si no existe el archivo del catálogo
        catalogo = fopen("catalogo.txt", "w"); // Creamos el archivo si no existe
        fclose(catalogo);
    }

    /* Comprobamos después la existencia del semáforo del catálogo */
    key_t llave_cat = ftok("catalogos", 1);
    int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
    semctl(semcat, 0, SETVAL, 1);

/*
    if(i == 1){        
        int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
        semctl(semcat, 0, SETVAL, 0);
        printf("%d \n", semctl(semcat, 0, GETVAL, 0));
        semctl(semcat, 0, SETVAL, 1);
    }
    else{
        int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
        printf("%d \n", semctl(semcat, 0, GETVAL, 0));
    }    
    if(catalogoKey = fopen("catalogo", "r")){ // Comprueba si existe el archivo del catálogo
        printf("Catalogo existe \n");
    }
    else{ // Creamos la llave y el semáforo del archivo
        printf("Catalogo no existe \n");
        key_t llave_cat = ftok("catalogo", 0);
        int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
        semctl(semcat, 0, SETVAL, 0);
        printf("%d", semctl(semcat, 0, GETVAL, 1));
        semctl(semcat, 0, SETVAL, 1);
    }*/

}

void comprobarCarritos(){
    /* Comprobamos primero la existencia del carritos */
    FILE *carritos;
    if(fopen("carritos.txt", "r") == NULL){ // Comprueba si no existe el archivo de carritos
        carritos = fopen("carritos.txt", "w"); // Creamos el archivo si no existe
        fclose(carritos);
    }

    /* Comprobamos después la existencia del semáforo del catálogo */
    key_t llave_car = ftok("carritos", 1);
    int semcar = semget(llave_car, 1, IPC_CREAT|PERMISOS);
}

void comprobarClientes(){
    /* Comprobamos primero la existencia del carritos */
    FILE *clientes;
    if(fopen("clientes.bin", "r") == NULL){ // Comprueba si no existe el archivo de clientes
        clientes = fopen("clientes.bin", "w"); // Creamos el archivo si no existe
        fclose(clientes);
    }

    /* Comprobamos después la existencia del semáforo del catálogo */
    key_t llave_cli = ftok("clientes", 1);
    int semcli = semget(llave_cli, 1, IPC_CREAT|PERMISOS);
}

int obtenerNuevoID(){
    FILE *catalogo = fopen("catalogo.txt", "r");
    char *aux;
    char c_aux[50];
    int id = 0;
    aux = fgets(c_aux, 50, catalogo);
    while(aux != NULL){
        aux = fgets(c_aux, 50, catalogo);
        id++;
    }
    fclose(catalogo);
    return id;
}

int agregarArticulo(char *nombre, int cantidad, float precio){
    FILE *catalogo;
    if(fopen("catalogo.txt", "r") == NULL){ // Comprueba si no existe el archivo del catálogo
        return -1; // error, no existe
    }
    else{
        key_t llave_cat = ftok("catalogos", 1);
        int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
        if(semctl(semcat, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
            semctl(semcat, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado
            
            /* Creamos toda la cadena para el archivo */
            char id[3];
            char cant[20];
            char prec[20];

            int nuevo_id = obtenerNuevoID(); // Obtenemos un id libre para darselo al producto
            float nuevo_precio = precio + precio*IVA + precio*GANANCIA;       
            sprintf(id, "%d", nuevo_id); // Convertimos para poder escribirlo en el archivo
            sprintf(cant, "%d", cantidad);
            sprintf(prec, "%0.2f", nuevo_precio);
            
            // Copiando el contenido a una cadena para escribirla en el archivo
            char nuevo[200];
            strcat(nuevo, id);
            strcat(nuevo, "-");
            strcat(nuevo, nombre);
            strcat(nuevo, "-");
            strcat(nuevo, cant);
            strcat(nuevo, "-");
            strcat(nuevo, prec);
            strcat(nuevo, "\n");
            
            FILE *catalogo = fopen("catalogo.txt", "a");
            fputs(nuevo, catalogo); // Escribe el nuevo artículo en la list
            fclose(catalogo);
            semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
            return 0;
        }
        else{
            return -2; // error, catálogo ocupado
        }        
    }
}

int buscarporID(int id){
    FILE *catalogo;
    if(fopen("catalogo.txt", "r") == NULL){ // Comprueba si no existe el archivo del catálogo
        return -1; // error, no existe
    }
     else{
        FILE *catalogo = fopen("catalogo.txt", "r+");
        char *aux;
        char c_aux[50]; // Guardará cada linea del archivo de manera temporal
        aux = fgets(c_aux, 50, catalogo);

        while(aux != NULL){                
            aux = fgets(c_aux, 50, catalogo);
            
        }
        fclose(catalogo);         

        return 0;      
    }
}

int buscarporNombre(char *nombre){
    FILE *catalogo;
    if(fopen("catalogo.txt", "r") == NULL){ // Comprueba si no existe el archivo del catálogo
        return -1; // error, no existe
    }
     else{
        FILE *catalogo = fopen("catalogo.txt", "r+");
        char *aux;
        char c_aux[50]; // Guardará cada linea del archivo de manera temporal
        aux = fgets(c_aux, 50, catalogo);

        while(aux != NULL){                
            aux = fgets(c_aux, 50, catalogo);                
        }
        fclose(catalogo);  

        return 0;      
    }
}

int agregarCantidad(int id, int cantidad, int indice_archivo){
    FILE *catalogo;
    if(fopen("catalogo.txt", "r") == NULL){ // Comprueba si no existe el archivo del catálogo
        return -1; // error, no existe
    }
     else{
        key_t llave_cat = ftok("catalogos", 1);
        int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
        if(semctl(semcat, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
            semctl(semcat, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado

            FILE *catalogo = fopen("catalogo.txt", "r+");
            char *aux;
            char c_aux[50]; // Guardará cada linea del archivo de manera temporal
            int indice = 0;
            aux = fgets(c_aux, 50, catalogo);

            while(aux != NULL){
                if(indice == 3){                    
                    fputs("hola jaja", catalogo);
                }
                indice++;
                aux = fgets(c_aux, 50, catalogo);
                
            }
            fclose(catalogo);  
            

            semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
            return 0;
        }
        else{
            return -2; // error, catálogo ocupado
        }        
    }
}

int agregarCliente(){
    FILE *cliente;
    if(fopen("clientes.bin", "r") == NULL){ // Comprueba si no existe el archivo del catálogo
        return -1; // error, no existe
    }
     else{
        key_t llave_cli = ftok("clientes", 1);
        int semcli = semget(llave_cli, 1, IPC_CREAT|PERMISOS);
        if(semctl(semcli, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
            semctl(semcli, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado

            /* Creamos un cliente*/
            CLIENTE cl1;
            cl1.contrasena = "Lola";
            cl1.id_cliente = 0;
            cl1.nombre_cliente = "Juan Pablo II";

            
            FILE *clientes = fopen("catalogo.txt", "ab");
            fwrite(&cl1, sizeof(CLIENTE), 1, clientes);

            fclose(clientes);
            semctl(semcli, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
            return 0;
        }
        else{
            return -2; // error, catálogo ocupado
        }        
    }
}

int leerCliente(){
    FILE *cliente;
    if(fopen("clientes.bin", "r") == NULL){ // Comprueba si no existe el archivo del catálogo
        return -1; // error, no existe
    }
     else{
        /* Creamos un cliente*/
        CLIENTE cl1;
        
        FILE *clientes = fopen("catalogo.txt", "ab");
        fread(&cl1, sizeof(CLIENTE), 1, clientes);
        fclose(clientes);
        printf("%i, %s, %s", cl1.id_cliente, cl1.contrasena, cl1.nombre_cliente);
        return 0;
             
    }
}