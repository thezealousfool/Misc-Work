// Using FIFO
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 100

int main() {

  int file;
  pid_t pid;
  char caller[MAX_SIZE], receiver[MAX_SIZE];
  const char *vvk_fifo = "/tmp/vvk_fifo";

  mkfifo(vvk_fifo, 0600);

  pid = getpid();
  printf("Calling...\n");

  while (1) {
    file = open(vvk_fifo, O_WRONLY);
    if (!file) {
      continue;
    }

    printf("%5d :: Sending: ", pid);

    fgets(caller, MAX_SIZE, stdin);

    write(file, caller, strlen(caller)+1);
    close(file);
    if((caller[0] == 'E') && (caller[1] == 'X') && (caller[2] == 'I') && (caller[3] == 'T')) {
      break;
    }

    file = open(vvk_fifo, O_RDONLY);
    if (!file) {
      continue;
    }

    read(file, receiver, MAX_SIZE);

    if((receiver[0] == 'E') && (receiver[1] == 'X') && (receiver[2] == 'I') && (receiver[3] == 'T')) {
      close(file);
      break;
    }
    printf("%5d :: Receiving: %s\n", pid, receiver);
    close(file);
  }

  printf("Exiting...\n");
  return 0;
}