#include <stdio.h>

int main() {
    int loop1, loop2, column;
    int inner_loop[4];
    printf("\tA\tB\tf1\tf2\tf3\tf4\tf5\tf6\tf7\tf8\tf9\tf10\tf11\tf12\tf13\tf14\tf15\tf16\n\n");
    column = 0;
    for (loop1 = 0; loop1 < 2; ++loop1) {
        for (loop2 = 0; loop2 < 2; ++loop2) {
            printf("\t%d\t%d\t", loop1, loop2);
            for (inner_loop[3] = 0; inner_loop[3] < 2; ++inner_loop[3]) {
                for (inner_loop[2] = 0; inner_loop[2] < 2; ++inner_loop[2]) {
                    for (inner_loop[1] = 0; inner_loop[1] < 2; ++inner_loop[1]) {
                        for (inner_loop[0] = 0; inner_loop[0] < 2; ++inner_loop[0]) {
                            printf("%d\t", inner_loop[column]);
                        }
                    }
                }
            }
            ++column;
            printf("\n");
        }
    }
    return 0;
}