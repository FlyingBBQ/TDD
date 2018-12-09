#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stddef.h>

/* make the circular buffer an Abstract Data Type (ADT) */
typedef struct
circular_buffer {
    uint8_t *buffer;
    uint8_t *head;
    uint8_t *tail;
    size_t size;
} cbuf_t;

/* circular buffer functions */
void cbuf_init(cbuf_t *cbuf, uint8_t *buffer, size_t size);
void cbuf_put(cbuf_t *cbuf, uint8_t data);

#endif
