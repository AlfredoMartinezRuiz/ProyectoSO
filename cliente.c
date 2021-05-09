/* Programa principal del cliente*/ 

# include <stdio.h>
# include <stdlib.h>
# include "funcioneskernel.c"

void mostrarProductos(){
	PRODUCTO productos[100]; 
	obtenerProductos(productos);
	printf("Mostrando lista de productos...\n");
	printf("ID   |                 Nombre                |   Cantidad disp.  |  Precio/U \n");
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
		for(int o = 0; o < 30 - sizeof(productos[i].nombre_producto); o++){
			printf(" ");
		}
		printf("|");
		// Impresion de la cantidad 
		if(productos[i].cantidad > 9){					
			printf(" %d               |", productos[i].cantidad);
		} 
		else{
			printf(" %d                |", productos[i].cantidad);
		}

		// Impresion del precio unitario 
		if(productos[i].precio > 9){					
			printf(" %f               |", productos[i].precio);
		} 
		else{
			printf(" %f                |", productos[i].precio);
		}
		printf("\n");
	}
}

void main(){
	int op;
	char aux;
	char *email = (char*)malloc(sizeof(char)*30);
	char *contrasena = (char*)malloc(sizeof(char)*30);

	printf("Ingrese su correo: ");
	scanf("%d", &op);
	fgets(email, 30, stdin);
	strtok(email, "\n");

	printf("Ingrese su contraseña: ");
	scanf("%d", &op);
	fgets(contrasena, 30, stdin);
	strtok(contrasena, "\n");

	if(comprobarCredenciales(email, contrasena)  == -2){
		printf("Correo no encontrado \n");
	}
	else if(comprobarCredenciales(email, contrasena)  == -3){
		printf("Contrasna incorrecta \n");
	}
	else{
		do{
		system("clear");
		printf("Bienvenido! \nQue desea hacer?\n");
		printf("1. Ver productos.\n");
		printf("2. Agregar a carrito\n");
		printf("3. Ver carrito.\n");
		printf("4. Pagar carrito.\n");
		printf("5. Salir.\n");
		scanf("%d", &op);

		int resultado_operacion;
		int id;
		switch (op){ 
		case 1:;	// Mostrar todos los productos
			mostrarProductos();
			printf("Presione una tecla para continuar\n\n");
    		getc(stdin);
			break;

		case 2: ; // Agregar articulo a carrito
			int cantidad;
			mostrarProductos();
			printf("Ingresa el ID del articulo\n");
			scanf("%d", &id);
			printf("Ingresa la cantidad del articulo\n");
			scanf("%d", &cantidad);
			do{
				resultado_operacion = agregarACarrito(email, id, cantidad); // Comprobemos que no haya ningun error en la operacion
				if(resultado_operacion == -5){
					printf("Error: Producto no encontrado, o no hay stock \n");
				}
			}while(resultado_operacion < 0);
			printf("Operacion exitosa!\n");
			printf("Volviendo al menu...\n");
			sleep(1);			
			break;

		case 3:; // Ver el carrito completo
			
			break;
		case 4:; // Pagar carrito
			
			break;
		}
	}while (op != 5);
	}
	
	
	
}
