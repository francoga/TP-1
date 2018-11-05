#define _POSIX_C_SOURCE 200809L // getline
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cola.h"

char* duplicar_cadena(const char* cadena) {
	size_t largo= strlen(cadena) + 1;
	char* dup= malloc(sizeof(char)*largo);
	
	if(dup == NULL) return NULL;
	
	strcpy(dup, cadena);
	return dup;
}

bool verificar_si_es_numero(char* string) {
	size_t largo= strlen(string);
	
	for( size_t i= 0; i < largo; i++){
		if(string[i] < '0' || string[i] > '9') {
			return false;
		}
	}
	return true;
}

bool encontrar_cadena(char* cadena_buscar, char* linea_archivo) {
	bool esta= false;
	size_t largo_cad= strlen(linea_archivo);
	size_t largo_cad_bus= strlen(cadena_buscar);
	
	/* La cadena a buscar no puede ser mas grande que la linea del archivo*/
	if(largo_cad < largo_cad_bus) return false;
	
	for(size_t i= 0; i < largo_cad; i++) {
		if(linea_archivo[i] == cadena_buscar[0]) {
			size_t cont= 0; 
			for(size_t j= 0; j < largo_cad_bus; j++) {
				esta = (linea_archivo[i+j] == cadena_buscar[j])? true: false;
				if(esta) cont++;
				if(cont == largo_cad_bus) return esta;
			}
		}
	}
	return esta;
}

void imprimir_lineas(cola_t* cola) {
	while(!cola_esta_vacia(cola)) {
		char* linea= cola_desencolar(cola);
		fprintf(stdout, "%s\n", linea);
		free(linea);
	}
}

void recorrer_archivo(FILE* archivo, cola_t* cola, char* cadena, char* string){
	char* linea= NULL;
	size_t capacidad= 0, lineas_mostrar= 0;
	size_t numero_lineas= atoi(string);
	
	while(getline(&linea, &capacidad, archivo) != -1) {
		linea[strlen(linea)-1]= '\0';// Elimino el \n
		char* linea_arch= duplicar_cadena(linea);
		cola_encolar(cola, linea_arch);
		lineas_mostrar++;
		
		if(encontrar_cadena(cadena, linea_arch)) {
			imprimir_lineas(cola);
			lineas_mostrar= 0; 
		}
		
		if(lineas_mostrar > numero_lineas) {
			free((char*)cola_desencolar(cola));	
		}
	}
	cola_destruir(cola, free);
	free(linea);
}

FILE* abrir_archivo(char* nombre_archivo, bool parametro_archivo) {
	FILE* archivo;
	if(parametro_archivo) {
		archivo= fopen(nombre_archivo, "rt");
	}else {
		archivo= stdin;
	}
	return archivo;
}

bool verificacion_de_parametros(int numero_parametros, char** parametros, bool* parametro_archivo) {
	if(numero_parametros < 3 || numero_parametros > 4) {
		fprintf(stderr, "Cantidad de parametros erronea\n");
		return false;
	}
	
	if(!verificar_si_es_numero(parametros[2])) {
		fprintf(stderr, "Tipo de parametro incorrecto\n");
		return false;
	}
	// si mando el archivo como parametro
	if(numero_parametros == 4) {
		FILE* archivo= fopen(parametros[3], "rt");
		if(archivo == NULL) {
			fprintf(stderr, "No se pudo leer el archivo indicado\n");
			return false;
		}
		*parametro_archivo = true; 
		fclose(archivo);
	}
	return true;
}

int main(int argc, char* argv[]) {
	bool parametro_archivo= false;
	if(verificacion_de_parametros(argc, argv, &parametro_archivo)) {
		FILE* archivo= abrir_archivo(argv[3], parametro_archivo);
		cola_t* cola= cola_crear();
		recorrer_archivo(archivo, cola, argv[1], argv[2]);
		
		if(parametro_archivo) fclose(archivo);
	}
	return 0;
}
