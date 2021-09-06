#include <stdio.h>
#include<stdbool.h>
#include <unistd.h>
#include "../file_manager/manager.h"


void handler_states(int sig, siginfo_t *siginfo, void *ucontext){
  printf("Repartidor recibe info\n");
  int valor_recibido = siginfo-> si_value.sival_int;
  printf("Recibi %i\n", valor_recibido);
  printf("aca debe estar sender: %i\n", siginfo->si_pid);
}

int main(int argc, char const *argv[])
{
  connect_sigaction(SIGUSR1, handler_states);
  printf("I'm the REPARTIDOR process and my PID is: %i\n", getpid());
  int velocidad = 1;
  while (true)
    ;
  //connect_sigaction(SIGUSR1, handler_states);
}
