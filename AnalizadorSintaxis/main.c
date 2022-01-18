#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cabecera.h"

const char palabReserv[][100] = {"Leer", "Mostrar", "Mientras", "Romper", "Para", "Si", "Sino", "Encambio", "Cad", "Ent", "Flot", "Car"};

NODO *cabeza = NULL;

/*Esta función genera un lexema de un símbolo de distintos tipos;
    Al final se llama a la función generarToken(int, char*, int)*/
void lexemaSimb(char car){
    char lexema[] = {car, '\0'};

    switch(car){
        case 42://----OPAR------
        case 43:
        case 45:
        case 47:
            generarToken(4, lexema, 2);
            break;
        case 58://----OPCOMP-----
        case 60:
        case 62:
            generarToken(5, lexema, 2);
            break;
        case 61://----OPASIGN----
            generarToken(6, lexema, 2);
            break;
        case 33://----OPLOG------
        case 38:
        case 124:
            generarToken(7, lexema, 2);
            break;
        case 91://----ESPECIAL---
        case 93:
        case 123:
        case 125:
        case 40:
        case 41:
        case 34:
            generarToken(8, lexema, 2);
            break;
        default:
            generarToken(10, lexema, 2); //Caracter desconocido
    }
}

/*Esta función genera un lexema de tipo Cadena, el lexema se genera con comillas;
    Al final se llama a la función generarToken(int, char*, int)*/
void lexemaCad(FILE *arch, char car){
    char str1[2] = {car, '\0'};
    char lexema[100] = "";
    strcpy(lexema,str1);

    while((car = fgetc(arch)) != EOF){
        if(isascii(car) && car != '"'){
            char str2[2] = {car, '\0'};
            strcat(lexema, str2);
        }
        else if(car == '"'){
            strcat(lexema, "\"");
            break;
        }
        else{
            printf("Error: Cadena no admite %c como caracter valido", car);
            exit(-1);
        }
    }

    generarToken(9, lexema, 4);
}

/*Esta función genera un lexema de tipo número entero o decimal
    Al final se llama a la función generarToken(int, char*, int)*/
void lexemaNum(FILE *arch, char car){
    char str1[2] = {car, '\0'};
    char lexema[100] = "";
    int cantPuntos = 0;
    strcpy(lexema,str1);

    while((car = fgetc(arch)) != EOF){
        if(isdigit(car)){
            char str2[2] = {car, '\0'};
            strcat(lexema, str2);
        }
        else if(car == 46 && cantPuntos != 1){
            strcat(lexema, ".");
            cantPuntos++;
        }
        else if(car == ' ' || car == ';'){
            break;
        }
        else if(cantPuntos == 1){
            printf("Error: Un numero no puede contener mas de un punto decimal");
            exit(-1);
        }
        else{
            printf("Error: Dato tipo numero no admite el caracter %c como caracter valido", car);
            exit(-1);
        }
    }


    cantPuntos==0 ? generarToken(2, lexema, 0) : generarToken(2, lexema, 3);
}

/*Esta función genera un lexema tipo Identificador y llama a la función
    existePalRes(char * lexema), una vez concluido si existe esa palabra reservada
        o no,llama a la función generarToken(int, char*, int)*/
void lexemaId(FILE *arch, char car){
    char str1[2] = {car, '\0'};
    char lexema[100] = "";
    strcpy(lexema,str1);

    while((car = fgetc(arch)) != EOF){
        if(isalnum(car)){
            char str2[2] = {car, '\0'};
            strcat(lexema, str2);
        }
        else if(car == ' ' || car == ';'){
            break;
        }
        else{
            printf("Error: Identificador no admite %c como caracter valido", car);
            exit(-1);
        }
    }

    if(existePalRes(lexema) == 1){
        generarToken(0, lexema, 4);
    }else{
        generarToken(1, lexema, 4);
    }

}

/*Esta función recibe un lexema(cadena) y devuelve 1 si dicho
    lexema existe dentro de las palabras reservadas y 0 si no existe*/
int existePalRes(char lexema[]){
    int i=0, bandera=0;
    for(i == 0; i < 4; i++){ //El valor límite de i dependerá del tamaño del arreglo palabReserv
        if(strcmp(lexema, palabReserv[i]) == 0){
            bandera = 1;
        }
    }

    return bandera;
}

/*Esta función genera un token con los datos recibidos de los
    generadores de lexemas e inserta el token generado en una lista doblemente
        enlazada.*/
void generarToken(int tipoToken, char lexema[], int tipoDato){
    Token token;

    token.tipoToken = tipoToken;
    strcpy(token.lexema, lexema);
    token.tipoDato = tipoDato;

    if(cabeza == NULL){
        InsertarInicio(&cabeza, token);
    }else{
        InsertarFinal(&cabeza, token);
    }

}


int main () {
    FILE * arch = fopen("hola.txt", "rt"); //Abrimos documento de texto
    char car = ' ';

    while((car = fgetc(arch)) != EOF){ //EOF = End of file (Fin de archivo)

        if(isalpha(car)){//Si se presenta una letra
            lexemaId(arch, car);
        }
        else if(isdigit(car)){//Si se presenta un número
            lexemaNum(arch, car);
        }
        else if(car == '"'){//Si se presenta una comilla
            lexemaCad(arch, car);
        }
        else if(isascii(car) && car != ' ' && car != ';' && car != 10 && car != 13 && car != 9){//Si es un símbolo
            lexemaSimb(car);
        }
    }
    printf("-TOKENS CREADOS-\n\n");
    ImprimirLista(cabeza);

    return 0;
}

