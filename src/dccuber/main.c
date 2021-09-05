#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../file_manager/manager.h"

// void handle_sigint(int sig)
// {
//   printf("Gracefully finishing\n");
//   //

//   // Terminamos el programa con exit code 0
//   exit(0);
// }


void hander_test(int sig, siginfo_t *siginfo, void *ucontext){
  printf("ENTRO//\n");
  int valor_recibido = siginfo-> si_value.sival_int;
}

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);
  char *distancia[5]; //flo
  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
    distancia[i] = data_in->lines[0][i]; //flo
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
  char *tiempo_1 = data_in->lines[1][2];
  char *tiempo_2 = data_in->lines[1][3];
  char *tiempo_3 = data_in->lines[1][4];
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
  int id_fabrica;
  int id_fabrica_original;
  // int a = 0;
  
  id_semaforo = fork(); 

  if (id_semaforo > 0){ //proceso padre 
    printf("MAIN: soy proceso padre PID: %i\n", getpid());
    
    id_fabrica = fork();//crear FABRICA
    id_fabrica_original = id_fabrica;


    if (id_fabrica > 0){ //proceso padre
      id_semaforo1 = fork();
      if (id_semaforo1 == 0){ ///proceso hijo SEMAFORO
        printf("SEMAFORO1: soy un semaforo PID: %i\n", getpid());
        printf("$$$$$$$$$$$ %i\n", id_fabrica);
        char str[10];
        sprintf(str, "%d",id_fabrica);
        char *argv[] = {"semaforo", distancia[0], tiempo_1, str, NULL};
            

        //char *argv[] = {"semaforo", distancia[1],tiempo_2, id_fabrica, NULL};
        execv("./semaforo", argv);
        printf("probando 123 \n");
      };
        if (id_semaforo2 == 0){ ///proceso hijo SEMAFORO
          printf("SEMAFORO2: soy un semaforo prueba PID: %i\n", getpid());
          char str[10];
          sprintf(str, "%d",id_fabrica);
          char *argv[] = {"semaforo", distancia[0], tiempo_1, str, NULL};
          
          //char *argv[] = {"semaforo", distancia[2], tiempo_3, id_fabrica, NULL};
          execv("./semaforo", argv);
          printf("probando 123 \n");
        };
      };

    };
    if (id_fabrica == 0){ ///proceso hijo FABRICA
      printf("FABRICA: soy una fabrica PID: %i\n", getpid());
      //ACA SE RECIBE SEÑAL SEMAFORO
      connect_sigaction(SIGUSR1, hander_test);
      //ACA SE CREAN LOS REPARTIDORES
      if (envios_completados < envios_necesarios){
        int id_repartidor;
        printf("me demoro %i segundos en crear un repartidor.....\n", tiempo_creacion);
        sleep(tiempo_creacion);  // Creo que deberia ser un alarm alarm(tiempo_creacion)
        id_repartidor = fork();
        if (id_repartidor == 0){
          char *argv[] = {"repartidor", "dfsf", NULL};
          execv("./repartidor", argv);
          printf("REPARTIDOR: Hola naci PID: %i\n", getpid());
        }      
      }
    };
    
  };

  if (id_semaforo == 0){ ///proceso hijo SEMAFORO
    printf("SEMAFORO0: soy un semaforo PID: %i\n", getpid());
    printf("------------------pruebas----------\n");
    char str[10];
    sprintf(str, "%d",id_fabrica_original);
    char *argv[] = {"semaforo", distancia[0], tiempo_1, str, NULL};
    execv("./semaforo", argv);
    printf("probando 123 \n");
  };

  printf("Liberando memoria...PID: %i\n", getpid());
  input_file_destroy(data_in);
}
