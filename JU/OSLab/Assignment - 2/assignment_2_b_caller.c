#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_SIZE 200

int main(int argc, char** argv) {

  int file, i, no_other_calls;
  pid_t pid;
  const char *vvk_fifo = "/tmp/vvk_fifo";

  if (mkfifo(vvk_fifo, 0600) == -1) {
    printf("Error :: Creating FIFO Failed\n");
    abort();
  }

  pid = getpid();
  printf("Calling...\n");

  while (1) {
    file = open(vvk_fifo, O_WRONLY);
    if (!file) {
      continue;
    }

    if (argc < 2) {
      no_other_calls = 2;
    } else {
      no_other_calls = atoi(argv[1]);
    }

    printf("%5d :: Sending: ", pid);

    fgets(caller, MAX_SIZE, stdin);

    for (i = 0; i < no_other_calls; ++i) {
      write(file, caller, strlen(caller)+1);
    }
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
