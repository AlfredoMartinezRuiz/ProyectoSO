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
			char nombre[30];
			int cantidad;
			float precio;
			system("clear");
			printf("Por favor, indique el nombre del articulo: \n");
			scanf("%c", &aux);
			fgets(nombre, 30, stdin);		
			printf("Por favor, indique la cantidad del articulo: \n");
			scanf("%d", &cantidad);
			printf("Por favor, indique su precio del articulo: \n");
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
