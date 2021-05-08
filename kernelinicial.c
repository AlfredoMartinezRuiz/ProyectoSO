/* Programa principal del kernel*/ 

# include <stdio.h>
int main(){
	
	/* c�digo principal de ejecuci�n */
	
	pid_t pid;
	pid = fork();
	if(pid==-1){
		perror("\nError al crear el proceso\n");
		exit(-1);
	}
	if(pid == 0){ // Proceso encargado de manejar archivo de cat�logo -> Hijo 1
		
	exit(0);	
	}
	
	else{ 
		pid = fork();
		if(pid == 0){ // Proceso encargado de manejar archivo de clientes -> Hijo 2
		
		exit(0);	
		}
		else{
			pid = fork();
			if(pid == 0){ // Proceso encargado de manejar archivo de carritos -> Hijo 3
		
			exit(0);	
			}
			else{ // Proceso encargado de controlar los semaforos -> Padre
				//Padre iria actualizando el semaforo para sus 3 hijos 
			}
			
		}
	}	
	
	return 0;
}
