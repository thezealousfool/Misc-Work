#include <stdio.h>
#include <float.h>
#include <math.h>
int main() {
    float max, min, sum, sum_sq, element;
    int no_of_elements;
    max = FLT_MIN; min = FLT_MAX; no_of_elements = 0; sum = 0.0; sum_sq = 0.0;
    printf("Enter numbers (anything else to exit): \n");
    while (scanf(" %f ", &element)) {
        if (element > max) {
            max = element;
        }
        if (element < min) {
            min = element;
        }
        sum += element;
        sum_sq += pow(element, 2);
        ++no_of_elements;
    }
    printf("Minimum:\t\t%9.4f\nMaximum:\t\t%9.4f\nMean:\t\t\t%9.4f\nStandard Deviation:\t%9.4f\n", min, max, sum/no_of_elements, sqrt(sum_sq/no_of_elements - pow(sum/no_of_elements, 2)));
    printf("\t.\n");
}