#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

typedef struct {
    int _data[BUFFER_SIZE], head, tail;
} Queue;

void init_queue (Queue *queue) {
    int loop;
    for (loop = 0; loop < BUFFER_SIZE; ++loop) {
        queue->_data[loop] = 0;
    }
    queue->head = 0;
    queue->tail = 0;
}

void enqueue (Queue *queue, int value) {
    queue->_data[queue->tail] = value;
    queue->tail = (queue->tail + 1) % BUFFER_SIZE;
}

int dequeue (Queue *queue) {
    int consumed;
    consumed = queue->_data[queue->head];
    queue->head = (queue->head + 1) % BUFFER_SIZE;
    return consumed;
}

int main () {
    int p, c, no, *total;
    Queue *queue;
    sem_t *full, *empty, *queue_mutex, *total_mutex;
    pid_t pid;

    int i;

    queue = (Queue *)mmap(NULL , sizeof(Queue), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1, 0);
    total = (int *)mmap(NULL , sizeof(int), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1, 0);

    *total = 0;
    init_queue(queue);

    printf("No of Producers: ");
    scanf("%d", &p);
    printf("No of Consumers: ");
    scanf("%d", &c);

    full = sem_open("/full", O_CREAT,  0600, BUFFER_SIZE);
    empty = sem_open("/empty", O_CREAT,  0600, 0);
    queue_mutex = sem_open("/queue_mutex", O_CREAT,  0600, 1);
    total_mutex = sem_open("/total_mutex", O_CREAT,  0600, 1);

    pid = fork();

    if (pid < 0)
        fprintf(stderr, "Error creating child process\n");
    else if (pid == 0) {
        for ( i = 0; i < p; ++i) {
            pid = fork();
            if (pid == 0) {
                break;
            } else if (pid < 0) {
                printf("%6d :: Producer %3d failed\n", getpid(), i);
            }
        }
        if (i == p) {
            for (i = 0; i < p; ++i) {
                pid = wait(NULL);
                printf("%5d returned\n", pid);
            }
            exit(0);
        }
        sleep(1);
        sem_wait(full);
        sem_wait(queue_mutex);
        no = (rand() % 59) + 1;
        printf("%6d :: Producer %3d produced %2d\n", getpid(), i, no);
        enqueue(queue, no);
        sem_post(queue_mutex);
        sem_post(empty);
        printf("%6d :: Producer %3d done\n", getpid(), i);
        exit(0);
    } else {
        pid = fork();
        if (pid < 0)
            fprintf(stderr, "Error creating child process\n");
        else if (pid == 0) {
            for ( i = 0; i < c; ++i) {
                pid = fork();
                if (pid == 0) {
                    break;
                } else if (pid < 0) {
                    printf("%6d :: Consumer %3d failed\n", getpid(), i);
                }
            }
            if (i == c) {
                for (i = 0; i < c; ++i) {
                    pid = wait(NULL);
                    printf("%5d returned\n", pid);
                }
                exit(0);
            }
            sleep(1);
            sem_wait(empty);
            sem_wait(queue_mutex);
            no = dequeue(queue);
            printf("%6d :: Consumer %3d consumed %2d\n", getpid(), i, no);
            sem_wait(total_mutex);
            *total = *total + no;
            sem_post(total_mutex);
            sem_post(queue_mutex);
            sem_post(full);
            printf("%6d :: Consumer %3d done\n", getpid(), i);
            exit(0);
        } else {
            for (i = 0; i < 2; ++i) {
                pid = wait(NULL);
                printf("%5d returned\n", pid);
            }
            printf("\nTotal %5d\n\n", *total);
            sem_close(full);
            sem_unlink("/full");
            sem_close(empty);
            sem_unlink("/empty");
            sem_close(queue_mutex);
            sem_unlink("/queue_mutex");
            sem_close(total_mutex);
            sem_unlink("/total_mutex");
        }
    }
    return 0;
}
