#include "cbuf.h"
#include <assert.h>
#include <stdio.h>

void
cbuf_init(cbuf_t *cbuf, uint8_t *buffer, size_t size)
{
    cbuf->buffer = buffer;
    cbuf->head = buffer;
    cbuf->tail = buffer;
    cbuf->size = size;
}

int
cbuf_ptrpos(cbuf_t *cbuf, uint8_t *ptr)
{
    return (ptr - cbuf->buffer);
}

void
cbuf_write(cbuf_t *cbuf, uint8_t data)
{
    if (cbuf_ptrpos(cbuf, cbuf->head) >= cbuf->size)
    {
        cbuf->head = cbuf->buffer;
    }

    *(cbuf->head++) = data;
}

uint8_t
cbuf_read(cbuf_t *cbuf)
{
    if (cbuf_ptrpos(cbuf, cbuf->tail) >= cbuf->size)
    {
        cbuf->tail = cbuf->buffer;
        //return (cbuf->buffer[pos]);
    }

    int pos = cbuf_ptrpos(cbuf, cbuf->tail);
    cbuf->tail++;

    return (cbuf->buffer[pos]);
}



