#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "semaforo.h"

Semaforo* createSemaforo(int id, int delay, int padre){ //Problema: El children[0] se ocupa por un puntero que no se de donde sale
    Semaforo* newsemaforo = malloc(sizeof(Semaforo));
    *newsemaforo = (Semaforo){.id = id, .delay = delay, .padre = padre, .color = 'r' };
    //printf("Se instancio una celula \n");
    return newsemaforo;
}



int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  printf("creare un semaforo\n");
  Semaforo* semaforo = createSemaforo(1,1,1);
  printf("%d\n", semaforo);
  printf("%d\n", semaforo->color);
}
