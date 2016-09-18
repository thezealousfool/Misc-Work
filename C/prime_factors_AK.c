#include <stdio.h>
#include <math.h>
int main(void) {
  
    int number, n, root, d;
    
    //Find prime factors.
  
    while (scanf("%d", &number)) {
          root = sqrt(number);
          n = number; d = 2;
          printf("%d" " = ", number);
          for (d = 2; d <= root; d = d + 2) {
              while ((n % d == 0) && (n!=d)) {
                    printf("%d" " * ", d); 
                    n = n / d;
              };
              if (d==2)
                d=1;
          };
          if (n == number) printf("PRIME NUMBER");
          else printf("%d", n);
          printf("\n");
    };
  
  

    return 0;
}

