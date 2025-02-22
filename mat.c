#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mat.h"


matrix_tp 
matrix_new(size_t h, size_t w)
{
    matrix_tp mp = (matrix_tp) malloc(sizeof(matrix_t));
    mp->m_h = h;
    mp->m_w = w;
    mp->m_data = (data_tp) calloc(h * w, sizeof(data_t));

    return mp;
}

void 
matrix_free(matrix_tp m)
{
    if (!m) 
        return;
    if (m->m_data)
        free(m->m_data);
    free(m);
}

static data_tp
_matrix_at(matrix_tp m, index_t i, index_t j)
{
    return (data_tp) (m->m_data + (i * m->m_w + j) * sizeof(data_t));
}

void 
matrix_set(matrix_tp m, index_t i, index_t j, data_t val)
{
    *_matrix_at(m, i, j)  = val;
}

data_t 
matrix_get(matrix_tp m, index_t i, index_t j)
{
    return *_matrix_at(m, i, j);
}

void 
matrix_load(matrix_tp m, data_tp data)
{
    (void) memcpy(m->m_data, data, m->m_h * m->m_w * sizeof(data_t));
}

void 
matrix_print(char *title, matrix_tp m)
{
    if (title)
        (void) printf("%s = [\n", title);
    else
        (void) printf("[\n");
    data_tp dp = m->m_data;
    for (int i = 0; i < m->m_h; i++) {
        (void) printf("    [");
        for (int j = 0; j < m->m_w; j++) {
            printf("%7.2g ", *dp++);
        }
        (void) printf("]\n");
    }
    (void) printf("]\n");
}

matrix_tp 
matrix_i(size_t n)
{
    matrix_tp m = matrix_new(n, n);
    data_tp dp = m->m_data;
    for (int i = 0; i < n; i++) {
        *dp = 1;
        dp += n + 1;
    }
    return m;
}

matrix_tp 
matrix_add(matrix_tp m1, matrix_tp m2)
{
    if (m1->m_h != m2->m_h || m1->m_w != m2->m_w) {
        return NULL;
    }
    matrix_tp m = matrix_new(m1->m_h, m1->m_w);
    data_tp dp = m->m_data;
    data_tp dp1 = m1->m_data;
    data_tp dp2 = m2->m_data;
    for (int i = 0; i < m1->m_h * m1->m_w; i++)
        *dp++ = *dp1++ + *dp2++;

    return m;
}

matrix_tp 
matrix_sub(matrix_tp m1, matrix_tp m2)
{
    if (m1->m_h != m2->m_h || m1->m_w != m2->m_w) {
        return NULL;
    }
    matrix_tp m = matrix_new(m1->m_h, m1->m_w);
    data_tp dp = m->m_data;
    data_tp dp1 = m1->m_data;
    data_tp dp2 = m2->m_data;
    for (int i = 0; i < m1->m_h * m1->m_w; i++)
        *dp++ = *dp1++ - *dp2++;

    return m;
}

matrix_tp 
matrix_mul(matrix_tp m1, matrix_tp m2)
{

    /* @TODO: fill me */
    return NULL;
}

matrix_tp 
matrix_transpose(matrix_tp m)
{

    /* @TODO: fill me */
    return NULL;
}

matrix_tp 
matrix_submat(matrix_tp m, index_t start_i, index_t start_j, unsigned int h, unsigned int w)
{
    /* @TODO: fill me */
    return NULL;
}