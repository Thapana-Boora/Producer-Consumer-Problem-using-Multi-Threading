#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BUFFER 20

int buffer[MAX_BUFFER];
int in = 0, out = 0;
int buffer_size;

int totalProduced = 0;
int totalConsumed = 0;

pthread_mutex_t mutex;
sem_t empty, full;

void displayBuffer()
{
    printf("Buffer: ");
    for(int i = 0; i < buffer_size; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void *producer(void *arg)
{
    int id = *((int*)arg);

    for(int i = 0; i < 5; i++)
    {
        int item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d produced: %d\n", id, item);

        in = (in + 1) % buffer_size;
        totalProduced++;

        displayBuffer();

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(rand()%3);
    }
}

void *consumer(void *arg)
{
    int id = *((int*)arg);

    for(int i = 0; i < 5; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        buffer[out] = 0;

        printf("Consumer %d consumed: %d\n", id, item);

        out = (out + 1) % buffer_size;
        totalConsumed++;

        displayBuffer();

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand()%3);
    }
}

int main()
{
    int pCount = 2, cCount = 2;

    printf("Enter buffer size (max 20): ");
    scanf("%d", &buffer_size);

    pthread_t producers[pCount], consumers[cCount];
    int pID[pCount], cID[cCount];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);

    for(int i = 0; i < pCount; i++)
    {
        pID[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &pID[i]);
    }

    for(int i = 0; i < cCount; i++)
    {
        cID[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &cID[i]);
    }

    for(int i = 0; i < pCount; i++)
        pthread_join(producers[i], NULL);

    for(int i = 0; i < cCount; i++)
        pthread_join(consumers[i], NULL);

    printf("\nFinal Statistics\n");
    printf("Total Produced: %d\n", totalProduced);
    printf("Total Consumed: %d\n", totalConsumed);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}