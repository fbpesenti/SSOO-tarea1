#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "../file_manager/manager.h"

int id_proceso_rep;

void sig_handler_rep(int signum){
 
  printf("Crear repartidor\n");
  printf(" %i signum\n", signum);
  send_signal_with_int(id_proceso_rep, signum);
}

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);
  int distancia[4]; //flo
  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
    distancia[i] = atoi(data_in->lines[0][i]); //flo
  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
  }
  printf("\n");
  printf("VARIABLES\n");
  int tiempo_creacion = atoi(data_in->lines[1][0]);
  int envios_necesarios = atoi(data_in->lines[1][1]);
  int tiempo_1 = atoi(data_in->lines[1][2]);
  int tiempo_2 = atoi(data_in->lines[1][3]);
  int tiempo_3 = atoi(data_in->lines[1][4]);
  int envios_completados;
  envios_completados = 0;
  printf("tiempo creacion %i\n", tiempo_creacion);
  printf("\n");
  printf("MAIN  PID: %i\n", getpid());
  printf("MAIN: creare una fabrica..\n");
  printf("MAIN: creare un semaforo..\n");
  int id_semaforo;
  int id_semaforo1;
  int id_semaforo2;
  // int a = 0;
  
  id_semaforo = fork(); 

  if (id_semaforo > 0){ //proceso padre 
    printf("MAIN: soy proceso padre PID: %i\n", getpid());
    int id_fabrica;
    id_fabrica = fork();//crear FABRICA

    if (id_fabrica > 0){ //proceso padre
      id_semaforo1 = fork();
      if (id_semaforo1 == 0){ ///proceso hijo SEMAFORO
        printf("SEMAFORO: soy un semaforo PID: %i\n", getpid());
        char *argv[] = {"semaforo", distancia[1],"6", NULL};
        execv("./semaforo", argv);
        printf("probando 123 \n");
      };
      if (id_semaforo1 > 0){ //proceso padre
        id_semaforo2 = fork();
        if (id_semaforo2 == 0){ ///proceso hijo SEMAFORO
          printf("SEMAFORO: soy un semaforo PID: %i\n", getpid());
          char *argv[] = {"semaforo", distancia[2], "7", NULL};
          execv("./semaforo", argv);
          printf("probando 123 \n");
        };
      };
      //printf("MAIN: soy el mismo padre fabrica PID: %i\n", getpid());
    };
    if (id_fabrica == 0){ ///proceso hijo FABRICA
      printf("FABRICA: soy una fabrica PID: %i\n", getpid());
      //ACA SE CREAN LOS REPARTIDORES
      if (envios_completados < envios_necesarios){
        int id_repartidor;
        signal(SIGALRM,sig_handler_rep);
        printf("me demoro %i segundos en crear un repartidor.....\n", tiempo_creacion);
        alarm(tiempo_creacion);  // Creo que deberia ser un alarm alarm(tiempo_creacion)
        // id_repartidor = fork();
        // if (id_repartidor == 0){
        //   char *argv[] = {"repartidor", "dfsf", NULL};
        //   execv("./repartidor", argv);
        //   printf("REPARTIDOR: Hola naci PID: %i\n", getpid());
        // } 
        while (true)
        {
        };
        
      }
    };
    
  };

  if (id_semaforo == 0){ ///proceso hijo SEMAFORO
    printf("SEMAFORO: soy un semaforo PID: %i\n", getpid());
    char *argv[] = {"semaforo", distancia[0], "4", NULL};
    execv("./semaforo", argv);
    printf("probando 123 \n");
  };

  printf("Liberando memoria...PID: %i\n", getpid());
  input_file_destroy(data_in);
}
