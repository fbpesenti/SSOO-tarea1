#include <stdio.h>
#include<stdbool.h>
#include <unistd.h>
#include "../file_manager/manager.h"


void handler_states(int sig, siginfo_t *siginfo, void *ucontext){
  printf("Repartidor recibe info\n");
  int valor_recibido = siginfo-> si_value.sival_int;
  printf("Recibi %i\n", valor_recibido);
  printf("aca debe estar sender: %i\n", siginfo->si_pid);
  //send_signal_with_int(id_fabrica, valor_recibido);
}

int main(int argc, char const *argv[])
{
  
  printf("I'm the REPARTIDOR process and my PID is: %i\n", getpid());
  printf("Ahora voy a cnectar al repartidor\n");
  connect_sigaction(SIGUSR1, handler_states);
  int velocidad = 1;
  while (true)
    ;
}
