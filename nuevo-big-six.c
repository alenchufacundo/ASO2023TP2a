#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#define NUMBER_OF_THREADS 2
#define CANTIDAD_INICIAL_HAMBURGUESAS 20
int cantidad_restante_hamburguesas = CANTIDAD_INICIAL_HAMBURGUESAS;
bool want[NUMBER_OF_THREADS] = {false};
int turno = 0;

void *comer_hamburguesa(void *tid) {
    int mi_tid = (int)tid;

    while (cantidad_restante_hamburguesas > 0) {
        while (turno != mi_tid)
            ; // Esperar a que sea mi turno

        // Sección crítica: comer una hamburguesa
        if (cantidad_restante_hamburguesas > 0) {
            printf("Hola! soy el hilo(comensal) %d , me voy a comer una hamburguesa ! ya que todavia queda/n %d\n", mi_tid, cantidad_restante_hamburguesas);
            cantidad_restante_hamburguesas--;
        } else {
            // Si no quedan hamburguesas, salgo del bucle
            break;
        }

        // Cambiar el turno al otro hilo
        turno = 1 - mi_tid;
    }

    printf("SE TERMINARON LAS HAMBURGUESAS :( \n"); 
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) { 
	pthread_t threads[NUMBER_OF_THREADS]; 
	int status,i,ret ; 
	for(int i=0; i < NUMBER_OF_THREADS; i++) { 
		printf("Hola!, soy el hilo principal. Estoy creando el hilo %d \n", i); 
		status = pthread_create(&threads[i], NULL, comer_hamburguesa, (void *)i); 
		if (status != 0) { 
		printf("Algo salio mal, al crear el hilo recibi el codigo de error %d \n", status);
		exit(-1); 
		} 
	} 

	for (i= 0; i < NUMBER_OF_THREADS; i++) {
        void *retval;
        ret = pthread_join(threads[i], &retval); //espero por la terminacion de los hilos que cree
        }
        pthread_exit(NULL); //como los hilos que cree ya terminaron de ejecutarse, termino yo tambien.

} 

