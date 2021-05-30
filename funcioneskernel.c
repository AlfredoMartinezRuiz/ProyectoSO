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
# define NPRODS 10
struct cliente{
    int id_cliente;
    char nombre_cliente[30];
    char email[50];
    char contrasena[30];
};
typedef struct cliente CLIENTE;

struct proveedor{
    int id_proveedor;
    char RFC[13];
    char nombre[50];
    char contrasena[30];
};
typedef struct proveedor PROVEEDOR;

struct producto{
    int id_producto;
    char nombre_producto[40];
    int cantidad;
    float precio;
};
typedef struct producto PRODUCTO;

struct carrito{
    char email[50]; // Para relacionarlo con su carrito
    PRODUCTO productos[NPRODS]; // Puede llevar máximo de 10 productos en carrito, cantidad representará cuántos lleva
    int n_productos; // Representa cuantos tipos de productos diferentes lleva
    float precio_total;
};
typedef struct carrito CARRITO;

/* Funcion encargada de crear archivo catalgo */
void crearCatalogo(){
    /* Comprobamos primero la existencia del catalogo */
    FILE *catalogo;
    catalogo = fopen("catalogo.bin", "wb"); // Creamos el archivo si no existe
    fclose(catalogo);    

    /* Comprobamos después la existencia del semáforo del catálogo */
    key_t llave_cat = ftok("catalogos", 1);
    int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
    semctl(semcat, 0, SETVAL, 1);
}

/* Funcion encargada de crear archivo carritos */
void crearCarritos(){
    /* Comprobamos primero la existencia del carritos */
    FILE *carritos;
    carritos = fopen("carritos.bin", "wb"); // Creamos el archivo si no existe
    fclose(carritos);    

    /* Comprobamos después la existencia del semáforo de carritos */
    key_t llave_car = ftok("carritos", 1);
    int semcar = semget(llave_car, 1, IPC_CREAT|PERMISOS);
    semctl(semcar, 0, SETVAL, 1);    
}

/* Funcion encargada de crear archivo clientes*/
void crearClientes(){
    /* Comprobamos primero la existencia del carritos */
    FILE *clientes;
    clientes = fopen("clientes.bin", "wb"); // Creamos el archivo si no existe
    fclose(clientes);    

    /* Comprobamos después la existencia del semáforo de clientes*/
    key_t llave_cli = ftok("clientes", 1);
    int semcli = semget(llave_cli, 1, IPC_CREAT|PERMISOS);
    semctl(semcli, 0, SETVAL, 1);
}

/* Funcion encargada de crear archivo clientes*/
void crearProveedores(){
    /* Comprobamos primero la existencia del carritos */
    FILE *proveedores;
    proveedores = fopen("proveedores.bin", "wb"); // Creamos el archivo si no existe
    fclose(proveedores);    

    /* Comprobamos después la existencia del semáforo de proveedores */
    key_t llave_pro = ftok("proveedores", 1);
    int sempro = semget(llave_pro, 1, IPC_CREAT|PERMISOS);
    semctl(sempro, 0, SETVAL, 1);
}

/* Obtenemos algun id disponible para un nuevo producto */
int obtenerNuevoID(){
	FILE *catalogo = fopen("catalogo.bin", "rb");
    int id;
    /* Creamos un producto*/
    PRODUCTO prod;
    fread(&prod, sizeof(PRODUCTO), 1, catalogo);
    int i=0;
    while(!feof(catalogo)){ // Recorremos cada estructura del archivo
        id = prod.id_producto;
        
        if(id != i){
            fclose(catalogo);
            return id; //id es el que se lee
        }
        fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        i++;
    }
    fclose(catalogo);
    return i; //SI van en orden regresa el id que le sigue
}
  
/* Agregamos un articulo al catalogo */
int agregarArticulo(char *nombre, int cantidad, float precio){ 
	FILE *catalogo;
	if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
		crearCatalogo();
        return -1; // error, no existe
	}
	else{
		key_t llave_cat = ftok("catalogos", 1);
		int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
		if(semctl(semcat, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
			semctl(semcat, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado
		    
			/* Creamos un producto*/
			PRODUCTO prod;
			
			FILE *catalogo = fopen("catalogo.bin", "ab");  
			prod.id_producto = obtenerNuevoID(); // Obtenemos un id libre para darselo al producto
			
			/*Asignamos los valores a la estructura*/
			strcpy(prod.nombre_producto, nombre);
			prod.cantidad = cantidad;
            float precio_aux = precio + precio*IVA + precio*GANANCIA;
			prod.precio = precio_aux;
			
			fwrite(&prod, sizeof(PRODUCTO), 1, catalogo); //escribimos la estructura
			fclose(catalogo);
			semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
			return 0;
		}
		else{
		    return -2; // error, catálogo ocupado
		}        
	}
}

/* Buscamos el id de un articulo por medio de su nombre exacto */
int buscarporNombre(char *nombre){ 
	FILE *catalogo;
	if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
		crearCatalogo();
        return -1; // error, no existe
	}
	else{
		FILE *catalogo = fopen("catalogo.bin", "rb");
		/* Creamos un producto*/
		PRODUCTO prod;
		int existe = 0;
		fread(&prod, sizeof(PRODUCTO), 1, catalogo);
		
		while(!feof(catalogo)){
			if(strcmp(nombre, prod.nombre_producto)==0){
				int id = prod.id_producto;
				existe=1;
				return id;				
			}
			fread(&prod, sizeof(PRODUCTO), 1, catalogo);
		}
		fclose(catalogo);
		if(existe==0)
			return -3; 
		return 0;      
	}
}

/* Agregamos la cantidad dada por el proveedor al articulo con el id dado por el mismo */
int agregarCantidad(int id, int cantidad){ 
	FILE *catalogo;
	if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
		crearCatalogo();
        return -1; // error, no existe
	}
	else{
		key_t llave_cat = ftok("catalogos", 1);
		int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
		if(semctl(semcat, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
			semctl(semcat, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado

			FILE *catalogo = fopen("catalogo.bin", "r+b");
			/* Creamos un producto*/
			PRODUCTO prod;
			int existe = 0; //bandera para saber si existe el producto
			fread(&prod, sizeof(PRODUCTO), 1, catalogo);

			while(!feof(catalogo)){
				if(id == prod.id_producto){
					prod.cantidad = prod.cantidad+cantidad; //aumentamos la cantidad
					//printf("cantNuev: %d\n", prod.cantidad);
					int pos=ftell(catalogo)-sizeof(PRODUCTO); //actualiza el puntero
					fseek(catalogo,pos,SEEK_SET);
					fwrite(&prod, sizeof(PRODUCTO), 1, catalogo); //escribimos la estructura modificada
					existe = 1;
           			break;
				}
				fread(&prod, sizeof(PRODUCTO), 1, catalogo);
			}
			fclose(catalogo); 
			
			semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
			if(existe==0)
				return -3;
			return 0;				
		}
		else{
			return -2; // error, catálogo ocupado
		}        
	}
}

/* Consultamos el precio de un producto por medio de su id */
float consultarPrecio(int id){ 
    if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
        crearCatalogo();
        return -1; // error, no existe
    }
     else{
        /* Creamos un producto*/
        PRODUCTO prod;
        FILE *catalogo = fopen("catalogo.bin", "rb");
        
        fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        
        while(!feof(catalogo)){ // Recorremos cada estructura del archivo
            if(prod.id_producto == id){ // checamos que coincida con el ID
                return prod.precio; // Retornamos el precio del producto
            }
            fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        }
        fclose(catalogo);        
        return -14; // ID no encontrado      
    }
}

/* Consultamos el nombre de un producto por medio de su id */
int consultarNombre(int id, char *nombre){ 
    if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
        crearCatalogo();
        return -1; // error, no existe
    }
     else{
        /* Creamos un producto*/
        PRODUCTO prod;
        FILE *catalogo = fopen("catalogo.bin", "rb");
        
        fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        
        while(!feof(catalogo)){ // Recorremos cada estructura del archivo
            if(prod.id_producto == id){ // checamos que coincida con el ID
                strcpy(nombre, prod.nombre_producto);// Retornamos el precio del producto
                fclose(catalogo);
                return 0;
            }
            fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        }
        fclose(catalogo);        
        return -13; // ID no encontrado      
    }
}

/* Consultamos la cantidad disponible de un producto por medio de su id */
int consultarDisponibilidad(int id){ 
    if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
        crearCatalogo();
        return -1; // error, no existe
    }
     else{
        /* Creamos un producto*/
        PRODUCTO prod;
        FILE *catalogo = fopen("catalogo.bin", "rb");
        
        fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        
        while(!feof(catalogo)){ // Recorremos cada estructura del archivo
            if(prod.id_producto == id){ // checamos que coincida con el ID
                return prod.cantidad; // Retornamos la cantidad disponible del producto
            }
            fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        }
        fclose(catalogo);        
        return -12; // ID no encontrado      
    }
}

/* Descontamos la cantidad añadida al carrito, al producto con el id dado */
int descontarDeStock(int id, int cantidad){  
    if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
        crearCatalogo();
        return -1; // error, no existe
    }
     else{
        key_t llave_cat = ftok("catalogos", 1);
		int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
		if(semctl(semcat, 0, GETVAL, 0) == 0){ // Comprobamos que no esté ocupado
			semctl(semcat, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado
            
            /* Creamos un producto*/
            PRODUCTO prod;
            FILE *catalogo = fopen("catalogo.bin", "r+b");
            
            fread(&prod, sizeof(PRODUCTO), 1, catalogo);
            
            while(!feof(catalogo)){ // Recorremos cada estructura del archivo
                if(prod.id_producto == id){ // checamos que coincida con el ID
                    prod.cantidad = prod.cantidad - cantidad; // Descontamos la cantidad que se agregó al carrito 
                    // Actualizamos el carrito en el archivo 
                    int pos = ftell(catalogo) - sizeof(PRODUCTO); //actualiza el puntero
                    fseek(catalogo, pos, SEEK_SET);
                    fwrite(&prod, sizeof(PRODUCTO), 1, catalogo); //escribimos la estructura modificada
                             
                    fclose(catalogo); 
                    semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya noestá ocupado       
                    return 0;
                }
                fread(&prod, sizeof(PRODUCTO), 1, catalogo);
            }
            fclose(catalogo);        
            semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
            return -3; // ID no encontrado
        }
        else{
            return -11; // error, catálogo ocupado
        }        
    }
}

/* Almacenamos todos los productos en la lista dada desde clientes */
int obtenerProductos(PRODUCTO *p){ 
    if(fopen("catalogo.bin", "rb") == NULL){ // Comprueba si no existe el archivo del catálogo
        crearCatalogo();
        return -1; // error, no existe
    }
     else{
        /* Creamos un producto*/
        PRODUCTO prod;
        FILE *catalogo = fopen("catalogo.bin", "rb");
        
        fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        
        while(!feof(catalogo)){ // Recorremos cada estructura del archivo
            (*p).id_producto = prod.id_producto;
            (*p).cantidad = prod.cantidad;
            (*p).cantidad = prod.precio;
            strcpy((*p).nombre_producto, prod.nombre_producto);
            p++;
            fread(&prod, sizeof(PRODUCTO), 1, catalogo);
        }
        fclose(catalogo);        
        return -3; // ID no encontrado      
    }
}
/* Para conocer el numero de caracteres en una cadena */
int obtenerTam(char *cad){
    char aux[400];
    strcpy(aux, cad);
    int contador;
    for(contador=0; aux[contador]!='\0'; contador++);
    
    return contador;
}

/* Obtenemos algun id disponible para un nuevo cliente */
int obtenerNuevoIDcliente(){ 
	FILE *clientes = fopen("clientes.bin", "rb");
    char *aux;
    char *c_aux=(char*)malloc(sizeof(char)*50);
    int id;
    char comp;
    aux = fgets(c_aux, 50, clientes);
    int i=0;
    while(aux != NULL){
        id = strtol((c_aux+1), &c_aux, 10); //Obtiene lo que no sea caracter 
                                //se pone c_aux+1 por el espacio que se tiene al principio
        if(id != i){
            fclose(clientes);
            return id;
        }
        aux = fgets(c_aux, 50, clientes);
        //id es el que leo del archivo
        i++; //contador con el que se compara        
    }
    fclose(clientes);
    return i; //SI van en orden regresa el id que le sigue
}

/* Creamos un carrito para cada cliente, esto pasa después de crearlos */
int crearCarrito(char *email){ 
    if(fopen("carritos.bin", "rb") == NULL){ // Comprueba si no existe el archivo de carritos
        crearCarritos();
        return -1; // error, no existe
    }
     else{
        key_t llave_car = ftok("carritos", 1);
        int semcar = semget(llave_car, 1, IPC_CREAT|PERMISOS);
        if(semctl(semcar, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
            semctl(semcar, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado

            /* Creamos un carrito*/
            CARRITO car;
            strcpy(car.email, email);
            car.n_productos = 0;
            car.precio_total = 0;
            FILE *carritos = fopen("carritos.bin", "ab");
            fwrite(&car, sizeof(CARRITO), 1, carritos);

            fclose(carritos);
            semctl(semcar, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
            return 0;
        }
        else{
            return -2; // error, carritos ocupado
        }        
    }
}

/* Agregamos un cliente*/
int agregarCliente(char *nombre, char *email,  char *contrasena){ // Agregamos un cliente 
    if(fopen("clientes.bin", "rb") == NULL){ // Comprueba si no existe el archivo de clientes
        crearClientes();
        return -1; // error, no existe
    }
     else{
        key_t llave_cli = ftok("clientes", 1);
        int semcli = semget(llave_cli, 1, IPC_CREAT|PERMISOS);
        if(semctl(semcli, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
            semctl(semcli, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado

            /* Creamos un cliente*/
            CLIENTE cli;
            cli.id_cliente = obtenerNuevoIDcliente();
            strcpy(cli.nombre_cliente, nombre);
            strcpy(cli.contrasena, contrasena);
            strcpy(cli.email, email);
            
            /* Creamos su carrito */
            int operacion;
            do{
                operacion = crearCarrito(email); // Creamos su carrito
            }while (operacion < 0);          
            
            
            FILE *clientes = fopen("clientes.bin", "ab");
            fwrite(&cli, sizeof(CLIENTE), 1, clientes);

            fclose(clientes);
            semctl(semcli, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
            return 0;
        }
        else{
            return -2; // error, clientes ocupado
        }        
    }
}

/* Comprobamos que el correo exista y la contraseña sea correcta para que el cliente pueda iniciar sesión */
int comprobarCredenciales(char *email, char *contrasena){ 
    if(fopen("clientes.bin", "rb") == NULL){ // Comprueba si no existe el archivo de clientes
        crearClientes();
        return -1; // error, no existe
    }
     else{
        /* Creamos un cliente*/
        CLIENTE cli;
        FILE *clientes = fopen("clientes.bin", "rb");
        
        fread(&cli, sizeof(CLIENTE), 1, clientes);
        while(!feof(clientes)){
            if(strcmp(cli.email, email) == 0){ // checamos que exista el correo
                if(strcmp(cli.contrasena, contrasena) == 0){ // checamos que sea correcta la contraseña
                    fclose(clientes); 
                    return 0;
                }
                return -3; // Contraseña incorrecta
            }
            fread(&cli, sizeof(CLIENTE), 1, clientes);
        }
        fclose(clientes);        
        return -2; // Correo no encontrado       
    }
}

/* Agregamos un producto al carrito de un cliente */
int agregarACarrito(char *email, int id, int cantidad){ 
    if(fopen("carritos.bin", "rb") == NULL){ // Comprueba si no existe el archivo del carritos
        crearCarritos();    

        /* Creamos su carrito */
            int operacion;
            do{
                operacion = crearCarrito(email); // Creamos su carrito
            }while (operacion < 0);             
        return -1; // error, no existe
    }
    else{
        key_t llave_car = ftok("carritos", 1);
        int semcar = semget(llave_car, 1, IPC_CREAT|PERMISOS);
        //printf("%d", semctl(semcar, 0, GETVAL, 0));

        if(semctl(semcar, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
            semctl(semcar, 0, SETVAL, 0);
            
            // Consultamos disponibilidad
            int respuesta = consultarDisponibilidad(id);
            if(respuesta >= cantidad){ // Si hay disponibles
                printf("%d \n", descontarDeStock(id, cantidad)); // Descontamos lo que apartamos
                /* Creamos un carrito*/
                CARRITO car;            
                FILE *carritos = fopen("carritos.bin", "r+b");  
                fread(&car, sizeof(CARRITO), 1, carritos);
                //printf("%s, %s \n", email, car.email);
                
                while(!feof(carritos)){
                   
                    if(strcmp(car.email, email) == 0){
                        
                        // Creamos el producto que va ingresar
                        PRODUCTO prod;
                        prod.id_producto = id;
                        // Obtenemos el nombre con el id
                        char *nombre = (char *) malloc(sizeof(char)*30);
                        consultarNombre(id, nombre);
                        strcpy(prod.nombre_producto, nombre);
                        
                        // Obtenemos el precio con el id
                        float precio = consultarPrecio(id);
                        prod.precio = precio;
                        // Asignamos la cantidad a ser comprada
                        prod.cantidad = cantidad;
                        
                        car.precio_total = car.precio_total + (prod.cantidad*prod.precio); // Sumamos el precio que ya estaba con lo que tenemos aquí

                        /* Comprobamos si ya esta el producto en el carrito*/
                        int mismo_producto = 0;
                        for(int i = 0; i < car.n_productos; i++){
                            if(car.productos[i].id_producto == id){ // Si llegase a ser lo mismo que otro carrito 
                                car.productos[i].cantidad += cantidad;
                                mismo_producto = 1;
                            }
                        }
                        if(mismo_producto == 0){
                            car.productos[car.n_productos] = prod;
                            car.n_productos++;
                        }
                        
                        // Actualizamos el carrito en el archivo 
                        int pos = ftell(carritos) - sizeof(CARRITO); //actualiza el puntero
					    fseek(carritos, pos, SEEK_SET);
					    fwrite(&car, sizeof(CARRITO), 1, carritos); //escribimos la estructura modificada
                        
                        /* Cerramos todo */
                        fclose(carritos);
                        semctl(semcar, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
                        return 0;
                    }
                    fread(&car, sizeof(CARRITO), 1, carritos);					
                }                
                fclose(carritos);      
                semctl(semcar, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
                return -10; // Correo no encontrado
            }
            else{ // Hubo algún error y lo notificamos
                semctl(semcar, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
                return -5; // No hay suficiente stock
            }
        }
        else{
            return -2; // error, carritos ocupado
        }  
            
    }
}

/* Agregamos un producto al carrito de un cliente */
int obtenerCarrito(char *email, CARRITO *c){ 
    if(fopen("carritos.bin", "rb") == NULL){ // Comprueba si no existe el archivo del carritos
        crearCarritos();    

        /* Creamos su carrito */
            int operacion;
            do{
                operacion = crearCarrito(email); // Creamos su carrito
            }while (operacion < 0);             
        return -1; // error, no existe
    }
    else{

         /* Creamos un carrito*/
        CARRITO car;            
        FILE *carritos = fopen("carritos.bin", "rb");  
        fread(&car, sizeof(CARRITO), 1, carritos);

        while(!feof(carritos)){                   
            if(strcmp(car.email, email) == 0){
                for(int i = 0; i < NPRODS; i++){
                    (*c).productos[i] = car.productos[i];
                }
                (*c).n_productos = car.n_productos;
                (*c).precio_total = car.precio_total;
                fclose(carritos); 
                return 0;
            }
            fread(&car, sizeof(CARRITO), 1, carritos);					
        }                
        fclose(carritos);
        return -2; //Carrito no encontrado
    }
}

/* Vaciamos el carrito porque ya "se hizo" el pago */
int pagarCarrito(char *email){ 
    if(fopen("carritos.bin", "rb") == NULL){ // Comprueba si no existe el archivo de carritos
        crearCarritos();
        return -1; // error, no existe
    }
     else{
        key_t llave_car = ftok("carritos", 1);
        int semcar = semget(llave_car, 1, IPC_CREAT|PERMISOS);
        if(semctl(semcar, 0, GETVAL, 0) > 0){ // Comprobamos que no esté ocupado
            semctl(semcar, 0, SETVAL, 0); // asignamos a 0 para decir que está ocupado

            /* Creamos un carrito*/
            CARRITO car;
            strcpy(car.email, email);
            car.n_productos = 0;
            
            FILE *carritos = fopen("carritos.bin", "ab");
            fwrite(&car, sizeof(CARRITO), 1, carritos);
             while(!feof(carritos)){
                if(strcmp(car.email, email) == 0){ // checamos que exista el correo
                    // Eliminamos productos
                    PRODUCTO prod;
                    for(int i = 0; i < car.n_productos; i++){
                        car.productos[i] = prod;
                    }                      
                    // Reseteamos contadores
                    car.n_productos = 0;
                    car.precio_total = 0;

                    fclose(carritos);      
                    semctl(semcar, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
                    return 0;
                }
                fread(&car, sizeof(CARRITO), 1, carritos);
            }
            fclose(carritos);      
            semctl(semcar, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
            return -5; // Correo no encontrado 
        }
        else{
            return -2; // error, carritos ocupado
        }        
    }
}

/* Funcion temporal */
void listado()
{
    FILE *catalogo;
    catalogo=fopen("catalogo.bin","rb");
    if (catalogo==NULL)
        exit(1);
    PRODUCTO producto;
    fread(&producto, sizeof(PRODUCTO), 1, catalogo);
    while(!feof(catalogo))
    {
        printf("Producto: %s\n", producto.nombre_producto);
        printf("Precio: %0.2f\n", producto.precio);
        printf("ID: %d\n", producto.id_producto);
        printf("Articulos existentes: %d\n \n \n", producto.cantidad);

        fread(&producto, sizeof(PRODUCTO), 1, catalogo);
    }
    fclose(catalogo);

}
