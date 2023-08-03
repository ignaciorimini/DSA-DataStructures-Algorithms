#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stackUsingArrays.h"

// Solution to the following problem: https://leetcode.com/problems/baseball-game/
// Difficulty: Easy

// Funcion copiadora de strings.
void* copiar_strings(void* dato){
    char* cadena= (char*) dato;
    char* nuevaCadena= malloc(sizeof(char)*(strlen(cadena)+1));
    strcpy(nuevaCadena, cadena);
    return nuevaCadena;
}

// Funcion comparadora de strings.
int comparar_strings(void* dato1, void* dato2){
    char* cadena1= (char*)dato1;
    char* cadena2= (char*)dato2;
    return strcmp(cadena1, cadena2);
}

// Funcion destructora de strings.
void destruir_strings(void* dato){
    free(dato);
}

// Funcion Hash de strings: retorna la suma ASCII de cada caracter de la cadena.
unsigned hash_strings(void* dato){
    char* cadena= (char*) dato;
    int sumaASCII= 0;
    for(int i=0; i<strlen(cadena); i++){
        sumaASCII+= cadena[i];
    }
    return sumaASCII;
}

// Funcion visitante de strings: imprime cada cadena.
void imprimir_string(void* dato){
    printf("%s ", (char*) dato);
}

int es_numerico(const char* str) {
    // Verifica que el string no sea nulo o vacío
    if (str == NULL || *str == '\0') {
        return 0;
    }

    // Recorre cada caracter del string
    while (*str) {
        // Si alguno de los caracteres no es un dígito, retorna falso
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }

    // Si todos los caracteres son dígitos, retorna verdadero
    return 1;
}

int calPoints(char** operations, int operationsSize){
    Stack stack= stack_create(copiar_strings, destruir_strings, imprimir_string);

    for(int i=0; i<operationsSize; i++){
        if(strcmp(operations[i], "C") == 0){

            stack= stack_pop(stack);

        }else if(strcmp(operations[i], "D") == 0){

            if(stack_last_value(stack) != NULL && es_numerico(stack_last_value(stack))){
                int lastElement= atoi(stack_last_value(stack));
                lastElement*=2;

                char newInsert[20];
                sprintf(newInsert, "%d", lastElement);

                stack= stack_push(stack, newInsert);
            }
            
        }else if(strcmp(operations[i], "+") == 0){

            if(stack_last_value(stack) != NULL && es_numerico(stack_last_value(stack))){
                int lastElement= atoi(stack_last_value(stack));
                stack= stack_pop(stack);

                if(stack_last_value(stack) != NULL && es_numerico(stack_last_value(stack))){
                    int newLast= atoi(stack_last_value(stack));
                    int sum= lastElement + newLast;
                }
            }

        }else{
            stack= stack_push(stack, operations[i]);
        }
    }

    stack_iteration(stack);
    stack_destroy(stack);
}

int main(){
    char* array[] = {"5", "2", "C", "D", "+"};
    printf("es numerico %d\n", es_numerico("21312"));
    calPoints(array, 5);
    return 0;
}