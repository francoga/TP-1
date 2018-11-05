#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "strutil.h"
 
const char FIN_DE_CARACTER= '\0';
static char* VACIO= "";

char *duplicar_linea(const char *linea){
	size_t largo= strlen(linea) + 1;
	char *dup_linea = malloc(sizeof(char)*largo);
	
	if(dup_linea == NULL) return NULL;
	
	strcpy(dup_linea, linea);
	return dup_linea;
}

char* dividir_cadena(const char* str, size_t ini ,size_t fin) {
	
	size_t largo= (fin-ini) + 1;
	size_t j= 0;
	
	 if(ini == fin && largo == 1){
		return duplicar_linea(VACIO);
	}
	
	char* aux= calloc(largo, sizeof(char));
	
	if(aux == NULL) return NULL;
	
	for(size_t i= ini; i < fin; i++) {
		aux[j]= str[i];
		j += 1;
	}
	aux[j]= FIN_DE_CARACTER;
	return aux;	
}
 
char** split(const char* str, char sep) {
	
	size_t cant_palabras= 2;
	size_t inicio= 0, j= 0;
	size_t largo= strlen(str) + 1;
	
	// Cuento la cantidad de separadores que hay
	for(size_t i= 0; i < largo; i++) {
		if(str[i] == sep){
			cant_palabras += 1;
		}
	}

	char** sub_cadenas= calloc(cant_palabras, sizeof(char*));
	
	if(sub_cadenas == NULL) return NULL;
	
	for(size_t i= 0; i < largo; i++) {
		if(str[i] == sep || str[i] == FIN_DE_CARACTER ) {
			sub_cadenas[j]= dividir_cadena(str, inicio, i);
			inicio= i+1;
			j += 1;	
		} 
	}
	sub_cadenas[j]= NULL;
	return sub_cadenas;
}

char *join(char **strv, char sep) {
    size_t i = 0, j = 0, k = 0, largo = 0;

    while (strv[i] != NULL) {
        largo += strlen(strv[i])+1;
        i++;
    }
    char *cadena = malloc((largo+1) * sizeof(char)); // agrego 1 por el '\0' final

    //itero el array de subcadenas
    i = 0;
    while (strv[i] != NULL) {
        if (i > 0) {
            //agrego separador antes de cada substring
            cadena[k] = sep;
            k++;
        }
        //itero la subcadena
        char *sub_cadena = strv[i];
        j = 0;
        while (sub_cadena[j] != FIN_DE_CARACTER) {
            cadena[k] = sub_cadena[j];
            k++, j++;
        }
        i++;
    }
    cadena[k] = FIN_DE_CARACTER;
    return cadena;
}

void free_strv(char* strv[]) {
	size_t i= 0;
	
	while(strv[i] != NULL) {
		free(strv[i]);
		i++;
	}
	free(strv);
}
