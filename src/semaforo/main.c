#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<signal.h>

void sig_handler(int signum){
 
  printf("CAMBIO COLOR\n");
  printf(" %i signum\n", signum);
  send_signal_with_int();
}


int main(int argc, char const *argv[])
{
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
  printf("distancia: %s en proceso %i\n", argv[1], getpid());
  printf("delay: %s en proceso %i\n", argv[2], getpid());
  printf("ID FABRICA: %s en proceso %i\n", argv[3], getpid());
  signal(SIGALRM,sig_handler); // Register signal handler
  int delay = atoi(argv[2]);
  printf("%i de dealy\n", delay);
  
  alarm(delay); 
  printf("a con %i\n", delay);
  sleep(delay+1);
    //sleep(delay);
  
  
  //printf("creare un semaforo\n");
  //Semaforo* semaforo = createSemaforo(1,1,1);
  //printf("%d\n", semaforo);
  //printf("%d\n", semaforo->color);
}
