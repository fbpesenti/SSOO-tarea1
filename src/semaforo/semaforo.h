#include <stdio.h>
#include <unistd.h>

struct Semaforo;
typedef struct semaforo
{
    int id;
    int delay;
    int padre;
    char color;
}Semaforo;

Semaforo* createSemaforo(int id, int delay, int padre);