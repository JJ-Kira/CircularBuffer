#include "circbuf.h"

#include <stdlib.h>
#include <string.h>

/**
 * @file
 * The implementation of circular buffer functions.
*/


circbuf* circbuf_init(size_t size)
{
    circbuf* buf = malloc(sizeof(*buf));

    buf->data = malloc(size);

    buf->size = size;
    buf->head = buf->tail = 0;

    return buf;
}

static inline void inc_tail(circbuf* buf, size_t bytes)
{
    buf->tail += bytes;
}

static inline void inc_head(circbuf* buf, size_t bytes)
{
    buf->head = (buf->head + bytes) % buf->size;
    buf->tail -= bytes;
}

void circbuf_push(circbuf* buf, const char* from, size_t len)
{
    if (len > circbuf_remaining(buf)) return;

    char* tail = buf->data + ((buf->head + buf->tail) % buf->size);
    char* write_end = buf->data + ((buf->head + buf->tail + len) % buf->size);

    if (tail <= write_end)
    {
        memcpy(tail, from, len);
    }
    else
    {
        char* end = buf->data + buf->size;

        size_t write = end - tail;
        memcpy(tail, from, write);

        write = len - write;
        memcpy(buf->data, from + write, write);
    }

    inc_tail(buf, len);
}

void circbuf_pop(circbuf* buf, char* to, size_t len)
{
    if (len > circbuf_used(buf)) return;

    char* head = buf->data + buf->head;
    char* end_read = buf->data + ((buf->head + len) % buf->size);

    if (end_read <= head)
    {
        char* end = buf->data + buf->size;

        size_t read = end - head;
        memcpy(to, head, read);

        read = len - read;
        memcpy(to + read, buf->data, read);
    }
    else
    {
        memcpy(to, head, len);
    }

    inc_head(buf, len);
}