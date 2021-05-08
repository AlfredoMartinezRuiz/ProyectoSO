/* Funciones a las que acceden el cliente y proveedor para interactuar con los recursos */
/* Programa principal del kernel*/ 

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<wait.h>
# include<sys/ipc.h>
# include<sys/shm.h>
# include<sys/sem.h>
# include<sys/types.h>

# define PERMISOS 0644
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
    if(fopen("clientes.txt", "r") == NULL){ // Comprueba si no existe el archivo de clientes
        clientes = fopen("clientes.txt", "w"); // Creamos el archivo si no existe
        fclose(clientes);
    }

    /* Comprobamos después la existencia del semáforo del catálogo */
    key_t llave_cli = ftok("clientes", 1);
    int semcli = semget(llave_cli, 1, IPC_CREAT|PERMISOS);
}