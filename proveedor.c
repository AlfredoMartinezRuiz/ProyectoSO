/* Programa principal del proveedor*/ 

# include <stdio.h>
# include <stdlib.h>
# include "funcioneskernel.c"


void main(){
	int op;
	char aux;
	do{
		system("clear");
		printf("Bienvenido! \nQue desea hacer?\n");
		printf("1. Agregar existencia.\n");
		printf("2. Agregar articulo.\n");
		printf("3. Buscar articulo por nombre.\n");
		//printf("4. Ver productos.\n");
		printf("4. Salir.\n");
		scanf("%d", &op);
		
		int resultado_operacion;
		switch (op){ 
		case 1:;	// Agregar cantidad de artículos
			int id; 
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
				//printf("res: %d \n", resultado_operacion);
				if(resultado_operacion == -3){
					printf("Error: Producto no encontrado, intente de nuevo\n");
				}
				sleep(1);
			}while(resultado_operacion < 0);
			printf("Operacion exitosa!\n");
			printf("Volviendo al menu...\n");
			sleep(1);			
			break;

		case 2: ;// Agregar artículo nuevo
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
				//printf("%d \n", resultado_operacion);
				sleep(1);
			}while(resultado_operacion < 0);					
			printf("Operacion exitosa!\n");
			printf("Volviendo al menu...\n");
			sleep(1);			
			break;

		case 3:; // Buscar articulo por nombre
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
			break;
		
		case 4:; //Ver articulos
			//mostrarProductos();
			listado();
			sleep(2);
			break;
		}
	}while (op != 5);
	
	
}
