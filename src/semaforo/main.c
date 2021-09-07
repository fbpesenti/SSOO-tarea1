#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<signal.h>
#include <stdbool.h>
#include "../file_manager/manager.h"

int id_proceso_fabrica;
int delay_all;
int estado = 0;
int id_proceso_actual;
int cambios_color = 0;

//Esta funcion crea el output para el semaforo
void output_file(int cantidad_cambios, char* nombre_archivo){
  FILE *output_file = fopen(nombre_archivo, "w");
  fprintf(output_file, "%i", cantidad_cambios);
  fclose(output_file);
}

void sig_handler(int signum){
 
  printf("CAMBIO COLOR en estado %i\n", estado);
  printf("mando al proceso %i  desde proceso %i\n", id_proceso_fabrica, getpid());
  send_signal_with_int(id_proceso_fabrica, estado);
  cambios_color++;
  if (estado == 0){
    estado = 1;
  }
  else if (estado == 1){
    estado = 0;
  }
  alarm(delay_all);
  
}


int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
 // printf("distancia: %s en proceso %i\n", argv[1], getpid());
  //printf("delay: %s en proceso %i\n", argv[2], getpid());
  //printf("ID FABRICA: %s en proceso %i\n", argv[3], getpid());
  signal(SIGALRM,sig_handler); // Register signal handler
  int delay = atoi(argv[2]);
  id_proceso_actual = getpid();

  delay_all = delay;
  printf("%i de dealy\n", delay);
  id_proceso_fabrica = atoi(argv[3]);
  
  alarm(delay); 
  while (true)
      ;
    //sleep(delay);
  
  
  //printf("creare un semaforo\n");
  //Semaforo* semaforo = createSemaforo(1,1,1);
  //printf("%d\n", semaforo);
  //printf("%d\n", semaforo->color);
}
