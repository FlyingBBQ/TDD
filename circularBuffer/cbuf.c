#include "cbuf.h"
#include <assert.h>

void
cbuf_init(cbuf_t *cbuf, uint8_t *buffer, size_t size)
{
    cbuf->buffer = buffer;
    cbuf->head = buffer;
    cbuf->tail = buffer;
    cbuf->size = size;
}

void
cbuf_put(cbuf_t *cbuf, uint8_t data)
{
    *(cbuf->head++) = data;
}
