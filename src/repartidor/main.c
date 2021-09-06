#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

int turnos[] = {0,0,0,0};

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
}


//Esta funcion crea el output para el repartidor
void output_file(int tiempo_semaforo1, int tiempo_semaforo2,int tiempo_semaforo3, int turnos_bodega, char* repartidor_name){
  FILE *output_file = fopen(repartidor_name, "w");
  fprintf(output_file, "%i,%i,%i,%i", tiempo_semaforo1, tiempo_semaforo2, tiempo_semaforo3, turnos_bodega);
  fclose(output_file);
}

int main(int argc, char const *argv[])
{
  int distancia[4];
  int velocidad = 1;
  //se asume que todos los semaforos empiezan en verde 
  char estado_semaforo[] = {"verde", "verde", "verde"};
  int señal;
  char estado_recibido;
  
  connect_sigaction(SIGUSR1, handle_sigusr1);

  // aqui se recibe la señal correspondiente a cada semaforo con su cambio de color
  // Semaforo 1 
  if (señal == 1)
  {
    // se cambia el estado del semaforo 1 correspondiente al color
    estado_semaforo[0] = estado_recibido;
  }
  else if(señal == 2)
  {
    turnos[1] =+1;
    estado_semaforo[1] = estado_recibido;
  }
  else if(señal == 3)
  {
    turnos[1] =+1;
    estado_semaforo[1] = estado_recibido;
  }


  alarm(velocidad);
  
  while (true)
  ;

  
  
  
}
