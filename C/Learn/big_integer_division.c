#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 100

int remove_zero (char* s)
{
	int idx = 0;
	
	if(s == NULL)
		return 0;
	
	if(s[0] != '0')
		return 0;

	for(idx = 1; s[idx] != '\0'; ++idx)
		s[idx-1] = s[idx];
	s[idx-1] = '\0';
	return 1;
}

void subs(char* val, char* from)
{
	int idx = 0;
	int len = 0;

	if(val == NULL || from == NULL)
		return;

	if(strcmp(from, val) < 0)
		return;

	len = strlen(val);

	while(len) {
		--len;

		if(from[len] < val[len]) {
			--from[len-1];
			from[len] += 10;
		}

		from[len] -= val[len] - '0';
	}
}

char* divide (char* divisor, char* divident)
{
	int divt_len = 0, divs_len = 0;
	int itr = 0;
	int val = 0;
	int quo_idx = 0;
	char* quotient = NULL;

	if(divisor == NULL || divident == NULL)
		return NULL;

	quotient = (char*)malloc(MAXLEN * sizeof(char));
	quotient[0] = '\0';

	divt_len = strlen(divident);
	divs_len = strlen(divisor);

	itr = divt_len - divs_len + 1;

	while(itr--) {
		if(divs_len > strlen(divident)) {
			quotient[quo_idx++] = '0';
			break;
		}

		val = 0;

		while(strcmp(divisor, divident) < 0) {
			subs(divisor, divident);
			++val;
		}

		quotient[quo_idx++] = '0' + val;
		if(remove_zero(divident))
			continue;
		if(!val) {
			for(val = divs_len+1; val > 0; --val) {
				divisor[val] = divisor[val-1];
			}
			divisor[0] = '0';
			++divs_len;
		}
	}
	quotient[quo_idx] = '\0';

	while(remove_zero(divident));
	while(remove_zero(quotient));
	if(strcmp(divident, "") == 0) {
		divident[0] = '0';
		divident[1] = '\0';
	}
	if(strcmp(quotient, "") == 0) {
		quotient[0] = '0';
		quotient[1] = '\0';
	}

	return quotient;
}

int main(void)
{
	char *divisor = NULL, *divident = NULL, *quotient = NULL;

	divisor = (char*)malloc(MAXLEN * sizeof(char));
	divident = (char*)malloc(MAXLEN * sizeof(char));

	printf("Enter Divisor: ");
	scanf("%s", divisor);
	printf("Enter Divident: ");
	scanf("%s", divident);
	printf("\n");

	quotient = divide(divisor, divident);

	printf("Quotient: %s\n", quotient);
	printf("Remainder: %s\n", divident);

	free(divisor);
	free(divident);
	free(quotient);
	return 0;
}