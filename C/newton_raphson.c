#include <stdio.h>

int main (void) {
	float f_x, df_x, new_x, old_x;
	old_x = 0;
	new_x = 15625;
	while ((old_x-new_x)>=0.00001 || (new_x-old_x)>=0.00001) {
		printf("%13.6f\t%13.6f\n",old_x,new_x);
		old_x = new_x;
		f_x = old_x*old_x*old_x*old_x*old_x*old_x-15625;
		df_x = 6*old_x*old_x*old_x*old_x*old_x;
		new_x = old_x - (f_x/df_x);
	}
	printf("%13.6f\t%13.6f\n",old_x,new_x);
	printf("Sixth root of 15625 is %f\n", new_x);
}