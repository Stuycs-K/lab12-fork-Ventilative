#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

void err(){
  printf("errno %d\n",errno);
  printf("%s\n",strerror(errno));
  exit(1);
}

void perr(){
  perror("fork fail");
  exit(1);
}

int rand(){
  int randFile;
  int ret;
  int bytesRead;
  randFile = open("/dev/random", O_RDONLY, 0);
  bytesRead = read(randFile, &ret, 4);
  if (bytesRead <= 0){
    err();
  }
  return ret;
}

int main(){
  int myID = getpid();
  printf("%d about to create 2 child processes\n", myID);
  pid_t p = fork();
  if (p != 0){
    p = fork();
  }
  if (p < 0) perr();

  if (p != 0) {
    int status;
    wait(&status);
    exit(0);
  }

  if (p == 0) {
    int pid = getpid();
    int rando = abs(rand()) % 5 + 1;
    printf("PID: %d %dsec\n",pid, rando);
    sleep(rando);
    int ppid = getppid();
    if (ppid != 1) {
      printf("\nMain Process %d is done. Child %d slept for %dsec\n", ppid, pid, rando);
    }
    else {
      printf("\n%d finished after %dsec\n",pid, rando);
    }
    exit(0);
  }

  return 0;
}
