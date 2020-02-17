This repository contains a simple, embedded-friendly ringbuffer implementation. All memory is statically allocated. 

License is MIT.

Usage:
```c
uint8_t buf[8];
ringbuf_t ringbuf;
ringbuf_init(&ringbuf, &buf[0], 8); 

size_t count = ringbuf_push(&ringbuf, "12345678", 8);
// count == 8, indicating that all data was pushed
count = ringbuf_push(&ringbuf, "abcdefgh", 8);
// count == 0, indicating no data was pushed as the buffer was full

uint8_t tmp[10];
count = ringbuf_pop(&ringbuf, &tmp, 10);
// count == 8, indicating that only 8 bytes could be popped instead of 10
```