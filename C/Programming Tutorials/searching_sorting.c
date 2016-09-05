#include <stdio.h>
#include <stdlib.h>

int binary_search (int *data, int start, int end, int key) {
    int middle;
    middle = (start + end) / 2;
    while (data[middle] != key) {
        if (start == end)
            return -1;
        if (data[middle] > key) 
            end = middle - 1;
        else
            start = middle + 1;
        middle = (start + end) / 2;
    }
    return middle;
}

int linear_search (int *data, int start, int end, int key) {
    int loop;
    for (loop = start; loop <= end; ++loop) {
        if (data[loop] == key)
            return loop;
    }
    return -1;
}

void insertion_sort (int *data, int start, int end) {
    int loop1, loop2, key;
    for (loop1 = start+1; loop1 <= end; ++loop1) {
        key = data[loop1];
        for (loop2 = loop1; loop2 >= 0; --loop2) {
            if (loop2 - 1 < start || data[loop2-1] < key) {
                data[loop2] = key;
                break;
            }
            data[loop2] = data[loop2-1];
        }
    }
}

void print_data (int *data, int start, int end) {
    int loop;
    printf("%d", data[start]);
    for (loop = start+1; loop <= end; ++loop) {
        printf(" , %d", data[loop]);
    }
    printf("\n");
}

int main(void) {
    int *data, no_data, search, loop, index;
    printf("Enter number of elements: ");
    scanf("%d", &no_data);
    data = malloc(no_data*sizeof(int));
    printf("Enter %d values:\n", no_data);
    for (loop=0; loop<no_data; ++loop) {
        scanf("%d", &data[loop]);
    }
    print_data(data, 0, no_data-1);
    printf("\n");
    printf("Enter value to search: ");
    scanf("%d", &search);
    index = linear_search(data, 0, no_data-1, search);
    if (index >= 0)
        printf("Value found at position %d\n", index+1);
    else
        printf("Value not found\n");
    printf("\nSorting\n\n");
    insertion_sort(data, 0, no_data-1);
    print_data(data, 0, no_data-1);
    printf("\n");
    printf("Enter value to search: ");
    scanf("%d", &search);
    index = binary_search(data, 0, no_data-1, search);
    if (index >= 0)
        printf("Value found at position %d\n", index+1);
    else
        printf("Value not found\n");
    return 0;
}