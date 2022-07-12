#include "circbuf.h"

#include <stdlib.h>
#include <string.h>

circbuf* circbuf_init(size_t size)
{
    circbuf* buf = malloc(sizeof(*buf));

    buf->data = malloc(size);

    buf->size = size;
    buf->head = buf->fill = 0;

    return buf;
}

static inline void advance_tail(circbuf* buf, size_t bytes)
{
    buf->fill += bytes;
}

void circbuf_push(circbuf* buf, const char* from, size_t bytes)
{
    if (bytes > circbuf_remaining(buf)) return;

    char* tail = buf->data + ((buf->head + buf->fill) % buf->size);
    char* write_end = buf->data + ((buf->head + buf->fill + bytes) % buf->size);

    if (tail <= write_end)
    {
        memcpy(tail, from, bytes);
    }
    else
    {
        char* end = buf->data + buf->size;

        size_t write = end - tail;
        memcpy(tail, from, write);

        write = bytes - write;
        memcpy(buf->data, from + write, write);
    }

    advance_tail(buf, bytes);
}

static inline void advance_head(circbuf* buf, size_t bytes)
{
    buf->head = (buf->head + bytes) % buf->size;
    buf->fill -= bytes;
}

void circbuf_pop(circbuf* buf, char* to, size_t bytes)
{
    if (bytes > circbuf_used(buf)) return;

    char* head = buf->data + buf->head;
    char* end_read = buf->data + ((buf->head + bytes) % buf->size);

    if (end_read <= head)
    {
        char* end = buf->data + buf->size;

        size_t first_read = end - head;
        memcpy(to, head, first_read);

        size_t second_read = bytes - first_read;
        memcpy(to + first_read, buf->data, second_read);
    }
    else
    {
        memcpy(to, head, bytes);
    }

    advance_head(buf, bytes);
}