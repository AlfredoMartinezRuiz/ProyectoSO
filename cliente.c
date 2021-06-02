/* Programa principal del cliente*/ 

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
		if(productos.cantidad > 0){
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
		}	
		fread(&productos, sizeof(PRODUCTO), 1, catalogo);			
	}
	semctl(semcat, 0, SETVAL, 1); // asignamos a 1 para decir que ya no está ocupado
	fclose(catalogo);
	printf("\n");
	}
}


void iniciarSesion(){
	int op;
	char aux;
	char *email = (char*)malloc(sizeof(char)*30);
	char *contrasena = (char*)malloc(sizeof(char)*30);

	printf("Identifícate\n\n");
	printf("E-MAIL: ");
	scanf("%d", &op);
	fgets(email, 30, stdin);
	strtok(email, "\n");

	printf("Contraseña: ");
	scanf("%d", &op);
	fgets(contrasena, 30, stdin);
	strtok(contrasena, "\n");
	int comprobacion = comprobarCredenciales(email, contrasena);

	if(comprobacion == -2 || comprobacion == -1){
		printf("Correo no encontrado \n");
		printf("Volviendo a menu...\n");
		sleep(2);
	}
	else if(comprobacion == -3){
		printf("Contraseña incorrecta \n");
		printf("Volviendo a menu...\n");
		sleep(2);
	}
	else{
		do{
			system("clear");
			printf("¡Hola! \nQue desea hacer?\n");
			printf("1. Ver productos.\n");
			printf("2. Agregar a carrito\n");
			printf("3. Ver carrito.\n");
			printf("4. Pagar carrito.\n");
			printf("5. Salir.\n");
			fflush(stdin);
			scanf("%d", &op);

			int resultado_operacion = 0;
			int id;
			switch (op){ 
			case 1:;	// Mostrar todos los productos
				mostrarProductos();
				sleep(2);
				break;

			case 2: ; // Agregar articulo a carrito
				int cantidad;
				mostrarProductos();
				fflush(stdin);
				printf("Ingresa el ID del articulo\n");
				scanf("%d", &id);
				printf("Ingresa la cantidad del articulo\n");
				scanf("%d", &cantidad);

				do{
					resultado_operacion = agregarACarrito(email, id, cantidad); // Comprobemos que no haya ningun error en la operacion
					if(resultado_operacion == -1){
						printf("Error: No existe el archivo carritos\n");			
					}
					else if(resultado_operacion == -2){
						printf("Por favor espere\n"); //Archivo carritos.bin ocupado
					}
					else if(resultado_operacion == -5){
						printf("Error: Producto no encontrado, o no hay stock\n");
					}
					else if(resultado_operacion == -10){
						printf("Error: Email no encontrado\n");
					}
					else if(resultado_operacion == 0){
						printf("Operacion exitosa!\n");
						printf("Volviendo al menu...\n");
					}
					else{
						printf("Error fatal\n");//Error no registrado
					}
					//sleep(1);
					}while(resultado_operacion < 0 && resultado_operacion!=-5);

				sleep(1);			
				break;

			case 3:; // Ver el carrito completo
				system("clear");
				CARRITO car;
				fflush(stdout);
				resultado_operacion = obtenerCarrito(email, &car);

				do{

					if(resultado_operacion == -1){
						printf("Error: No existe el archivo carritos\n");
						}
					else if(resultado_operacion == -2){
						printf("Error: Carrito no encontrado\n");
						}
					else if(resultado_operacion == 0){
						printf("Productos: \n");
						for(int i = 0; i < car.n_productos; i++){
						printf("	Nombre: %s \n", car.productos[i].nombre_producto);
						printf("	Precio: %0.2f \n", car.productos[i].precio);
						printf("	Cantidad: %d \n", car.productos[i].cantidad);
						printf("--------------------------------------------------------------- \n");
					}
					printf("Precio final con IVA: %0.2f \n", car.precio_total);
					}
					else{
						printf("Error fatal\n");//Error no registrado
						}
				}while(resultado_operacion < 0);

				sleep(2);
				break;


			case 4:; // Pagar carrito
				fflush(stdin);

				resultado_operacion = pagarCarrito(email);

				do{
					if(resultado_operacion == -1){
						printf("Error: No existe el archivo carritos\n");
						}
					else if(resultado_operacion == -2){
						printf("Por favor, espere\n");//Archivo carritos.bin ocupado
						}
					else if(resultado_operacion == -5){
						printf("Error: Email no encontrado\n");
						}
					else if(resultado_operacion == 0){
						printf("Operacion exitosa!\n");
						printf("Volviendo al menu...\n");
					}
					else{
						printf("Error fatal\n");//Error no registrado
						}
				}while(resultado_operacion < 0);

				sleep(2);
				break;
			}
		}while (op != 5);
	}
}

void registrarUsuario(){
	int op,res;
	char *email = (char*)malloc(sizeof(char)*30);
	char *contrasena = (char*)malloc(sizeof(char)*30);
	char *nombre = (char*)malloc(sizeof(char)*30);

	printf("Cliente Nuevo de QuickBuy\n");

	printf("Nombre: ");
	scanf("%d", &op);
	fgets(nombre, 30, stdin);
	strtok(nombre, "\n");

	printf("E-mail: ");
	scanf("%d", &op);
	fgets(email, 30, stdin);
	strtok(email, "\n");

	printf("Contraseña: ");
	scanf("%d", &op);
	fgets(contrasena, 30, stdin);
	strtok(contrasena, "\n");

	do{
		res = agregarCliente(nombre,email,contrasena); // Comprueba que se ejecute correctamente
	}while(res < 0);	
	printf("Registro existoso!\n\n");
}

void main(){
	int op;

	do{
		printf("¡Bienvenido a QuickBuy!\n");
		printf("1. Ver productos\n");
		printf("2. Iniciar sesión\n");
		printf("3. Registrarse\n");
		printf("4. Salir\n");
		scanf("%d", &op);

		switch(op){
			case 1: //Muestra todos los productos
				mostrarProductos();
				break;
			case 2: //iniciar sesion
				iniciarSesion();
				system("clear");
				break;
			case 3: //Registrar nuevo usuario
				registrarUsuario();
				//sleep(1);
				break;
		}
		
	}while(op != 4);
	
}
