/* SPDX-License-Identifier: MIT */

#include <string.h>
#include <assert.h>
#include "ringbuf.h"

int main() {
    uint8_t buf[8];
    uint8_t tmp[10];
    ringbuf_t ringbuf;
    ringbuf_init(&ringbuf, &buf[0], 8);

    // simple push and pop
    assert(ringbuf_push(&ringbuf, "a", 1) == 1);
    assert(ringbuf_pop(&ringbuf, &tmp[0], 1) == 1);
    assert(memcmp(tmp, "a", 1) == 0);

    // full push and pop
    assert(ringbuf_push(&ringbuf, "12345678", 8) == 8);
    assert(ringbuf_is_full(&ringbuf) == true);
    assert(ringbuf_pop(&ringbuf, &tmp[0], 8) == 8);
    assert(memcmp("12345678", tmp, 8) == 0);

    // test push when full
    assert(ringbuf_push(&ringbuf, "12345678", 8) == 8);
    assert(ringbuf_push(&ringbuf, "12345678", 8) == 0);
    assert(ringbuf_is_full(&ringbuf) == true);

    // test wrapping
    assert(ringbuf_pop(&ringbuf, &tmp[0], 4) == 4);
    assert(ringbuf_is_full(&ringbuf) == false);
    assert(memcmp("1234", tmp, 4) == 0);

    assert(ringbuf_push(&ringbuf, "abcd", 4) == 4);
    assert(ringbuf_is_full(&ringbuf) == true);
    assert(ringbuf_pop(&ringbuf, &tmp[0], 8) == 8);
    assert(memcmp(&tmp, "5678abcd", 8) == 0);

    // test empty pop
    assert(ringbuf_pop(&ringbuf, &tmp, 8) == 0);

    // test zero push
    assert(ringbuf_push(&ringbuf, "abc", 0) == 0);

    // test zero pop
    assert(ringbuf_pop(&ringbuf, &tmp[0], 0) == 0);

    // test push larger than buffer
    assert(ringbuf_push(&ringbuf, "1234567890", 10) == 8);

    // test pop larger than buffer
    assert(ringbuf_pop(&ringbuf, &tmp[0], 10) == 8);

    return 0;
}
