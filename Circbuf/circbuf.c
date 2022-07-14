#include "circbuf.h"

#include <string.h>
#include <malloc.h>

/**
 * @file
 * The implementation of circular buffer functions.
*/

struct CircularBuffer {
    size_t size;        // capacity
    size_t dataSize;    // number of stored elements
    size_t tail;        // head offset - the oldest byte position offset
    size_t head;        // tail offset - the lastest byte position offset
    char* buffer;
};


circbuf circbuf_init(size_t size)
{
    size_t full_size = sizeof(struct CircularBuffer) + size;
    circbuf buffer = malloc(full_size);
    buffer->buffer = buffer + sizeof(struct CircularBuffer);
    buffer->size = size;
    circbuf_reset(buffer);
    return buffer;
}

void circbuf_free(circbuf buf)
{
    circbuf_reset(buf);
    buf->size = 0;
    buf->dataSize = 0;
    buf->buffer = NULL;
    free(buf);
}

void circbuf_reset(circbuf buf)
{
    buf->head = -1;
    buf->tail = -1;
    buf->dataSize = 0;
}

void circbuf_push(circbuf buf, char* from, size_t len) {
    if (len == 0)
        return;

    if (len > buf->size)    //overflow case
    {
        size_t overflow = len - buf->size;
        len = buf->size;
        from = from + overflow;
    }

    bool resetHead = false;
    
    if (buf->tail + len < buf->size)
    {
        memcpy(&buf->buffer[buf->tail + 1], from, len);

        if ((buf->tail < buf->head) && (buf->tail + len >= buf->head))
            resetHead = true;

        buf->tail += len;
    }
    else  //overflow case
    {
        size_t remainSize = buf->size - buf->tail - 1;
        memcpy(&buf->buffer[buf->tail + 1], from, remainSize);

        size_t coverSize = len - remainSize;
        memcpy(buf->buffer, from + remainSize, coverSize);

        if (buf->tail < buf->head || coverSize > buf->head)
            resetHead = true;

        buf->tail = coverSize - 1;
    }

    if (buf->head == -1)
        buf->head = 0;

    if (resetHead)
    {
        if (buf->tail + 1 < buf->size)
            buf->head = buf->tail + 1;
        else
            buf->head = 0;

        buf->dataSize = buf->size;
    }
    else
    {
        if (buf->tail >= buf->head)
            buf->dataSize = buf->tail - buf->head + 1;
        else
            buf->dataSize = buf->size - (buf->head - buf->tail - 1);
    }
}

size_t circbuf_read(circbuf buf, size_t len, char *to, bool pop)
{
    if(buf->dataSize == 0 || len == 0 || !to)
        return 0;

    size_t read_len = len;

    if(buf->dataSize < read_len)
        read_len = buf->dataSize;


    if(buf->head <= buf->tail)
    {
        memcpy(to, &buf->buffer[buf->head], read_len);

        if(pop)
        {
            buf->head += read_len;
            if(buf->head > buf->tail)
            {
                buf->head = -1;
                buf->tail = -1;
            }
        }
    }
    else
    {
        if(buf->head + read_len <= buf->size)
        {
            memcpy(to, &buf->buffer[buf->head], read_len);

            if(pop)
            {
                buf->head += read_len;
                if(buf->head == buf->size)
                    buf->head = 0;
            }
        }
        else
        {
            size_t read1 = buf->size - buf->head;
            memcpy(to, &buf->buffer[buf->head], read1);

            size_t read2 = read_len - read1;
            memcpy(to + read1, buf->buffer, read2);

            if(pop)
            {
                buf->head = read2;
                if(buf->head > buf->tail)
                {
                    buf->head = -1;
                    buf->tail = -1;
                }
            }
        }
    }

    if(pop)
        buf->dataSize -= read_len;

    return read_len;
}

size_t circbuf_pop(circbuf buf, char* to, size_t len) {
    return circbuf_read(buf, len, to, true);
}

size_t circbuf_peek(circbuf buf, char* to, size_t len) {
    return circbuf_read(buf, len, to, false);
}