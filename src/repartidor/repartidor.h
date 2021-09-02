#pragma once

#include <stdio.h>

struct repartidor;
typedef struct repartidor Repartidor;

struct repartidor{
    int id;
    int state;
    int velocidad;
    Repartidor* parent;
};

Repartidor* repartidor_init(int id, int velocidad);