#ifndef MEM_H
#define MEM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	size_t mem_size;
	void *mem_buf;
} mem_block_t;
typedef mem_block_t *mem_block_tp;

void *mem_alloc(size_t size);
int mem_free(void *p);
int mem_free_all();
int mem_is_allocated(void *p);

#ifdef __cplusplus
}
#endif

#endif /* MEM_H */
