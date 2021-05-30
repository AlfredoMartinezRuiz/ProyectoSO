/* Programa principal del cliente*/ 

# include <stdio.h>
# include <stdlib.h>
# include "funcioneskernel.c"


void mostrarProductos(){
	PRODUCTO productos[100];
	obtenerProductos(productos);
	printf("Mostrando lista de productos...\n");
	printf("ID   |                 Nombre                |   Cantidad disp.  |  Precio/U |\n");
	
	for(int i = 0; productos[i].cantidad != 0 ; i++){
		// impresion del id
		if(productos[i].id_producto > 9){					
			printf(" %d  |", productos[i].id_producto);
		} 
		else{
			printf(" %d   |", productos[i].id_producto);
		}
		
		// impresion del nombre
		printf(" %s", productos[i].nombre_producto);
		for(int o = 0; o < 38 - obtenerTam(productos[i].nombre_producto); o++){
			printf(" ");
		}
		printf("|");
		
		// Impresion de la cantidad 
		if(productos[i].cantidad > 9){					
			printf(" %d                |", productos[i].cantidad);
		} 
		else{
			printf(" %d                 |", productos[i].cantidad);
		}

		// Impresion del precio unitario 
		if(productos[i].precio > 9){					
			printf(" %0.2f     |", productos[i].precio);
		}  
		else{
			printf(" %0.2f      |", productos[i].precio);
		}
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
			
			scanf("%d", &op);

			int resultado_operacion = 0;
			int id;
			switch (op){ 
			case 1:;	// Mostrar todos los productos
				listado();
				sleep(2);
				//printf("Presione una tecla para continuar\n\n");
				//getc(stdin);
				break;

			case 2: ; // Agregar articulo a carrito
				int cantidad;
				listado();
				printf("Ingresa el ID del articulo\n");
				scanf("%d", &id);
				printf("Ingresa la cantidad del articulo\n");
				scanf("%d", &cantidad);

				do{
					resultado_operacion = agregarACarrito(email, id, cantidad); // Comprobemos que no haya ningun error en la operacion
					if(resultado_operacion == -5)
						printf("Error: Producto no encontrado, o no hay stock\n");				
					if(resultado_operacion < 0)
						printf("Codigo: %d\n", resultado_operacion);
					sleep(1);
				}while(resultado_operacion < 0 && resultado_operacion!=-5);
				printf("Operacion exitosa!\n");
				printf("Volviendo al menu...\n");
				sleep(5);			
				break;

			case 3:; // Ver el carrito completo
				system("clear");
				CARRITO car;
				fflush(stdout);
				obtenerCarrito(email, &car);
				printf("Productos: \n");
				for(int i = 0; i < car.n_productos; i++){
					printf("	Nombre: %s \n", car.productos[i].nombre_producto);
					printf("	Precio: %0.2f \n", car.productos[i].precio);
					printf("	Cantidad: %d \n", car.productos[i].cantidad);
					printf("--------------------------------------------------------------- \n");
				}
				printf("Precio final con IVA: %0.2f \n", car.precio_total);
				sleep(5);
				break;
			case 4:; // Pagar carrito
				break;
			}
		}while (op != 5);
	}
}

void registrarUsuario(){
	//agregarCliente(1, "Juan Pablo II", "Juanpablo@gmail.com", "Lola");
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
		//printf("%d \n", res);
	}while(res < 0);	
	printf("Registro existoso!");
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
				//listado();
				//printf("Presione una tecla para continuar\n\n");
				//getc(stdin);
				break;
			case 2: //iniciar sesion
				iniciarSesion();
				system("clear");
				break;
			case 3: //Registrar nuevo usuario
				registrarUsuario();
				sleep(3);
				break;
		}
		
	}while(op != 4);
	
}
