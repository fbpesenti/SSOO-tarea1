#include <stdio.h>
#include<stdbool.h>
#include <unistd.h>

//Esta funcion crea el output para el repartidor
void output_file(int tiempo_semaforo1, int tiempo_semaforo2,int tiempo_semaforo3, int turnos_bodega, char* repartidor_name){
  FILE *output_file = fopen(repartidor_name, "w");
  fprintf(output_file, "%i,%i,%i,%i", tiempo_semaforo1, tiempo_semaforo2, tiempo_semaforo3, turnos_bodega);
  fclose(output_file);
}

int main(int argc, char const *argv[])
{
  int velocidad = 1;
  int turnos[] = {0,0,0,0};
  char estado_semaforo[4];
  int señal;
  char estado_recibido;
  if (señal == 1)
  {
    turnos[0] =+1;
    estado_semaforo[0] = estado_recibido;
  };
  
  
}
