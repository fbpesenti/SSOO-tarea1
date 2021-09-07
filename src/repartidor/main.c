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
int senal;
int distancia_semaforo_1;
int distancia_semaforo_2;
int distancia_semaforo_3;
int distancia_bodega;
int envios_completos;

void handler_states(int sig, siginfo_t *siginfo, void *ucontext){
  printf("Repartidor recibe info\n");
  int valor_recibido = siginfo-> si_value.sival_int;
  printf("Recibi %i\n", valor_recibido);
  printf("aca debe estar sender: %i\n", siginfo->si_pid);
  //send_signal_with_int(id_fabrica, valor_recibido);
}

//Esta funcion crea el output para el repartidor
void output_file(int tiempo_semaforo1, int tiempo_semaforo2,int tiempo_semaforo3, int turnos_bodega, char* repartidor_name){
  FILE *output_file = fopen(repartidor_name, "w");
  fprintf(output_file, "%i,%i,%i,%i", tiempo_semaforo1, tiempo_semaforo2, tiempo_semaforo3, turnos_bodega);
  fclose(output_file);
}
void repartidor_avanza(int signum){
  printf("*********");
  printf("LLegue a la alarma");
  if(distancia==(distancia_semaforo_1)){
    if(estado_semaforo[0]==0){
      distancia++;
      turnos[0]++;
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
    }
    else{
      turnos[0]++;
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
    }
  }
  else if(distancia==(distancia_semaforo_2-1)){
    if(estado_semaforo[1]==0){
      distancia++;
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
    }
    else{
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
    }
  }
  else if(distancia==(distancia_semaforo_3-1)){
    if(estado_semaforo[2]==0){
      distancia++;
      turnos[2]++;
      turnos[3]++;
    }
    else{
      turnos[2]++;
      turnos[3]++;
    }
  }
  else if(distancia==(distancia_bodega-1)){
    if(estado_semaforo[1]==0){
      distancia++;
      turnos[3]++;
    }
    else{
      turnos[3]++;
    }
  }
  // aca termina el proceso y se escirbe el archi 
  // CACHAR como escribir el Nombre del repartidor con su identificador del o al numero de envios
  else if(distancia==(distancia_bodega)){
    output_file(turnos[0], turnos[1], turnos[2], turnos[3], "repartidor_.txt");
    ///TERMINAR EL PROCESO
  }
  else{
    distancia++;
    if (distancia<(distancia_semaforo_1-1)){
      turnos[0]++;
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
    }
    else if (distancia<(distancia_semaforo_2-1)){
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
    }
    else if (distancia<(distancia_semaforo_3-1)){
      turnos[2]++;
      turnos[3]++;
    }
    else if (distancia<(distancia_bodega)){
      turnos[3]++;
    }
  }

}

// debo recibir distancias 
int main(int argc, char const *argv[])
{
  
  printf("*****************************");
  printf("LLEGOOO BIEN distancia 1: %s", argv[1]);
  connect_sigaction(SIGUSR1, handler_states);

  signal(SIGALRM,repartidor_avanza);


  alarm(velocidad);

  while (true)
  {
  };
  
}
