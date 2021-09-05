#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  printf("distancia: %s en proceso %i\n", argv[1], getpid());
  printf("delay: %s en proceso %i\n", argv[2], getpid());

  //printf("creare un semaforo\n");
  //Semaforo* semaforo = createSemaforo(1,1,1);
  //printf("%d\n", semaforo);
  //printf("%d\n", semaforo->color);
}
