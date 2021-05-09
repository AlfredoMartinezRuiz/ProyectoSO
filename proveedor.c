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
		printf("4. Salir.\n");
		scanf("%d", &op);
		
		int resultado_operacion;
		switch (op){ 
		case 1:;	// Agregar cantidad de artículos
			int id; 
			int cantidad_aumentada;
			int indice_archivo;

			system("clear");
			printf("Agregar articulo\n");	

			printf("ID del articulo: \n");
			scanf("%d", &id);
			indice_archivo = buscarporID(id); // Solicitamos el indice para saber en que linea del archivo buscar
			if(indice_archivo >= 0){
				printf("Cantidad a aumentar: \n");
				scanf("%d", &id);

				do{
					resultado_operacion = agregarCantidad(id, cantidad_aumentada, indice_archivo); // Comprueba que se ejecute correctamente
					//printf("%d \n", resultado_operacion);
				}while(resultado_operacion < 0);
				printf("Operacion exitosa!\n");
				printf("Volviendo al menu...\n");
				sleep(1);
			}
			else{
				printf("Articulo no encontrado, verifique su ID\n");
			}
			
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
			}while(resultado_operacion < 0);					
			printf("Operacion exitosa!\n");
			printf("Volviendo al menu...\n");
			sleep(1);
			
			break;
		case 3:; // Buscar articulo por nombre
			char *nombre_buscar= (char*)malloc(sizeof(char)*30);
			system("clear");
			printf("Buscar articulo\n");	

			printf("Nombre exacto del articulo (mayusculas y minusculas): \n");
			scanf("%d", &op);
			fgets(nombre_buscar, 30, stdin);
			strtok(nombre_buscar, "\n");
			do{
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
		}
	}while (op != 4);
	
	
}
