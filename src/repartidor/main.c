#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include "../file_manager/manager.h"

//se asume que todos los semaforos empiezan en verde 
char estado_semaforo[] = {0,0,0};
int turnos[] = {0,0,0,0};
int id_semaforo1;
int id_semaforo2;
int distancia = 0;
int velocidad = 1;

void handler_states(int sig, siginfo_t *siginfo, void *ucontext){
  printf("Repartidor recibe info\n");
  int valor_recibido = siginfo-> si_value.sival_int;
  printf("Recibi %i\n", valor_recibido);
  printf("aca debe estar sender: %i\n", siginfo->si_pid);
}
void repartidor_avanza(int signum){
  printf("Se gatillo repartidor avanza*****************");
}

//Esta funcion crea el output para el repartidor
void output_file(int tiempo_semaforo1, int tiempo_semaforo2,int tiempo_semaforo3, int turnos_bodega, char* repartidor_name){
  FILE *output_file = fopen(repartidor_name, "w");
  fprintf(output_file, "%i,%i,%i,%i", tiempo_semaforo1, tiempo_semaforo2, tiempo_semaforo3, turnos_bodega);
  fclose(output_file);

}


// debo recibir distancias 
int main(int argc, char const *argv[])
{
  printf("LLEGOOO BIEN distancia 1: %s; %s, %s", argv[1], argv[2], argv[3]);
  connect_sigaction(SIGUSR1, handler_states);

  signal(SIGALRM,repartidor_avanza);


  alarm(velocidad);

  while (true)
  {
  };
  


}
