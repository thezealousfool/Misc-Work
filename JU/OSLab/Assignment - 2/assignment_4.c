#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

int main () {
    int readers, writers, no, *data;
    sem_t *writers_waiting, *mutex;
    pid_t pid;

    int i;

    data = (int *)mmap(NULL , sizeof(int), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1, 0);

    *data = 0;

    printf("No of Writer: ");
    scanf("%d", &writers);
    printf("No of Readers: ");
    scanf("%d", &readers);

    writers_waiting = sem_open("/writers_waiting", O_CREAT,  0600, 0);
    mutex = sem_open("/mutex", O_CREAT,  0600, 1);

    pid = fork();

    if (pid < 0)
        fprintf(stderr, "Error creating child process\n");
    else if (pid == 0) {
        for ( i = 0; i < writers; ++i) {
            pid = fork();
            if (pid == 0) {
                break;
            } else if (pid < 0) {
                printf("%6d :: Writer %3d failed\n", getpid(), i);
            }
        }
        if (i == writers) {
            for (i = 0; i < writers; ++i) {
                pid = wait(NULL);
                printf("%5d returned\n", pid);
            }
            exit(0);
        }
        sleep(1);
        srand(time(NULL));
        no = (rand() % 59) + 1;
        sem_post(writers_waiting);
        sem_wait(mutex);
        printf("%6d :: Writer %3d writing %2d\n", getpid(), i, no);
        *data += no;
        printf("%6d :: Writer %3d done\n", getpid(), i);
        sem_post(mutex);
        sem_wait(writers_waiting);
        exit(0);
    } else {
        pid = fork();
        if (pid < 0)
            fprintf(stderr, "Error creating child process\n");
        else if (pid == 0) {
            for ( i = 0; i < readers; ++i) {
                pid = fork();
                if (pid == 0) {
                    break;
                } else if (pid < 0) {
                    printf("%6d :: Readers %3d failed\n", getpid(), i);
                }
            }
            if (i == readers) {
                for (i = 0; i < readers; ++i) {
                    pid = wait(NULL);
                    printf("%5d returned\n", pid);
                }
                exit(0);
            }
            sleep(1);
            while(1) {
                if (sem_trywait(writers_waiting) < 0) {
                    sem_wait(mutex);
                    printf("%6d :: Reader %3d read %2d\n", getpid(), i, *data);
                    printf("%6d :: Reader %3d done\n", getpid(), i);
                    sem_post(mutex);
                    exit(0);
                } else {
                    sem_post(writers_waiting);
                }
            }
        } else {
            for (i = 0; i < 2; ++i) {
                pid = wait(NULL);
                printf("%5d returned\n", pid);
            }
            sem_close(mutex);
            sem_unlink("/mutex");
            sem_close(writers_waiting);
            sem_unlink("/writers_waiting");
        }
    }
    return 0;
}