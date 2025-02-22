#include <stdio.h>
#include <stdlib.h>

#include "mat.h"

int
xmain(int argc, char **argv)
{
	data_t _coefs[] = {
		-4, 4, 3,
		3, 8, -4,
		2, -1, -5,
	};
	data_t _vals[] = {
		23, 14, -12	
	};
	/* x, y, x = { -2, 3, 1 } */
	matrix_tp m = matrix_new(3, 3);
	matrix_load(m, (data_tp) _coefs);
	matrix_print("coefs", m);
	matrix_free(m);

	matrix_tp im = matrix_i(4);
	matrix_print("I", im);


	m = matrix_add(im, im);
	matrix_print("sum", m);
	matrix_free(m);

	m = matrix_sub(im, im);
	matrix_print("sub", m);
	matrix_free(m);

	matrix_free(im);

	return 0;
}

int
main(int argc, char **argv)
{
	matrix_tp m1 = matrix_new(3, 2);
	matrix_load(m1, (data_t[]) { 
		5, -1, 
		-2, 1, 
		4, 3
	});
	matrix_print("m1", m1);
	matrix_tp m2 = matrix_new(2, 4);
	matrix_load(m2, (data_t[]) { 
		7, -2, 6, 11, 
		-3, 0, 4, 9
	});
	matrix_print("m2", m2);
	matrix_tp mul = matrix_mul(m1, m2);
	matrix_print("mul", mul);
	/* 
		38, -10, 26, 46,
		-17, 4, -8, -13,
		19, -8, 36, 71
	*/
}