#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>

/* Definición del struct nodo
 */
 typedef struct nodo{
	 void* dato;
	 struct nodo* prox;
 }nodo_t;
 
 /* Definición del struct cola.
 */
 struct cola{
	 nodo_t* primero;
	 nodo_t* ultimo;
 };

/* ******************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* nodo_crear(void* valor) {
	nodo_t* nodo= malloc(sizeof(nodo_t));
	
	if(nodo == NULL) return NULL;
	
	nodo->dato= valor;
	nodo->prox= NULL;
	return nodo;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/
 
 cola_t* cola_crear(void) {
	 cola_t* cola= malloc(sizeof(cola_t));
	 
	 if(cola == NULL) return NULL;
	 
	 cola->primero= NULL;
	 cola->ultimo= NULL;
	 return cola;
 }
 
void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	while(!cola_esta_vacia(cola)) {
		void* eliminar= cola_desencolar(cola);
		if(destruir_dato != NULL) {
			destruir_dato(eliminar);
		}
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola) { 
	return cola->primero == NULL;
}

bool cola_encolar(cola_t *cola, void* valor) {
	nodo_t* nuevo_nodo= nodo_crear(valor);
	
	if(nuevo_nodo == NULL) return false;
	
	if(cola_esta_vacia(cola)){
		cola->primero= nuevo_nodo;
	}else {
		cola->ultimo->prox= nuevo_nodo;
	}
	cola->ultimo= nuevo_nodo;
	return true;
}

void* cola_ver_primero(const cola_t *cola) {
	if(cola_esta_vacia(cola)) return NULL;
	
	return cola->primero->dato;
}

void* cola_desencolar(cola_t *cola) {
	if(cola_esta_vacia(cola)) return NULL;
	
	nodo_t* aux= cola->primero;
	void* valor= cola->primero->dato;
	
	/* Si el primero y el ultimo son iguales, entonces la cola tiene un solo elemento,
	 * si lo desencolo la cola queda vacia.*/
	if(cola->primero == cola->ultimo) {
		cola->primero= NULL;
		cola->ultimo= NULL;
	}else {
		cola->primero= aux->prox;
	}
	free(aux);
	return valor;
}
