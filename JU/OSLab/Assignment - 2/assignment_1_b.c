#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
  int i;
  pid_t pid;
  sem_t *semaphore;

  semaphore = sem_open("/semaphore", O_CREAT,  0600, 0);

  pid = fork();

  if (pid < 0) {

    fprintf(stderr, "Error creating child process\n");

  } else if (pid == 0) {

    pid = getpid();
    for (i = 0; i < 10; i++) {
      printf("Y (pid: %6d) - %2d\n", pid, i);
      sem_post(semaphore);
      usleep(80000);
    }
    exit(0);

  } else {

    pid = fork();
    if (pid < 0) {

      fprintf(stderr, "Error creating child process\n");

    } else if (pid == 0) {

      pid = getpid();
      for (i = 0; i < 10; ++i) {
          sem_wait(semaphore);
          printf("X (pid: %6d) - %2d\n", pid, i);
      }
      exit(0);
    } else {
      pid = wait(NULL);
      printf("Child (pid: %5d) Complete\n", pid);
      pid = wait(NULL);
      printf("Child (pid: %5d) Complete\n", pid);
    }

  }

  sem_close(semaphore);
  sem_unlink("/semaphore");
  return 0;
}