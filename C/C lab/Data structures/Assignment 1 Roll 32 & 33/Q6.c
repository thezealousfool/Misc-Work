/*
Q. Convert your name and surname into large integers
   by juxtaposing integer codes for alphabet. Print
   the corresponding converted integer. Cut the large
   integers into two halves and add the two halves.
   Compute the remainder by dividing the numbers by 
   a 4 digit prime number.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 50

int remove_insignificant_zeroes(int *number, int length, int no_of_zeroes) {
    int position = no_of_zeroes;
    while (position < length) {
        number[position - no_of_zeroes] = number[position];
        ++position;
    }
    return length - no_of_zeroes;
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

int get_length (int number) {
    int length = 1;
    while (number >= (int)pow(10,length)) {
        ++length;
    }
    return length;
}

int modulo_naive (int *number1, int length_number1, int number2) {
    int number1_integer = 0, new_length, loop;
    for (loop = 0; loop < length_number1; ++loop) {
        number1_integer = number1_integer * 10 + number1[loop];
    }
    number1_integer %= number2;
    new_length = get_length(number1_integer);
    for (loop = 0; loop < length_number1 - new_length; ++loop) {
        number1[loop] = 0;
    }
    for (loop = length_number1 - 1; loop >= length_number1 - new_length; --loop) {
        number1[loop] = number1_integer%10;
        number1_integer /= 10;
    }
    return length_number1 - new_length;
}

int modulo (int *number1, int length_number1, int number2) {
    int no_of_zeroes, length_number2 = get_length(number2);
    while (length_number1 > length_number2) {
        if (compare_numbers(number1, 0, length_number2, number2))
            no_of_zeroes = modulo_naive(number1, length_number2, number2);
        else
            no_of_zeroes = modulo_naive(number1, length_number2 + 1, number2);
        length_number1 = remove_insignificant_zeroes(number1, length_number1, no_of_zeroes);
    }
    no_of_zeroes = modulo_naive(number1, length_number1, number2);
    length_number1 = remove_insignificant_zeroes(number1, length_number1, no_of_zeroes);
    return length_number1;
}


int main() {
    char name[MAX_INPUT_LENGTH], surname[MAX_INPUT_LENGTH];
    int code_name[3*MAX_INPUT_LENGTH + 2], code_surname[3*MAX_INPUT_LENGTH + 2], name_length, surname_length, loop, P;

    printf("Enter full name (Name and Surname): ");
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

    printf("Enter a 4 digit prime number (e.g 1019): ");
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

    return 0;
}