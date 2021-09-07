#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "../file_manager/manager.h"
#include <stdbool.h>
#include<sys/wait.h>

// void handle_sigint(int sig)
// {
//   printf("Gracefully finishing\n");
//   //

//   // Terminamos el programa con exit code 0
//   exit(0);
// }
int id_repartidor;
int id_semaforo1;
int id_semaforo2;
int id_semaforo3;
int id_main;
int id_fabrica;
int id_fabrica_original;
int envios_necesarios;
int array_prueba[100];
int global = 0;

void hander_test(int sig, siginfo_t *siginfo, void *ucontext){
  printf("ENTRO a handler test//\n");
  int valor_recibido = siginfo-> si_value.sival_int;
  //printf("Recibi %i\n", valor_recibido);
  // printf("aca debe estar sender: %i\n", siginfo->si_pid);
  // printf("se manda a este repartidor id: %i\n", id_repartidor);
  int id_proceso_semaforo = siginfo->si_pid;
  // printf("$$$$############# %i --------------------\n", id_semaforo1);
  for (int j = 0; j < envios_necesarios; j++){
    if (array_prueba[j] != 0){
      printf("FABRICA: mandando cambio semaforo a repartidores\n");
      send_signal_with_int(array_prueba[j], valor_recibido);
    }
  }
  //send_signal_with_int(id_repartidor, valor_recibido);
}

void handle_sigint_fabrica(int signum){
  if (global==0){
    printf("LLEGO a handler sigint fabrica \n");
    kill(getppid(), SIGINT);
    global = 1;
  }
  else if(global==1){
    printf("dead1\n");
    exit(0);
    printf("dead2\n");
  }
}


void handle_sigint_main(int signum){
  printf("LLEGO a sigint main\n");
  // a id_fabrica_original %i  d semaforos %i %i %i \n", id_fabrica_original, id_semaforo1, id_semaforo2, id_semaforo3);
  kill(id_semaforo1, SIGABRT);
  kill(id_semaforo2, SIGABRT);
  kill(id_semaforo3, SIGABRT);
  kill(id_fabrica_original, SIGABRT);
  printf("esperando al semaforo 1 ..........................\n");
  wait(NULL);
  printf("esperando al semaforo 2 ..........................\n");
  wait(NULL);
  printf("esperando al semaforo 3 ..........................\n");
  wait(NULL);
  printf("esperando a fabrca orifina ..........................\n");
  wait(NULL);
  exit(0);
}

void sigabr_handler_fabrica(int signum){ 
  printf("fabrica: Mira recibi SIGABRT\n");
  //printf("array_id_repartidores %i %i %i \n", array_prueba[0], array_prueba[1], array_prueba[2]);
  for (int j = 0; j < envios_necesarios; j++){
    //printf("se mandara senal a el proceso %i con j = %i\n", array_prueba[j], j);
    if (array_prueba[j] != 0){
      printf("FABRICA: matando repartidor\n");
      kill(array_prueba[j], SIGABRT);
      wait(NULL);
    }
  }
  printf("muere fabrica\n");
  kill(getpid(), SIGINT);
  printf("muere4\n");
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
  envios_necesarios = atoi(data_in->lines[1][1]);
  char *tiempo_1 = data_in->lines[1][2];
  char *tiempo_2 = data_in->lines[1][3];
  char *tiempo_3 = data_in->lines[1][4];
  int envios_completados = 0;
  id_main = getpid();
 // printf("tiempo creacion %i\n", tiempo_creacion);
  //printf("\n");
  printf("MAIN  PID: %i\n", getpid());
  signal(SIGINT, handle_sigint_main);
  // int a = 0;
  
  id_fabrica = fork();//crear FABRICA
  id_fabrica_original = id_fabrica;
  if (id_fabrica > 0){ //proceso padre
    
    //crear semafoortos
    
    

    id_semaforo1 = fork(); //SEMAFORO 1

    if (id_semaforo1 >0){ //proceso main
     // printf("MAIN: creare un semaforo..\n");
      id_semaforo2 = fork(); //SEMAFORO 2

      if (id_semaforo2 >0){//proceso padre

        id_semaforo3 = fork(); //SEMAFORO 3
        if (id_semaforo3 > 0){//proceso padre
          //creo los 3 semaforos
        }
        if (id_semaforo3 == 0){
         // printf("SEMAFORO3: soy un semaforo PID: %i\n", getpid());
          char str[10];
          sprintf(str, "%d",id_fabrica_original);
          char *argv[] = {"semaforo", distancia[2], tiempo_3, str, "3", NULL};
          execv("./semaforo", argv);
         // printf("probando 123 \n");
        }
      }
      if (id_semaforo2 == 0){
       // printf("SEMAFORO2: soy un semaforo PID: %i\n", getpid());
        char str[10];
        sprintf(str, "%d",id_fabrica_original);
        char *argv[] = {"semaforo", distancia[1], tiempo_2, str, "2", NULL};
        execv("./semaforo", argv);
       // printf("probando 123 \n");
      }
    } 
    if (id_semaforo1 == 0){
     // printf("SEMAFORO1: soy un semaforo PID: %i\n", getpid());
      char str[10];
      sprintf(str, "%d",id_fabrica_original);
      char *argv[] = {"semaforo", distancia[0], tiempo_1, str, "1", NULL};
      execv("./semaforo", argv);
     // printf("probando 123 \n");
    }
    while (true)
    ;
  }
  if (id_fabrica == 0){ ///proceso hijo FABRICA

     // printf("MAIN: creare una fabrica..\n");
      printf("FABRICA: soy una fabrica PID: %i\n", getpid());
      //ACA SE RECIBE SEÑAL SEMAFORO
      signal(SIGABRT, sigabr_handler_fabrica);
      connect_sigaction(SIGUSR1, hander_test);
      //printf("mirar %i \n", id_main);
      signal(SIGINT, handle_sigint_fabrica);
      //signal(SIGINT2, handle_sigint_fabrica_dead);
      //while (true)
      //;
      //ACA SE CREAN LOS REPARTIDORES
      int array_id_repartidores[envios_completados];
      int contador_repartidor = 0;
      while (envios_completados < envios_necesarios){
        //int id_repartidor;
        printf("FABRICA: creare un repartidor.. \n");
        printf("me demoro %i segundos en crear un repartidor.....\n", tiempo_creacion);
        sleep(tiempo_creacion);  // Creo que deberia ser un alarm alarm(tiempo_creacion)
        printf("eseperando 2@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2\n");
        sleep(100000);
        //printf("envios completador: %i | envios necesarios: %i\n", envios_completados, envios_necesarios);
        
        //printf("envios completados %i$$$$$$$$$$$$$$$$$$$$$$$$$$$$ffffffffffffffffffffffffffffffffffffffff$$4kk\n", envios_completados );
        id_repartidor = fork();
        int id_repartidor_original = id_repartidor;
        array_id_repartidores[envios_completados] = id_repartidor_original;
        array_prueba[envios_completados] = id_repartidor_original;
        envios_completados = envios_completados + 1;
        if (id_repartidor == 0){
          printf("NUMERO DE REPARTIDORES CREADOS: %i", contador_repartidor);
          char str1[10];
          sprintf(str1, "%d",id_main);          
          printf(" id_main %i %s\n", id_main, str1);
          char str2[10];
          sprintf(str2, "%d",contador_repartidor);  
          char str3[10];
          sprintf(str3, "%d",envios_necesarios);      
          //printf("Ahora voy a conectar al repartidor\n");
          char *argv[] = {"repartidor", distancia[0], distancia[1], distancia[2], distancia[3], str1, str2, str3,  NULL};
          execv("./repartidor", argv);
          //printf("REPARTIDOR: Hola naci PID: %i\n", getpid());
          
        }   

        contador_repartidor++;
      }
      //printf(" array de repartidores --> %i %i %i \n", array_id_repartidores[0], array_id_repartidores[1], array_id_repartidores[2]);
      while (true)
      ;
    };
//####################################3
  printf("Liberando memoria...PID: %i\n", getpid());
  input_file_destroy(data_in);
};
