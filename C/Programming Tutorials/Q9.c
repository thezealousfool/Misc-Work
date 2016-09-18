#include <stdio.h>
#include <stdlib.h>

struct c_no {
    float real, imaginary;
};

typedef struct c_no complex_number;

complex_number add (complex_number c1, complex_number c2) {
    complex_number result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}

complex_number substract (complex_number c1, complex_number c2) {
    complex_number result;
    result.real = c1.real - c2.real;
    result.imaginary = c1.imaginary - c2.imaginary;
    return result;
}

complex_number multiply (complex_number c1, complex_number c2) {
    complex_number result;
    result.real = (c1.real * c2.real) - (c1.imaginary * c2.imaginary);
    result.imaginary = (c1.real * c2.imaginary) + (c2.real * c1.imaginary);
    return result;
}

complex_number division (complex_number c1, complex_number c2) {
    complex_number result;
    result.real = ((c1.real * c2.real) + (c1.imaginary * c2.imaginary)) / ((c2.real * c2.real) - (c2.imaginary * c2.imaginary));
    result.imaginary = ((c1.imaginary * c2.real) + (c1.real * c2.imaginary)) / ((c2.real * c2.real) - (c2.imaginary * c2.imaginary));
    return result;
}

int main(void) {
    complex_number number1, number2, number3;
    number1.real = 5;
    number1.imaginary = 7;
    number2.real = 6;
    number2.imaginary = 9;
    number3 = multiply(number1, number2);
    printf("real: %f    imaginary: %f\n", number3.real, number3.imaginary);
    return 0;
}