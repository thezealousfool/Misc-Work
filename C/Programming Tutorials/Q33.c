#include <stdio.h>
#include <math.h>

int main() {
    int binary, decimal, length;
    char bin[20], flag;
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);
    for (binary = 20; binary >= 0; --binary) {
        if (decimal >= pow(2,binary)) {
            bin[binary] = '1';
            decimal = decimal - (int)pow(2,binary);
        }
        else {
            bin[binary] = '0';
        }
    }
    flag = '0';
    printf("Binary Equivalent: ");
    for (binary=20; binary >= 0; --binary) {
        if (flag == '0'){
            if (bin[binary] == '1') {
                printf("%c", bin[binary]);
                flag = '1';
            }
        }
        else {
            printf("%c", bin[binary]);
        }
    }
    printf("\n");
    printf("Enter a binary number: ");
    scanf("%19s", bin);
    binary = 0; decimal = 0;
    for (length=0; bin[length]!='\0'; ++length);
    --length;
    while (bin[binary] != '\0') {
        if (bin[binary] == '1') {
            decimal += pow(2, length-binary);
        }
        ++binary;
    }
    printf("Decimal Equivalent: %d\n", decimal);
    return 0;
}