/* Programa principal del proveedor*/ 

# include <stdio.h>
# include <stdlib.h>
# include "funcioneskernel.c"

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
		sleep(1);
	}while(resultado_operacion < 0);
	printf("Operacion exitosa!\n");
	printf("Volviendo al menu...\n");
	sleep(1);			
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
	}while(resultado_operacion < 0);
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

		case 2: ;// Agregar artículo nuevo
			agregarNuevoArticulo();
			break;

		case 3:; // Buscar articulo por nombre
			buscarArticuloPorNombre();
			break;
		
		case 4:; //Ver articulos
			//mostrarProductos();
			listado();
			sleep(4);
			break;
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
		sleep(2);
	}
	else if(comprobacion == -3){
		printf("Contraseña incorrecta \n");
		printf("Volviendo a menu...\n");
		sleep(2);
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
		printf("%d \n", res);
	}while(res < 0);	
	printf("\nRegistro existoso!");
	
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
				sleep(2);
				break;
			case 2: //Registrar nuevo usuario
				registrarUsuario();
				sleep(3);
				break;
		}
		
	}while(op != 3);
	
}
