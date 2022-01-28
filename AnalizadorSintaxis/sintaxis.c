#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cabecera.h"

void SintaxisLeer(NODO *cabeza, int paso){
    if(cabeza != NULL){
        switch(paso){
            case 1:/* Espera un: "Leer" */
                if (strcmp(cabeza->tok.lexema, "MOSTRAR") == 0)
                    SintaxisLeer(cabeza->siguiente, 2);
                else{
                    printf("No lo encontro");
                }
                break;
            case 2:/* Espera un: "Leer" */
                printf("Ay la llevas guey");
                break;
        }
    }
}

void SintaxisMostrar(NODO *cabeza, int paso){
}

void SintaxisMientras(NODO *cabeza, int paso){
}

void SintaxisPara(NODO *cabeza, int paso){
}

void SintaxisSi(NODO *cabeza, int paso){
}

void SintaxisVariables(NODO *cabeza, int paso){
}
