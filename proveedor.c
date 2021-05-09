/* Programa principal del proveedor*/ 

# include <stdio.h>
# include <stdlib.h>
# include "funcioneskernel.c"
void main(){
	int op;
	char aux;
	do{
		printf("Bienvenido! \nQue desea hacer?\n");
		printf("1. Agregar existencia.\n");
		printf("2. Agregar articulo.\n");
		printf("3. Buscar articulo.\n");
		printf("4. Salir.\n");
		scanf("%d", &op);
		
		switch (op){
		case 1:			
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
			
			int resultado_operacion;
			
			do{
				resultado_operacion = agregarArticulo(nombre, cantidad, precio); // Comprueba que se ejecute correctamente
				//printf("%d \n", resultado_operacion);
			}while(resultado_operacion < 0);

					
			
			break;
		case 3:
			break;
		}
	}while (op != 4);
	
	
}
