#include "circbuf.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    int i;
    char buf;
    char buf_arr[50];

    /* Create and initialize ring buffer */
    circbuf *ring_buffer = circbuf_init(50);

    /* Add elements to buffer; one at a time */
    for (i = 0; i < 100; i++) {
        circbuf_push(ring_buffer, "1", 1);
    }

    /* Dequeue all elements */
    for (i = 100;  i > 0; i--) {
        circbuf_pop(ring_buffer, &buf, 1);
        printf("Read: %d\n", buf);
    }
    printf("\n===============\n");

    circbuf_push(ring_buffer, "Hello, Ring Buffer!", 20);

    /* Dequeue all elements */
    int count = 20;
    while (count > 0) {
        /* Print contents */
        circbuf_pop(ring_buffer, &buf, 1);
        printf("Read: %c\n", buf);
        count--;
    }

    /* Add new array */
    circbuf_push(ring_buffer, "Hello again, Ring Buffer!", 26);

    /* Dequeue array in two parts */
    printf("Read:\n");
    circbuf_pop(ring_buffer, buf_arr, 13);
    /* Add \0 termination before printing */
    buf_arr[13] = '\0';
    printf("%s\n", buf_arr);
    /* Dequeue remaining */
    circbuf_pop(ring_buffer, buf_arr, 13);
    printf("%s", buf_arr);

    printf("\n===============\n");

    return 0;
}