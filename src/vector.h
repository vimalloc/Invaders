#ifndef VECTOR_H
#define VECTOR_H

/* Handle for a vector */
typedef struct {
    void** contents; /* The data stored in this vector */
    int size;        /* The current number of elements in this vector */
    int capacity;    /* The current capacity of this vector */
} vector;

/**
 * Initializes this vector to the given size, or 10 by default
 *
 * @param v The vector to initialize
 * @param size How many elements to initially set this vector to
 * @return 0 on success, error (< 0) on failure
 */
int vector_init(vector *v, unsigned int initial_size = 10);

/**
 * Frees all the memory used by this vector
 *
 * @param v The vector to initialize
 */
void vector_free(vector *v);

/**
 * Adds an item into the vector
 *
 * @param v The vector to add this item into
 * @param i The item to add into this vector
 * @return 0 on success, error (< 0) on failure
 */
int vector_add(vector *v, void *item);

/**
 * Clears this array
 *
 * @param v The array to clear
 */
void vector_clear(vector *v);

/* Check if an item exists in this vector */

/* Remove an item from the vector (index or first instance of item) */

#endif
