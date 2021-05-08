/* Programa principal del kernel*/ 

# include <stdio.h>
# include "funcioneskernel.c"
int main(){
	
	/* c�digo principal de ejecuci�n */
	comprobarCatalogo();
	comprobarCarritos();
	comprobarClientes();
	comprobarCatalogo();
	comprobarCarritos();
	comprobarClientes();
	
	return 0;
}
