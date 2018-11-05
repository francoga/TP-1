#define _POSIX_C_SOURCE 200809L // getline
#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char SEP= ' ';
const char* SUMA= "+";
const char* RESTA= "-";
const char* MULTI= "*";
const char* DIV= "/";
const char* POT= "^";
const char* RAIZ= "sqrt";
const char* LOG= "log";
const char* TER= "?";

void destruir_pila(pila_t* pila) {
	if(!pila_esta_vacia(pila)) {
		free(pila_desapilar(pila));
	}
	pila_destruir(pila);
}

bool es_un_operador(char* string) {
	bool ok= false;
	
	if(strcmp(string, SUMA) == 0) {
		ok= true;
	}else if(strcmp(string, RESTA) == 0) {
		ok= true;
	}else if(strcmp(string, MULTI) == 0) {
		ok= true;
	}else if(strcmp(string, DIV) == 0) {
		ok= true;
	}else if(strcmp(string, POT) == 0) {
		ok= true;
	}else if(strcmp(string, RAIZ) == 0) {
		ok= true;
	}else if(strcmp(string, TER) == 0) {
		ok= true;
	}else if(strcmp(string, LOG) == 0) {
		ok= true;
	}
	return ok;
}

void libero_operandos(int* operando_1, int* operando_2) {
	free(operando_1);
	free(operando_2);
}

bool suma(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		free(operando_1);
		return false;
	}
	
	int* operando_2= pila_desapilar(pila);
	
	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado== NULL) {
		libero_operandos(operando_1, operando_2);
		return false;
	}
	
	/* Sumo los operandos*/
	*resultado= *operando_1 + *operando_2;
	
	/* Libero los operandos*/
	libero_operandos(operando_1, operando_2);
	return pila_apilar(pila, resultado);
}

bool resta(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		free(operando_1);
		return false;
	}
	
	int* operando_2= pila_desapilar(pila);
	
	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado== NULL) {
		libero_operandos(operando_1, operando_2);
		return false;
	}
	
	/* Resto los operandos*/
	*resultado= *operando_1 - *operando_2;
	
	/* Libero los operandos*/
	libero_operandos(operando_1, operando_2);
	return pila_apilar(pila, resultado);
}

int _calcular_raiz(int ini, int fin, int num) {
	if(ini > fin) return fin;
	
	int medio= (fin+ini)/2;
	
	if(medio*medio == num) return medio;
	
	if(num < medio*medio) {
		return _calcular_raiz(ini, medio-1, num);
	}
	return _calcular_raiz(medio+1, fin, num);
}

bool raiz(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(*operando_1 < 0) {
		free(operando_1);
		return false;
	}
	
	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado== NULL) {
		free(operando_1);
		return false;
	}
	
	/* Calculo la raiz*/
	 *resultado= _calcular_raiz(0, *operando_1, *operando_1);
	 
	/* Libero operando*/
	free(operando_1);
	return pila_apilar(pila, resultado);
}

bool multiplicar(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		free(operando_1);
		return false;
	}
	
	int* operando_2= pila_desapilar(pila);

	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado == NULL){
		libero_operandos(operando_1, operando_2);
		return false;
	}
	
	/* Multiplico los operandos*/
	*resultado= *operando_1 * *operando_2;
	
	/* Libero los operandos*/
	libero_operandos(operando_1, operando_2);
	return pila_apilar(pila, resultado);
}

bool dividir(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		free(operando_1);
		return false;
	}
	
	int* operando_2= pila_desapilar(pila);
	
	if(*operando_2 == 0) {
		libero_operandos(operando_1, operando_2);
		return false;
	}

	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado == NULL) {
		libero_operandos(operando_1, operando_2);
		return false;
	}
	/* Divido los operandos*/
	*resultado= *operando_1 / *operando_2;

	/* Libero los operandos*/
	libero_operandos(operando_1, operando_2);
	return pila_apilar(pila, resultado);
}

int _calcular_potencia(int base, int exp) {
	int p;
	if(exp == 0) return 1;
	
	if(exp % 2 == 0) {
		p= _calcular_potencia(base, exp/2);
		return p*p;
	}else{
		p= _calcular_potencia(base,(exp-1)/2);
		return p*p*base;
	}
}

bool potencia(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		free(operando_1);
		return false;
	}
	
	int* operando_2= pila_desapilar(pila);
	
	if(*operando_2 < 0) {
		libero_operandos(operando_1, operando_2);
		return false;
	}
	
	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado == NULL) {
		libero_operandos(operando_1, operando_2);
		return false;
	}
	
	/* Calculo la potencia*/
	*resultado= _calcular_potencia(*operando_1, *operando_2);
	
	/* Libero los operandos*/
	libero_operandos(operando_1, operando_2);
	return pila_apilar(pila, resultado);
}

int _calcular_logaritmo(int base, int antilog) {
	if(antilog < base) return 0;
	
	if(antilog/base >= base) {
		return 1 + _calcular_logaritmo(base, antilog/base);
	}
	return 1;
}

bool logaritmo(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		free(operando_1);
		return false;
	}
	
	int* operando_2= pila_desapilar(pila);

	if(*operando_2 <= 1) {
		libero_operandos(operando_1, operando_2);
		return false;
	}
	
	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado == NULL) {
		libero_operandos(operando_1, operando_2);
		return false;
	}
	
	/* Calculo el logaritmo*/
	*resultado = _calcular_logaritmo(*operando_2, *operando_1);
	
	/* Libero los operandos*/
	libero_operandos(operando_1, operando_2);
	return pila_apilar(pila, resultado);
}

bool ternario(pila_t* pila) {
	if(pila_esta_vacia(pila)) return false;
	
	int* operando_1= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		free(operando_1);
		return false;
	} 
	
	int* operando_2= pila_desapilar(pila);
	
	if(pila_esta_vacia(pila)) {
		libero_operandos(operando_1, operando_2);
		return false;
	} 
	
	int* operando_3= pila_desapilar(pila);
	
	/* Pido memoria para almacenar el resultado*/
	int* resultado= malloc(sizeof(int));
	
	if(resultado == NULL) {
		libero_operandos(operando_1, operando_2);
		free(operando_3);
		return false;
	}
	
	/* Calculo ternario*/
	if(*operando_1 == 0) {
		*resultado= *operando_3;
	}else{
		*resultado= *operando_2;
	}
	
	/* Libero los operandos*/
	libero_operandos(operando_1, operando_2);
	free(operando_3);
	return pila_apilar(pila, resultado);
}

bool operaciones(pila_t* pila, char* operador) {
	bool resul= false;
	
	if(strcmp(operador, SUMA) == 0) {
		resul= suma(pila);
	}else if(strcmp(operador, RESTA) == 0) {
		resul= resta(pila);
	}else if(strcmp(operador, MULTI) == 0) {
		resul= multiplicar(pila);
	}else if(strcmp(operador, DIV) == 0) {
		resul= dividir(pila);
	}else if(strcmp(operador, POT) == 0) {
		resul= potencia(pila);
	}else if(strcmp(operador, RAIZ) == 0) {
		resul= raiz(pila);
	}else if(strcmp(operador, TER) == 0) {
		resul= ternario(pila);
	}else if(strcmp(operador, LOG) == 0) {
		resul= logaritmo(pila);
	}
	return resul;
}

void imprimir_resultado(bool operacion, pila_t* pila) {
	if(operacion) {
		int* resultado= pila_desapilar(pila);
		if(pila_esta_vacia(pila)) {
			fprintf(stdout, "%d\n", *resultado); 
		}else { 
			fprintf(stdout, "ERROR\n");
		}
		free(resultado);
	 }else{ 
		 fprintf(stdout, "ERROR\n"); 
	 }	 
}

int* convertir_numero(char* operando) {
	int* numero= malloc(sizeof(int));
	
	if(numero == NULL) return NULL;
	
	*numero= atoi(operando);
	return numero;
}

void calculadora_polaca(char* linea) {
	pila_t* pila= pila_crear();
	int i = 0;
	bool resultado= true;
	
	/* Elimino el \n*/
	linea[strlen(linea)-1]= '\0';
	
	/* Separa la cadena que recibo*/
	char** calcular= split(linea, SEP);
	
	while(calcular[i] != NULL && resultado) {
		
		if(*calcular[i] != '\0') {
			if(!es_un_operador(calcular[i])) {
				int* numero= convertir_numero(calcular[i]);
				
				if(numero) pila_apilar(pila, numero);
			}else {
				char* operador= calcular[i];
				resultado= operaciones(pila, operador);
			}
		}
		i++;
	}
	imprimir_resultado(resultado, pila);
	free_strv(calcular);
	destruir_pila(pila);
}

int main() {
	
	char* linea_stdin= NULL;
	size_t capacidad= 0;
	
	while(getline(&linea_stdin, &capacidad, stdin) != -1) {
		calculadora_polaca(linea_stdin);
	} 
	free(linea_stdin);
	return 0;
}
