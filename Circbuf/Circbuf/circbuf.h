#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <stdbool.h>
#include <stddef.h>

typedef struct
{
    char* data;
    size_t size;

    size_t head;
    size_t fill;
} circbuf;

circbuf* circbuf_init(size_t size);

static inline bool circbuf_is_empty(circbuf* buf)
{
    return buf->fill == 0;
}

static inline bool circbuf_is_full(circbuf* buf)
{
    return buf->fill == buf->size;
}

static inline size_t circbuf_size(circbuf* buf)
{
    return buf->size;
}

static inline size_t circbuf_used(circbuf* buf)
{
    return buf->fill;
}

static inline size_t circbuf_remaining(circbuf* buf)
{
    return buf->size - buf->fill;
}

void circbuf_push(circbuf* buf, const char* from, size_t bytes);;

void circbuf_pop(circbuf* buf, char* to, size_t bytes);

#endif