#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <sys/types.h>
#include <stdbool.h>

/**
 * Structure holding the circular buffer.
 * Contains a buffer array and the metadata for the circular buffer.
*/
typedef struct CircularBuffer* circbuf;

/**
 * Initializes the circular buffer with the set size.
 * @param size - The size of the circular buffer to initialize.
*/
circbuf circbuf_init(size_t size);

/**
 * Frees the set circular buffere.
 * @param buf - The buffer to be freed.
*/
void circbuf_free(circbuf buf);

/**
 * Resets the given circular buffere.
 * @param buf - The buffer to be reset.
*/
void circbuf_reset(circbuf buf);

/**
 * Adds a set of bytes to the buffer.
 * Pushes data to the tail of the circular buffer from 'from' with 'len' size in byte.
 * @param buf - The buffer in which the data is to be placed.
 * @param from - A pointer to the array of bytes.
 * @param len - The size of the array.
*/
void circbuf_push(circbuf buf, char* from, size_t len);

/**
 * Saves a set number of oldest bytes in the buffer to the given location, deleting them from the buffer.
 * Returns the actual data size in byte popped, which is less or equal to the input 'len' parameter.
 * @param buf - The buffer from which the data is to be read.
 * @param to - A pointer to the array where the data is to be placed.
 * @param len - The maximum number of bytes to return.
*/
size_t circbuf_pop(circbuf buf, char* to, size_t len);

/**
 * Saves a set number of oldest bytes in the buffer to the given location.
 * Returns the actual data size in byte peeked, which is less or equal to the input 'len' parameter.
 * Doesn't delete them from the buffer.
 * @param buf - The buffer from which the data is to be read.
 * @param to - A pointer to the array where the data is to be placed.
 * @param len - The maximum number of bytes to return.
*/
size_t circbuf_peek(circbuf buf, char* to, size_t len);

#endif