#include <stdio.h>
#include <stdlib.h>

#include "mat.h"

int
main(int argc, char **argv)
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
