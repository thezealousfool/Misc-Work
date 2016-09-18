#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
struct coordinates {
    int x, y;
};

typedef struct coordinates point;

double calculate_distance (point p1, point p2) {
    return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
}

int main () {
    int loop1, loop2, no_of_elements_discovered = 0;
    point data[] = { {0,0} , {1,1} , {3,1} , {2,4} , {6,3} , {6,6} , {5,2} , {3,5} };
    int no_of_points = 8;
    double smallest_distance;
    point smallest_distance_point1, smallest_distance_point2;
    int present_level = 1;
    double* distances = malloc(((no_of_points*(no_of_points-1))/2)*sizeof(int));
    int* discovered = malloc (no_of_points*sizeof(int));
    for (loop1=0; loop1<no_of_points; ++loop1)
        for (loop2=loop1+1; loop2<no_of_points; ++loop2)
            distances[loop1*6+loop2] = calculate_distance(data[loop1], data[loop2]);
    for (loop1=0; loop1<no_of_points; ++loop1)
        discovered[loop1] = 0;
    while (no_of_elements_discovered<no_of_points) {
        smallest_distance = FLOAT_MAX;
        for (loop1 = 0; loop1<((no_of_points*(no_of_points-1))/2); ++loop1) {
            if (distances[loop1] < smallest_distance && discovered[loop1]!=present_level) {
                
            }
        }
    }
    return 0;
}