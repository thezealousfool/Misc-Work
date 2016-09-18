#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main(void) {
    int length, position, loop;
    float probability, random_generated_no;
    char *road;
    time_t seed;
    printf("Road is marked 0 to N\nEnter value of N: ");
    scanf("%d", &length);
    road = malloc((length+2)*sizeof(char));
    for (loop = 0; loop <= length; ++loop)
        road[loop] = '-';
    road[length+1] = '\0';
    printf("Enter starting position of walker: ");
    scanf("%d", &position);
    road[position] = '*';
    printf("Enter probability of forward step (P): ");
    scanf("%f", &probability);
    printf("\n%s\n", road);
    srand(time(NULL));
    while (position != 0 && position != length) {
        road[position] = '-';
        random_generated_no = ((float)rand()) / RAND_MAX;
        if (random_generated_no <= probability)
            ++position;
        else
            --position;
        road[position] = '*';
        printf("\n%s\n", road);
    }
    return 0;
}