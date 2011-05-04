#include <assert.h>
#include <stdlib.h>

#include "vector.h"
#include "errors.h"

int vector_init(vector *v, unsigned int initial_size)
{
    assert(v);

    if((v->contents = malloc(sizeof(void *) * initial_size)) == NULL)
        return ERR_MALLOC;

    v->size = 0;
    v->capacity = initial_size;

    return HUGE_SUCCESS;
}

void vector_free(vector *v)
{
    assert(v);

    free(v->contents);
}

int vector_add(vector *v, void *item)
{
    assert(v);

    v->size++;
    if(v->size == v->capacity)
        vector_resize(v);

    v->contents[v->size] = item;

    return HUGE_SUCCESS;
}
