/*input
30000
*/
#include <stdio.h>
#define _len 122000

unsigned int _result [_len];
int _length = 0;

void _initialize_array () {
	for (int i=0; i<_len; i++) {
		_result [i]=-1;
	}
	_result [0] = 1;
	_length = 1;
}

void _multiply (int n) {
	int _carry = 0;
	int _position = 0;
	int _temp = 0;
	_length = 0;
	do {
		if (_result [_position] != -1) {
			_temp = _result [_position] * n + _carry;
			_carry = _temp / 10;
			_result [_position] = _temp % 10;
		}
		else {
			_result [_position] = _carry % 10;
			_carry = _carry / 10;
		}
		_position++;
		_length++;
	}
	while ( _result [_position] != -1 || _carry != 0 );
}

void _factorial (int n) {
	if (n == 1) {
		return;
	}
	else {
		_multiply (n);
		_factorial (n-1);
	}
}

void _display_array () {
	for (int i = _length-1; i>-1; i--) {
		printf("%d",_result [i]);
	}
}

void _display_digits () {
	printf("\nDigits: %d\n",_length);
}

int main () {
	int _input = 1;
	_initialize_array ();
	scanf("%d",&_input);
	_factorial (_input);
	_display_array ();
	_display_digits ();
	return 0;
}
