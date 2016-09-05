/*input
25
*/
#include <stdio.h>

int main(void)
{
    int terms, center_value, loop;
    printf("Enter number of terms to print: ");
    scanf("%d", &terms);
    if (terms < 0) return 0;
    printf("1 ");
    --terms;
    center_value = 2;
    while (terms > 0) {
        for (loop = 2; loop < center_value && terms > 0; ++loop, --terms) {
            printf("%d ", loop);
        }
        loop -= 2;
        for (; loop > 0 && terms > 0; --loop, --terms) {
            printf("%d ", loop);
        }
        ++center_value;
    }
    return 0;
}