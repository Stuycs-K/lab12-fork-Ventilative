#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void err(){
  printf("errno %d\n",errno);
  printf("%s\n",strerror(errno));
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
  int p = fork();
  int rando = rand();
  printf("PID: %d, MY NUM: %d\n",p, rando);
  return 0;
}
