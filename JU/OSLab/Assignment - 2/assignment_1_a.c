#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

int main() {

  pid_t pid;
  int i;

  pid = fork();

  if (pid < 0) {

    fprintf(stderr, "Failed in creating child process");
    return 1;

  } else if (pid == 0) {

    pid = getpid();
    for (i = 0; i < 10; ++i) {
      sleep(2);
      printf("Y (pid: %5d) - %2d\n", pid, i);
    }
    exit(0);

  } else {

    pid = fork();

    if (pid < 0) {

      fprintf(stderr, "Failed in creating child process");
      return 1;

    } else if (pid == 0) {

      pid = getpid();
      for (i = 0; i < 10; ++i) {
        printf("X (pid: %5d) - %2d\n", pid, i);
        usleep(2000);
      }
      exit(0);

    } else {

      pid = wait(NULL);
      printf("Child (pid: %5d) Complete\n", pid);
      pid = wait(NULL);
      printf("Child (pid: %5d) Complete\n", pid);

    }

  }

  return 0;
}