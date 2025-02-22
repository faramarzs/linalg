#ifndef MAT_H
#define MAT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int index_t;

typedef double data_t;
typedef double *data_tp;

typedef struct {
	size_t v_size;
	size_t v_capacity;
	data_tp v_data;
} vector_t;
typedef vector_t *vector_tp;

typedef struct {
	size_t m_h;
	size_t m_w;
	data_tp m_data;
} matrix_t;
typedef matrix_t *matrix_tp;

matrix_tp matrix_new(size_t h, size_t w);
void matrix_free(matrix_tp mtp);

void matrix_set(matrix_tp m, index_t i, index_t j, data_t val);
void matrix_load(matrix_tp mtp, data_tp data);
void matrix_print(char *title, matrix_tp mtp);

matrix_tp matrix_i(size_t n);

matrix_tp matrix_add(matrix_tp m1, matrix_tp m2);
matrix_tp matrix_sub(matrix_tp m1, matrix_tp m2);
matrix_tp matrix_mul(matrix_tp m1, matrix_tp m2);

matrix_tp matrix_transpose(matrix_tp m);
matrix_tp matrix_submat(matrix_tp m, index_t start_i, index_t start_j, unsigned int h, unsigned int w);

#ifdef __cplusplus
}
#endif

#endif /* MAT_H */
