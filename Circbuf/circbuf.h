#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Structure holding the circular buffer.
 * Contains a buffer array and the metadata for the circular buffer.
*/
typedef struct
{
    char* data;
    size_t size;

    size_t head;
    size_t tail;
} circbuf;

/**
 * Initializes the circular buffer with the set size.
 * @param size - The size of the circular buffer to initialize.
*/
circbuf* circbuf_init(size_t size);

/**
 * Returns whether the buffer is empty.
 * @param buf - The buffer to be checked.
 * @return 1 if empty; 0 otherwise.
*/
static inline bool circbuf_is_empty(circbuf* buf)
{
    return buf->tail == 0;
}

/**
 * Returns whether the buffer is full.
 * @param buf - The buffer to be checked.
 * @return 1 if full; 0 otherwise.
*/
static inline bool circbuf_is_full(circbuf* buf)
{
    return buf->tail == buf->size;
}

/**
 * Returns the size of the buffer.
 * @param buf - The buffer whose size is to be returned.
 * @return buf->size.
*/
static inline size_t circbuf_size(circbuf* buf)
{
    return buf->size;
}

/**
 * Returns the number of elements that are stored in the buffer.
 * @param buf - The buffer whose number of elements is to be returned.
*/
static inline size_t circbuf_used(circbuf* buf)
{
    return buf->tail;
}

/**
 * Returns the number of elements that are stored in the buffer.
 * @param buf - The buffer whose number of remaining elements is to be returned.
*/
static inline size_t circbuf_remaining(circbuf* buf)
{
    return buf->size - buf->tail;
}

/**
 * Adds a set of bytes to the buffer.
 * @param buf - The buffer in which the data is to be placed.
 * @param from - A pointer to the array of bytes.
 * @param len - The size of the array.
*/
void circbuf_push(circbuf* buf, const char* from, size_t len);;

/**
 * Returns the set number of oldest bytes in the buffer.
 * @param buf - The buffer from which the data is to be read.
 * @param to - A pointer to the array where the data is to be placed.
 * @param len - The maximum number of bytes to return.
*/
void circbuf_pop(circbuf* buf, char* to, size_t len);

#endif