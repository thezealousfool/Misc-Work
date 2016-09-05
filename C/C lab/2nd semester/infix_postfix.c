#include <stdio.h>

int main() {
	char operators[51], temp;
	char input[101], output[101];
	int index, output_index, operator_index;
	scanf("%100[^\n]", input);
	index = 0;
	temp = input[index];
	output_index = 0;
	operator_index = 0;
	while (temp!='\0') {
		if ((temp>='a' && temp<='z') || (temp>='A' && temp<='Z')) {
			output[output_index] = temp;
			++output_index;
		}
		else if (temp>='0' && temp<='9') {
			output[output_index] = temp;
			++output_index;
		}
		else if (temp=='(') {
			operators[operator_index] = '(';
			++operator_index;
		}
		else if (temp==')') {
			while (operators[--operator_index] != '(') {
				output[output_index++] = operators[operator_index];
			}
		}
		else {
			operators[operator_index] = temp;
			++operator_index;
		}
		++index;
		temp = input[index];
	}
	output[output_index] = '\0';
	printf("Postfix: %s\n", output);
	return 0;
}