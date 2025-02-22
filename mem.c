#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mem.h"
#include "log.h"

static int _mem_count;			/* one plus last index of allocated blocks */
static int _mem_occupied;		/* number of blocks which does have values */
static int _mem_capacity = 4;	/* total number of allocated buffers */
static mem_block_tp *_mem_blocks;

#define	CLEAR(memp)	{ (memp)->mem_buf = NULL; (memp)->mem_size = 0; --_mem_occupied; }

/*
 * Registers an already allocated memory in out list.
 */
static void
_reg_mem_block(void *ptr, size_t sz)
{
	if (_mem_blocks == NULL) {
		_mem_blocks = calloc(_mem_capacity, sizeof(mem_block_tp));
	}

	mem_block_tp memp = NULL;

	/* first, try to reuse a free block item */
	for (int i = 0; i < _mem_count; i++) {
		if (!(_mem_blocks[i]->mem_buf)) {
			memp = _mem_blocks[i];
			break;
		}
	}

	/* free block not found, try to allocate a new one */
	if (!memp) {
		while (_mem_count >= _mem_capacity) {
			_mem_capacity <<= 1;
			_mem_blocks = (mem_block_tp *) realloc((void *) _mem_blocks, 
							_mem_capacity * sizeof(void *));
		}
		memp = (mem_block_tp) malloc(sizeof(mem_block_t));
		_mem_blocks[_mem_count++] = memp;
	}

	memp->mem_size = sz;
	memp->mem_buf = ptr;
	_mem_occupied++;
}

/*
 * Unregisters given allocated space from our block list. Returns 1 if blocks is found,
 * 0 otherwise.
 */
static int
_unreg_mem_block(void *ptr)
{
	for (int i = 0; i < _mem_count; i++) {
		if (_mem_blocks[i]->mem_buf == ptr) {
			CLEAR(_mem_blocks[i]);

			return 1;
		}
	}
	
	return 0;
}

/*
 * Walk through all registered memory blocks and clean them. Return number of blocks cleared.
 */
int
mem_free_all()
{
	int cleared = 0;
	for (int i = 0; i < _mem_count; i++) {
		if (_mem_blocks[i]->mem_buf) {
			(void) free(_mem_blocks[i]->mem_buf);
			CLEAR(_mem_blocks[i]);
			++cleared;
		}
	}

	return cleared;
}

/*
 * Allocated given size of memory, registers it and return the allocated pointer.
 */
void *
mem_alloc(size_t size) 
{
	void *p = malloc(size);
	_reg_mem_block(p, size);

	return p;
}

/*
 * Free up the space allocated for given pointer if it's found in our registrar.
 * Returns 1 if free up happens, 0 otherwise.
 */
int
mem_free(void *p)
{
	int count = _unreg_mem_block(p);
	if (!count) {
		return 0;
	}

	(void) free(p);
	return 1;
}

int
mem_is_allocated(void *p) 
{
	for (int i = 0; i < _mem_count; i++) {
		if (_mem_blocks[i]->mem_buf == p) {
			return 1;
		}
	}

	return 0;
}

#ifdef MAIN
int
main()
{
	int freed[] = { 2, 3, 7, 8 };
	int sizes[] = { 123, 14, 569, 1039, 945, 8549, 3400, 1847, 7740, 11208 };
	void *pointers[100];

	for (int i = 0; i < (sizeof(sizes) / sizeof(int)); i++) {
		pointers[i] = mem_alloc(sizes[i]);	
	}
	(void) printf("%lu pointers allocated...\n", sizeof(sizes) / sizeof(int));
	assert(_mem_count == 10);
	assert(_mem_occupied == 10);

	for (int i = 0; i < (sizeof(freed) / sizeof(int)); i++) {
		assert(mem_free(pointers[freed[i]]));
	}
	(void) printf("%lu pointers freed...\n", sizeof(freed) / sizeof(int));
	assert(_mem_count == 10);
	assert(_mem_occupied == 6);

	for (int i = 0; i < (sizeof(freed) / sizeof(int)); i++) {
		assert(!mem_free(pointers[freed[i]] + 1));
	}

	assert(_mem_count == 10);
	assert(_mem_occupied == 6);
	int _cur_cap = _mem_capacity;
	(void) mem_alloc(123);
	(void) mem_alloc(321);
	assert(_mem_count == 10);
	assert(_mem_occupied == 8);
	assert(_mem_capacity == _cur_cap);


	int count = mem_free_all();
	(void) printf("%d pointers cleared.\n", count);
	assert(count == 8);	

	return 0;
}
#endif
