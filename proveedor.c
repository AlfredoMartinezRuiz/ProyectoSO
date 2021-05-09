/* Programa principal del proveedor*/ 

# include <stdio.h>
# include <stdlib.h>
# include "funcioneskernel.c"
void main(){
	int op;
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
			char nombre[20];
			int cantidad;
			int precio;
			system("clear");
			printf("Por favor, indice el nombre del articulo: \n");
			scanf("%d", &op);
			fgets(nombre, 20, stdin);		
			printf("Por favor, indice la cantidad del articulo: \n");
			scanf("%d", &cantidad);
			printf("Por favor, indice su precio del articulo: \n");
			scanf("%d", &precio);
			
			break;
		case 3:
			break;
		}
	}while (op != 4);
	
	
}
