/* Programa principal del proveedor*/ 

# include <stdio.h>
# include <stdlib.h>
# include "funcioneskernel.c"


void mostrarProductos(){

	FILE *catalogo;
    catalogo=fopen("catalogo.bin","rb");
    if (catalogo==NULL){
        printf("No hay articulos disponibles \n\n\n");
        printf("Volviendo a menu...\n");
        sleep(2);
        system("clear");
    }
    else{
    	key_t llave_cat = ftok("/tmp", 1);
		int semcat = semget(llave_cat, 1, IPC_CREAT|PERMISOS);
	//PRODUCTO productos[100];
//	int n_productos = obtenerProductos(productos);
    PRODUCTO productos;
	printf("Mostrando lista de productos...\n");
	printf("ID   |                 Nombre                |   Cantidad disp.  |  Precio/U |\n");
	fread(&productos, sizeof(PRODUCTO), 1, catalogo);
	while(!feof(catalogo)){
		//if(productos.cantidad > 0){
			// impresion del id
			if(productos.id_producto > 99){					
				printf(" %d |", productos.id_producto);
			} 
			else if(productos.id_producto > 9){					
				printf(" %d  |", productos.id_producto);
			} 
			else{
				printf(" %d   |", productos.id_producto);
			}
			
			// impresion del nombre
			printf(" %s", productos.nombre_producto);
			for(int o = 0; o < 38 - obtenerTam(productos.nombre_producto); o++){
				printf(" ");
			}
			printf("|");
			
			// Impresion de la cantidad 
			if(productos.cantidad > 99){					
				printf(" %d               |", productos.cantidad);
			}
			else if(productos.cantidad > 9){					
				printf(" %d                |", productos.cantidad);
			} 
			else{
				printf(" %d                 |", productos.cantidad);
			}

			// Impresion del precio unitario 
			if(productos.precio > 99){					
				printf(" %0.2f    |", productos.precio);
			}
			else if(productos.precio > 9){					
				printf(" %0.2f     |", productos.precio);
			}  
			else{
				printf(" %0.2f      |", productos.precio);
			}
			printf("\n");
		//}	
		fread(&productos, sizeof(PRODUCTO), 1, catalogo);			
	}
	semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
	fclose(catalogo);
	printf("\n");
	}
}

void agregarCantidadArticulo(){
	int id; 
	int resultado_operacion;
	int cantidad_aumentada;
	int indice_archivo;

	system("clear");
	printf("Agregar existencia\n");	
	
	printf("Cantidad a aumentar: \n");
	scanf("%d", &cantidad_aumentada);
	do{
		printf("ID del articulo: \n");
		scanf("%d", &id);

		resultado_operacion = agregarCantidad(id, cantidad_aumentada); // Comprueba que se ejecute correctamente
		//printf("res_agregarCantidad: %d \n", resultado_operacion);
		if(resultado_operacion == -3){
			printf("Error: Producto no encontrado, intente de nuevo\n");
		}
		//sleep(1);
	}while(resultado_operacion < 0);
	printf("Operacion exitosa!\n");
	printf("Volviendo al menu...\n");
//	sleep(1);			
}

void agregarNuevoArticulo(){
	int op;
	int resultado_operacion;
	char *nombre = (char*)malloc(sizeof(char)*30);
	int cantidad;
	float precio;

	system("clear");
	printf("Agregar articulo\n");

	printf("Nombre del articulo: \n");
	scanf("%d", &op);
	fgets(nombre, 30, stdin);
	strtok(nombre, "\n");

	printf("Stock: \n");
	scanf("%d", &cantidad);

	printf("Precio por unidad: \n");
	scanf("%f", &precio);
				
	do{
		resultado_operacion = agregarArticulo(nombre, cantidad, precio); // Comprueba que se ejecute correctamente
		//printf("res_agregarArticulo: %d \n", resultado_operacion);
		sleep(1);
	}while(resultado_operacion < 0);					
	printf("Operacion exitosa!\n");
	printf("Volviendo al menu...\n");
	sleep(1);			
}

void buscarArticuloPorNombre(){
	int op;
	int resultado_operacion;
	char *nombre_buscar= (char*)malloc(sizeof(char)*30);
	system("clear");
	printf("Buscar articulo\n");
	
	do{
		printf("Nombre exacto del articulo (mayusculas y minusculas): \n");
		scanf("%d", &op);
		fgets(nombre_buscar, 30, stdin);
		strtok(nombre_buscar, "\n");
		
		resultado_operacion = buscarporNombre(nombre_buscar); // Comprueba que se ejecute correctamente y guarda el id para mostrarlo
		if(resultado_operacion == -3){
			printf("ID no encontrado, verifique el nombre. \n");
		}
		else{
			printf("ID de %s es: %d \n", nombre_buscar, resultado_operacion);
			
		}
		//printf("%d \n", resultado_operacion);
	}while(resultado_operacion == -1);
	printf("Presione una tecla para volver al menu\n");
	getchar();
}

void menu(){
	int op;
	char aux;
	do{
		system("clear");
		
		printf("\nBienvenido! \nQue desea hacer?\n");
		printf("1. Agregar existencia.\n");
		printf("2. Agregar articulo.\n");
		printf("3. Buscar articulo por nombre.\n");
		printf("4. Ver productos.\n");
		printf("5. Salir.\n");
		scanf("%d", &op);
		
		switch (op){ 
		case 1:	// Agregar cantidad de artículos
			agregarCantidadArticulo();
			break;

		case 2: // Agregar artículo nuevo
			agregarNuevoArticulo();
			break;

		case 3: // Buscar articulo por nombre
			buscarArticuloPorNombre();
			break;
		
		case 4: //Ver articulos
			mostrarProductos();
			sleep(2);
			break;
		case 5:
			printf("Saliendo de su sesión\n");
			break;

			default:
			printf("Opción inválida, eliga una opción válida, por favor\n");
		}
	}while (op != 5);
	
	
}

void iniciarSesion(){
	int op;
	char aux;
	char *email = (char*)malloc(sizeof(char)*30);
	char *contrasena = (char*)malloc(sizeof(char)*30);

	printf("Identifícate\n\n");
	printf("Email: ");
	scanf("%d", &op);
	fgets(email, 30, stdin);
	strtok(email, "\n");

	printf("Contraseña: ");
	scanf("%d", &op);
	fgets(contrasena, 30, stdin);
	strtok(contrasena, "\n");
	int comprobacion = comprobarCredencialesP(email, contrasena);
	printf("%d\n", comprobacion);
	if(comprobacion == -2 || comprobacion == -1){
		printf("Email no encontrado \n");
		printf("Volviendo a menu...\n");
		//sleep(1);
	}
	else if(comprobacion == -3){
		printf("Contraseña incorrecta \n");
		printf("Volviendo a menu...\n");
		//sleep(1);
	}
	else{
		menu();
	}
}

void registrarUsuario(){
	int op,res;
	char *email = (char*)malloc(sizeof(char)*30);
	char *contrasena = (char*)malloc(sizeof(char)*30);
	char *nombre = (char*)malloc(sizeof(char)*30);
	char *rfc = (char*)malloc(sizeof(char)*30);

	printf("Provedoor Nuevo de QuickBuy\n");

	printf("Nombre: ");
	scanf("%d", &op);
	fgets(nombre, 30, stdin);
	strtok(nombre, "\n");

	printf("E-mail: ");
	scanf("%d", &op);
	fgets(email, 30, stdin);
	strtok(email, "\n");

	printf("RFC: ");
	scanf("%d", &op);
	fgets(rfc, 30, stdin);
	strtok(rfc, "\n");

	printf("Contraseña: ");
	scanf("%d", &op);
	fgets(contrasena, 30, stdin);
	strtok(contrasena, "\n");

	do{
		res = agregarProveedor(nombre,email,rfc,contrasena); // Comprueba que se ejecute correctamente
		if(res == -1){
			printf("El archivo proveedores no existe\n");
		}
		else{
			printf("Archivo proveedores existente\n");
			if(res == -2){
				printf("Por favor espere\n");//Archivo proveedores.bin ocupado
				}
			else if(res == 0){
				printf("\nRegistro existoso!");
				}
			else{
				printf("Error fatal\n");//Error no registrado
				}
			}
	}while(res < 0);	
	
}

void main(){
	int op;

	do{
		printf("\n¡Bienvenido a QuickBuy!\n");
		printf("1. Iniciar sesión\n");
		printf("2. Registrarse\n");
		printf("3. Salir\n");
		scanf("%d", &op);

		switch(op){
			case 1: //iniciar sesion
				iniciarSesion();
				//sleep(1);
				break;
			case 2: //Registrar nuevo usuario
				registrarUsuario();
				//sleep(1);
				break;
			case 3:
				printf("Gracias, saliendo del programa\n");
				break;

			default:
				printf("Opción inválida, eliga una opción válida, por favor\n");	
		}
		
	}while(op != 3);
	
}
