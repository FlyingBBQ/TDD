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
int  cbuf_ptrpos(cbuf_t *cbuf, uint8_t *ptr);
void cbuf_write(cbuf_t *cbuf, uint8_t data);
uint8_t cbuf_read(cbuf_t *cbuf);

void cmake_test(void);

#endif
