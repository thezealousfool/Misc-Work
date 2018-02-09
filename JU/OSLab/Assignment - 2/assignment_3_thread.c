#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NO_PRODUCER 10
#define NO_CONSUMER 6

typedef struct {
    int _data[BUFFER_SIZE], head, tail;
} Queue;

int total, elems;
Queue queue;
pthread_mutex_t elem_mutex, total_mutex, queue_mutex;
pthread_t producer_tid[NO_PRODUCER], consumer_tid[NO_CONSUMER];

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

void* producer(void *arg) {
    int no;
    int *id = (int)arg;
    printf("%6d :: Producer started\n", id);
    while (elems >= BUFFER_SIZE);
    pthread_mutex_lock(&elem_mutex);
    ++elems;
    pthread_mutex_unlock(&elem_mutex);
    pthread_mutex_lock(&queue_mutex);
    no = (rand() % 59) + 1;
    printf("%6d :: Producer produced %2d\n", id, no);
    enqueue(&queue, no);
    pthread_mutex_unlock(&queue_mutex);
    printf("%6d :: Producer done\n", id);
}

void* consumer(void *arg) {
    int no;
    int id = (int)arg;
    printf("%6d :: Consumer started\n", id);
    while (elems <= 0);
    pthread_mutex_lock(&queue_mutex);
    no = dequeue(&queue);
    printf("%6d :: Consumer consumed %2d\n", id, no);
    pthread_mutex_unlock(&queue_mutex);
    pthread_mutex_lock(&elem_mutex);
    --elems;
    pthread_mutex_unlock(&elem_mutex);
    pthread_mutex_lock(&total_mutex);
    total += no;
    pthread_mutex_unlock(&total_mutex);
    printf("%6d :: Consumer done\n", id);
}

int main () {
    int i;

    total = 0;
    elems = 0;
    init_queue(&queue);

    if (pthread_mutex_init(&total_mutex, NULL) != 0
        || pthread_mutex_init(&elem_mutex, NULL) != 0
        || pthread_mutex_init(&queue_mutex, NULL) != 0) {
        printf("Mutex creation failed. Aborting...\n");
        return 1;
    }

    for (i = 0; i < NO_PRODUCER; ++i) {
        if (pthread_create(&(producer_tid[i]), NULL, producer, (void *)i) != 0)
            printf("Producer thread %2d creation failed\n", i);
    }

    for (i = 0; i < NO_CONSUMER; ++i) {
        if (pthread_create(&(consumer_tid[i]), NULL, consumer, (void *)i) != 0)
            printf("Consumer thread %2d creation failed\n", i);
    }

    for (i = 0; i < NO_PRODUCER; ++i) {
        pthread_join(producer_tid[i], NULL);
    }

    for (i = 0; i < NO_CONSUMER; ++i) {
        pthread_join(consumer_tid[i], NULL);
    }

    printf("Total: %3d\n", total);
    return 0;
}
