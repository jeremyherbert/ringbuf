/* SPDX-License-Identifier: MIT */

#include "ringbuf.h"

void ringbuf_init(ringbuf_t *ringbuf, ringbuf_element_t *buffer, size_t buffer_size) {
    ringbuf->buf = buffer;
    ringbuf->buffer_size = buffer_size;
    ringbuf->head = 0;
    ringbuf->tail = 0;
}

size_t ringbuf_push(ringbuf_t *ringbuf, const ringbuf_element_t *data, size_t len) {
    if (len == 0) return 0;

    size_t push_len;
    size_t old_len = ringbuf_len(ringbuf);

    if (ringbuf->buffer_size <= (len + old_len)) {
        push_len = ringbuf->buffer_size - old_len;
        ringbuf->is_full = true;
    } else {
        push_len = len;
    }

    for (size_t i=0; i<push_len; i++) {
        ringbuf->buf[ringbuf->tail] = data[i];
        ringbuf->tail = (ringbuf->tail + 1) % ringbuf->buffer_size;
    }

    return push_len;
}

size_t ringbuf_pop(ringbuf_t *ringbuf, ringbuf_element_t *data, size_t len) {
    if (len == 0) return 0;

    size_t pop_len;
    size_t old_len = ringbuf_len(ringbuf);

    if (len > old_len) {
        pop_len = old_len;
    } else {
        pop_len = len;
    }

    for (size_t i=0; i < pop_len; i++) {
        data[i] = ringbuf->buf[ringbuf->head];
        ringbuf->head = (ringbuf->head + 1) % ringbuf->buffer_size;
    }

    if (pop_len) {
        ringbuf->is_full = false;
    }

    return pop_len;
}

size_t ringbuf_len(ringbuf_t *ringbuf) {
    if (ringbuf->is_full) return ringbuf->buffer_size;
    else if (ringbuf->tail == ringbuf->head) return 0;
    else if (ringbuf->head < ringbuf->tail) {
        return ringbuf->tail - ringbuf->head;
    } else {
        return (ringbuf->buffer_size - ringbuf->head + ringbuf->tail);
    }
}

bool ringbuf_is_full(ringbuf_t *ringbuf) {
    return ringbuf->is_full;
}