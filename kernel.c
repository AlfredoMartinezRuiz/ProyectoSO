/* Programa principal del kernel*/ 

# include <stdio.h>
# include "funcioneskernel.c"
int main(){	
	// Comprobamos que estén creados los archivos necesarios para la ejecución
	comprobarCatalogo();
	comprobarCarritos();
	comprobarClientes();
	/* Aquí crearemos a los clientes que querramos y los administraremos, al igual que los productos*/
	agregarCliente("Juan Pablo II", "Juanpablo@gmail.com", "Lola");
	printf("%d", comprobarCredenciales("Juanpablo@gmail.com", "Lola"));
	crearCarrito("Juanpablo@gmail.com");
	

	return 0;
}
