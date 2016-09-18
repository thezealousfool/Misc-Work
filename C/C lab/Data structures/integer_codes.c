// Works but very slow
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int remove_insignificant_zeroes(int *number, int length) {
    int position;
    while (number[0] == 0) {
        position = 1;
        while (position < length) {
            number[position - 1] = number[position];
            ++position;
        }
        --length;
    }

    return length;
}

int compare_numbers (int *number1, int start, int length_number1, int number2) {
    int loop;

    if (pow(10, length_number1 - 1) > number2) {
        return 1;
    }

    int number1_integer = 0;
    for (loop = 0; loop < length_number1; ++loop) {
        number1_integer = number1_integer * 10 + number1[start + loop];
    }

    if (number1_integer > number2)
        return 1;
    else
        return 0;
}

int get_code(char *name, int *code_name) {
    int index = 0, temp_int, end_index = 0;
    while (name[index++] != '\0') {
        temp_int = name[index - 1];
        if (temp_int >= 100) {
            code_name[end_index++] = temp_int / 100;
            code_name[end_index++] = (temp_int / 10) % 10;
            code_name[end_index++] = temp_int % 10;
        }
        else {
            code_name[end_index++] = temp_int / 10;
            code_name[end_index++] = temp_int % 10;
        }
    }
    return end_index;
}

int split_add (int *code, int code_length) {
    int carry, position;
    int result_length = ceil(code_length/2.0);

    position = 1;
    carry = 0;

    while (position <= result_length) {
        if (code_length - position >= result_length) {
            code[result_length - position] += code[code_length - position] + carry;
            if (position != result_length) {
                carry = code[result_length - position] / 10;
                code[result_length - position] %= 10;
            }
        }
        else {
            code[result_length - position] += carry;
        }
        ++position;
    }

    while (code[0] > 10) {
        for (position = result_length; position > 0; --position) {
            code[position] = code[position - 1];
        }
        code[0] = code[1] / 10;
        code[1] %= 10;
        ++result_length;
    }
    
    return result_length;
}

void substract (int *number1, int start, int length_number1, int number2) {
    int position = 0;

    while (position < length_number1) {

        if (pow(10, length_number1 - position - 1) > number2) {
            ++position;        
            continue;
        }
        while (pow(10, length_number1 - position - 1) <= number2) {
            --number1[start + position];
            number2 -= (int)pow(10, length_number1 - position - 1);
        }
        ++position;
    }

    for (position = length_number1 - 1; position > 0; --position) {
        while (number1[start + position] < 0) {
            --number1[start + position - 1];
            number1[start + position] += 10;
        }
    }
}

int get_length (int number) {
    int length = 1;
    while (number > (int)pow(10,length)) {
        ++length;
    }
    return length;
}

void modulo_naive (int *number1, int length_number1, int number2) {
    while (compare_numbers(number1, 0, length_number1, number2)) {
        substract(number1, 0, length_number1, number2);
    }
}

int modulo (int *number1, int length_number1, int number2) {
    int length_number2 = get_length(number2);
    while (length_number1 > length_number2) {
        if (compare_numbers(number1, 0, length_number2, number2))
            modulo_naive(number1, length_number2, number2);
        else
            modulo_naive(number1, length_number2 + 1, number2);
        length_number1 = remove_insignificant_zeroes(number1, length_number1);
    }
    modulo_naive(number1, length_number1, number2);
    length_number1 = remove_insignificant_zeroes(number1, length_number1);
    return length_number1;
}


int main() {
    char name[50], surname[50];
    int code_name[152], code_surname[152], name_length, surname_length, loop, P;

    printf("Enter full name: ");
    scanf("%s %s", name, surname);

    name_length = get_code(name, code_name);
    surname_length = get_code(surname, code_surname);

    printf("Name: %s\nCode: ", name);
    for (loop = 0; loop < name_length; ++loop) {
        printf("%d",code_name[loop]);
    }
    printf("\n\n");

    printf("Surname: %s\nCode: ", surname);
    for (loop = 0; loop < surname_length; ++loop) {
        printf("%d",code_surname[loop]);
    }
    printf("\n\n");

    name_length = split_add(code_name, name_length);
    surname_length = split_add(code_surname, surname_length);

    printf("Name: %s\nModified Code: ", name);
    for (loop = 0; loop < name_length; ++loop) {
        printf("%d",code_name[loop]);
    }
    printf("\n\n");

    printf("Surname: %s\nModified Code: ", surname);
    for (loop = 0; loop < surname_length; ++loop) {
        printf("%d",code_surname[loop]);
    }
    printf("\n\n");

    printf("Enter a prime number: ");
    scanf("%d", &P);

    name_length = modulo(code_name, name_length, P);

    printf("Name: %s\nModulo Code: ", name);
    for (loop = 0; loop < name_length; ++loop) {
        printf("%d",code_name[loop]);
    }
    printf("\n\n");

    surname_length = modulo(code_surname, surname_length, P);

    printf("Surname: %s\nModulo Code: ", surname);
    for (loop = 0; loop < surname_length; ++loop) {
        printf("%d",code_surname[loop]);
    }
    printf("\n\n");

    /*int len, number1[6], number2, loop;

    number1[0] = 2;
    number1[1] = 1;
    number1[2] = 2;
    number1[3] = 1;
    number1[4] = 9;
    number1[5] = 7;

    number2 = 109;

    len = modulo(number1, 6, number2);

    for (loop = 0; loop < len; ++loop) {
        printf("%d ", number1[loop]);
    }
    printf("\n");*/

    return 0;
}