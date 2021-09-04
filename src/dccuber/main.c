#include <stdio.h>
#include <unistd.h>

#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");

  printf("\t- ");
  for (int i = 0; i < 4; i++)
  {
    printf("%s, ", data_in->lines[0][i]);
  }
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
  }
  printf("\n");
  printf("VARIABLES\n");
  int tiempo_creacion;
  int envios_necesarios;
  int envios_completados;
  // tiempo_creacion = data_in->lines[0][0];
  tiempo_creacion = 1;
  envios_necesarios = 3; 
  envios_completados = 0;
  printf("tiempo creacion %i\n", tiempo_creacion);
  printf("\n");
  printf("MAIN  PID: %i\n", getpid());
  printf("MAIN: creare una fabrica..\n");
  printf("MAIN: creare un semaforo..\n");
  int id_semaforo;
  id_semaforo = fork(); //CREAR SEMAFORO(id semafoto)

  if (id_semaforo > 0){ //proceso padre 
    printf("MAIN: soy proceso padre PID: %i\n", getpid());
    int id_fabrica;
    id_fabrica = fork();//crear FABRICA

    if (id_fabrica > 0){ //proceso padre
      //printf("MAIN: soy el mismo padre fabrica PID: %i\n", getpid());
    };
    if (id_fabrica == 0){ ///proceso hijo FABRICA
      printf("FABRICA: soy una fabrica PID: %i\n", getpid());
      //ACA SE CREAN LOS REPARTIDORES
      if (envios_completados < envios_necesarios){
        int id_repartidor;
        printf("me demoro %i segundos en crear un repartidor.....\n", tiempo_creacion);
        sleep(tiempo_creacion);
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
    printf("SEMAFORO: soy un semaforo PID: %i\n", getpid());
    char *argv[] = {"semaforo", "dfsf", NULL};
    execv("./semaforo", argv);

    printf("probando 123 \n");
  };


  printf("Liberando memoria...PID: %i\n", getpid());
  input_file_destroy(data_in);
}
