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
  //####hardcore
  id_semaforo1 = siginfo->si_pid;
  if (siginfo->si_pid == id_semaforo1){
    printf("---------llego un semaforo al repartidor -----------------\n");
    if (estado_semaforo[1] == 0){
      printf("---------estaba en 0 cambio a 1 -----------------\n");
      estado_semaforo[1] = 1;
    }
    else if (estado_semaforo[1] == 1){
      printf("---------estaba en 1 cambio a 0 -----------------\n");
      estado_semaforo[1] = 0;     
    }
    printf("array estados :{ %i %i %i}\n", estado_semaforo[1], estado_semaforo[2], estado_semaforo[3]);
    
  }
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
    //output_file(turnos[0], turnos[1], turnos[2], turnos[3], "repartidor_.txt");
    printf("**************Se Termino llego a bodega*********************\n");
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

  printf("*****************************\n");
  printf("LLEGOOO BIEN distancia 1: %i\n", distancia_semaforo_1);
  
  connect_sigaction(SIGUSR1, handler_states);

  signal(SIGALRM,repartidor_avanza);


  alarm(velocidad);

  while (true)
  {
  };
  
}
