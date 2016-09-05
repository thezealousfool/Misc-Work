#include <stdio.h>
#include <stdlib.h>

int binary_search (int *data, int begin, int end, int value) {
    int middle;
    middle = (begin + end) / 2;
    while (data[middle] != value) {
        if (end == begin) {
            middle = -1; break;
        }
        if (data[middle] < value)
            begin = middle + 1;
        else
            end = middle - 1;
        middle = (begin + end) / 2;
    }
        return middle;
}

int main() {
    int *input, no_of_elements, index, value;
    printf("Enter number of elements to be searched: ");
    scanf("%d", &no_of_elements);
    input = malloc (no_of_elements*sizeof(int));
    printf("Enetr array to be searched (sorted):\n");
    for (index = 0; index < no_of_elements; ++index) {
        scanf("%d", &input[index]);
    }
    printf("Enter value to be searched: ");
    scanf("%d", &value);
    index = binary_search(input, 0, no_of_elements-1, value);
    if (index == -1)
        printf("Value not found!!\n");
    else
        printf("Value found at index %d\n", index+1);

}