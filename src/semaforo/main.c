#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//Esta funcion crea el output para el semaforo
void output_file(int cantidad_cambios, char* nombre_archivo){
  FILE *output_file = fopen(nombre_archivo, "w");
  fprintf(output_file, "%i", cantidad_cambios);
  fclose(output_file);
}

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
