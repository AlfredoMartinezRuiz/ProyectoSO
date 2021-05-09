/* Programa principal del kernel*/ 

# include <stdio.h>
# include "funcioneskernel.c"
int main(){	
	// Comprobamos que estén creados los archivos necesarios para la ejecución
	comprobarCatalogo();
	comprobarCarritos();
	comprobarClientes();
	agregarCliente();
	agregarCliente();
	leerCliente();
	return 0;
}
