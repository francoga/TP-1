#include "strutil.h"
#include <stdio.h>

void pruebas_split_join_caso_1() {
	printf("\t\tINICIO DE PRUEBAS SPLIT Y JOIN CASO 1\n");
	
	char** sub_cadenas= split("a,b,c", ',');
	
	for(size_t i= 0; i < 4; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");
	
	char* cadena= join(sub_cadenas, ',');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

void pruebas_split_join_caso_2() {
	printf("\t\tINICIO DE PRUEBAS SPLIT Y JOIN CASO 2\n");
	
	char** sub_cadenas= split("abc-def-ghi", '-');
	
	for(size_t i= 0; i < 4; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");  
	
	char* cadena= join(sub_cadenas, '-');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

void pruebas_split_join_caso_3() {
	printf("\t\tINICIO DE PRUEBAS SPLIT Y JOIN CASO 3\n");
	
	char** sub_cadenas= split("abc,,def", ',');
	
	for(size_t i= 0; i < 4; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");
	  
	char* cadena= join(sub_cadenas, ',');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

void pruebas_split_join_caso_4() {
	printf("\t\tINICIO DE PRUEBAS SPLIT Y JOIN CASO 4\n");
	
	char** sub_cadenas= split("abc--def", '-');
	
	for(size_t i= 0; i < 4; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");  
	
	char* cadena= join(sub_cadenas, '-');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

void pruebas_split_join_caso_5() {
	printf("\t\tINICIO DE PRUEBAS SPLIT Y JOIN CASO 5\n");
	
	char** sub_cadenas= split("abc,def,", ',');
	
	for(size_t i= 0; i < 4; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");
	  
	char* cadena= join(sub_cadenas, ',');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

void pruebas_split_join_caso_6() {
	printf("\t\tINICIO DE PRUEBAS SPLIT Y JOIN CASO 6\n");
	
	char** sub_cadenas= split(",abc,def", ',');
	
	for(size_t i= 0; i < 4; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");  
	
	char* cadena= join(sub_cadenas, ',');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

void pruebas_split_join_caso_7() {
	printf("\t\tINICIO DE PRUEBAS SPLIT Y JOIN CASO 7\n");
	
	char** sub_cadenas= split("", ',');
	
	for(size_t i= 0; i < 2; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");  
	
	char* cadena= join(sub_cadenas, ',');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

void pruebas_split_join_caso_8() {
	printf("\t\tINICIO DE PREUBAS SPLIT Y JOIN CASO 8\n");
	
	char** sub_cadenas= split(",", ',');
	
	for(size_t i= 0; i < 3; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n"); 
	
	char* cadena= join(sub_cadenas, ',');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas); 
}

void pruebas_split_join_caso_9() {
	printf("\t\tINICIO DE PREUBAS SPLIT Y JOIN CASO 9\n");
	
	char** sub_cadenas= split("abc", '\0');
	
	for(size_t i= 0; i < 2; i++) {
		printf("%s \n", sub_cadenas[i]);
	}
	printf("\n");
	char* cadena= join(sub_cadenas, '\0');
	
	printf("La cadena es: %s\n", cadena);
	printf("\n");
	/*Destruyo las sub_cadenas*/
	free_strv(sub_cadenas);
}

int main() {
	pruebas_split_join_caso_1();
	pruebas_split_join_caso_2();
	pruebas_split_join_caso_3();
	pruebas_split_join_caso_4();
	pruebas_split_join_caso_5();
	pruebas_split_join_caso_6();
	pruebas_split_join_caso_7();
	pruebas_split_join_caso_8();
	pruebas_split_join_caso_9();
	return 0;
}

