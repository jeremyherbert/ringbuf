/* SPDX-License-Identifier: MIT */

#ifndef RINGBUF_RINGBUF_H
#define RINGBUF_RINGBUF_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// this is the type that will be stored in the ringbuffer
typedef uint8_t ringbuf_element_t;

typedef struct {
    ringbuf_element_t *buf;
    size_t head, tail;
    size_t buffer_size;
    bool is_full;
} ringbuf_t;

void ringbuf_init(ringbuf_t *ringbuf, ringbuf_element_t *buffer, size_t buffer_size);

size_t ringbuf_push(ringbuf_t *ringbuf, const ringbuf_element_t *data, size_t len);
size_t ringbuf_pop(ringbuf_t *ringbuf, ringbuf_element_t *data, size_t len);

size_t ringbuf_len(ringbuf_t *ringbuf);
bool ringbuf_is_full(ringbuf_t *ringbuf);

#endif //RINGBUF_RINGBUF_H
