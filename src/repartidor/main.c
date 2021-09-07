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
int id_repartidor;
int distancia_semaforo_1;
int distancia_semaforo_2;
int distancia_semaforo_3;
int distancia_bodega;
int envios_completos;

void handler_states(int sig, siginfo_t *siginfo, void *ucontext){
  printf("REPARTIDR: recibe info\n");
  int valor_recibido = siginfo-> si_value.sival_int;
  printf("REPARTIDR: Recibi %i\n", valor_recibido);
  printf("REPARTIDR: aca debe estar sender (semaforo): %i\n", siginfo->si_pid);
  //send_signal_with_int(id_fabrica, valor_recibido);
  //####hardcore
  printf("valor recibido %i\n", valor_recibido);
  if (valor_recibido == 1){
    printf("---------llego un semaforo 1 al repartidor -----------------\n");
    if (estado_semaforo[0] == 0){
      estado_semaforo[0] = 1;
    }
    else if (estado_semaforo[0] == 1){
      estado_semaforo[0] = 0;     
    }
    printf("array estados :{ %i %i %i}\n", estado_semaforo[0], estado_semaforo[1], estado_semaforo[2]);
  }
  if (valor_recibido == 2){
    printf("---------llego un semaforo 2 al repartidor -----------------\n");
    if (estado_semaforo[1] == 0){
      estado_semaforo[1] = 1;
    }
    else if (estado_semaforo[1] == 1){
      estado_semaforo[1] = 0;     
    }
    printf("array estados :{ %i %i %i}\n", estado_semaforo[0], estado_semaforo[1], estado_semaforo[2]);
  }
  if (valor_recibido == 3){
    printf("---------llego un semaforo 3 al repartidor -----------------\n");
    if (estado_semaforo[2] == 0){
      estado_semaforo[2] = 1;
    }
    else if (estado_semaforo[2] == 1){
      estado_semaforo[2] = 0;     
    }
    printf("array estados :{ %i %i %i}\n", estado_semaforo[0], estado_semaforo[1], estado_semaforo[2]);
  }
  printf("---------------------vamos a terminar el proceso -----------------\n");


}

//Esta funcion crea el output para el repartidor
void output_file(int tiempo_semaforo1, int tiempo_semaforo2,int tiempo_semaforo3, int turnos_bodega, char* repartidor_name){
  FILE *output_file = fopen(repartidor_name, "w");
  fprintf(output_file, "%i,%i,%i,%i", tiempo_semaforo1, tiempo_semaforo2, tiempo_semaforo3, turnos_bodega);
  fclose(output_file);
}
void repartidor_avanza(int signum){
  printf("*********\n");
  printf("LLegue a la alarma\n");
  if(distancia==(distancia_semaforo_1-1)&& distancia>0){
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
      turnos[3]++;
      distancia++;
  }
  // aca termina el proceso y se escirbe el archi 
  // CACHAR como escribir el Nombre de)l repartidor con su identificador del o al numero de envios
  else if(distancia==(distancia_bodega)){
    char repa[100];
    sprintf(repa, "repartidor_%i.txt", id_repartidor);
    output_file(turnos[0], turnos[1], turnos[2], turnos[3], repa);
    ///TERMINAR EL PROCESO

    
  }

  else{
    if (distancia<(distancia_semaforo_1)){
      distancia++;
      turnos[0]++;
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
    }
    else if (distancia<(distancia_semaforo_2-1)){
      turnos[1]++;
      turnos[2]++;
      turnos[3]++;
      distancia++;
    }
    else if (distancia<(distancia_semaforo_3-1)){
      turnos[2]++;
      turnos[3]++;
      distancia++; 
    }
    else if (distancia<(distancia_bodega)){
      turnos[3]++;
      distancia++;
    }
  }
  printf("%i----------------------------\n", distancia);
  printf("##################Ternmino##################\n");
  alarm(velocidad);
}

// debo recibir distancias 
int main(int argc, char const *argv[])
{
  distancia_semaforo_1 = atoi(argv[1]);
  distancia_semaforo_2 = atoi(argv[2]);
  distancia_semaforo_3 = atoi(argv[3]);
  distancia_bodega = atoi(argv[4]);
  id_repartidor = atoi(argv[6]);
  printf("*****************************\n");
  printf("LLEGOOO BIEN distancia 1: %i\n", distancia_semaforo_1);
  
  printf("*************nacio un repartidor %i****************\n", getpid());
  printf("LLEGOOO str 1: %s", argv[5]);
  connect_sigaction(SIGUSR1, handler_states);

  signal(SIGALRM,repartidor_avanza);


  alarm(velocidad);

  while (true)
  {
  };
  
}
