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

int main(int argc, char** argv) {

  int file, i, no_other_calls;
  pid_t pid;
  char caller[MAX_SIZE], receiver[MAX_SIZE];
  const char *vvk_fifo = "/tmp/vvk_fifo";

  pid = getpid();
  printf("Waiting for Caller...\n");

  while (1) {
    file = open(vvk_fifo, O_RDONLY);
    if (!file) {
      continue;
    }

    if (argc < 2) {
      no_other_calls = 2;
    } else {
      no_other_calls = atoi(argv[1]);
    }

    printf("Received call.\n");

    read(file, receiver, MAX_SIZE);

    if((receiver[0] == 'E') && (receiver[1] == 'X') && (receiver[2] == 'I') && (receiver[3] == 'T')) {
      close(file);
      break;
    }

    printf("%5d :: Receiving: %s", pid, receiver);
    close(file);

    printf("%5d :: Sending: ", pid);
    file = open(vvk_fifo,O_WRONLY);
    if (!file) {
      continue;
    }

    fgets(caller, MAX_SIZE, stdin);
    printf("\n");

    for (i = 0; i < no_other_calls; ++i) {
      write(file, caller, strlen(caller)+1);
    }
    close(file);

    if((caller[0] == 'E') && (caller[1] == 'X') && (caller[2] == 'I') && (caller[3] == 'T')) {
      break;
    }
  }

  printf("Exiting...\n");
  return 0;
}