#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "repartidor.h"

Repartidor* repartidor_init(int id, int velocidad){
    Repartidor* r = (Repartidor*) malloc(sizeof(Repartidor));
    r->id = id;
    r->velocidad = velocidad;
    r->parent = NULL;
    return r;
    
}