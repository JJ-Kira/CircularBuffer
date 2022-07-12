#include "circbuf.h"

#include <stdio.h>

int main(void) {
    int i;
    char buf;
    char buf_arr[50];

    /* Create and initialize circular buffer */
    circbuf *ring_buffer = circbuf_init(50);

    /* Push elements to buffer; one at a time */
    for (i = 0; i < 100; i++) {
        circbuf_push(ring_buffer, "1", 1);
    }

    /* Pop all elements */
    for (i = 100;  i > 0; i--) {
        circbuf_pop(ring_buffer, &buf, 1);
        printf("Read: %d\n", buf);
    }
    printf("\n===============\n");

    /* Push multiple elements to buffer at once */
    circbuf_push(ring_buffer, "Hello, Circ Buffer!", 20);

    /* Pop all elements */
    i = 20;
    while (i > 0) {
        circbuf_pop(ring_buffer, &buf, 1);
        printf("Read: %c\n", buf);
        i--;
    }

    /* Push new set of elements */
    circbuf_push(ring_buffer, "Hello again, Circ Buffer!", 26);

    /* Pop them in two parts */
    printf("Read:\n");
    circbuf_pop(ring_buffer, buf_arr, 13);
    /* Add \0 termination before printing */
    buf_arr[13] = '\0';
    printf("%s\n", buf_arr);
    /* Pop remaining */
    circbuf_pop(ring_buffer, buf_arr, 13);
    printf("%s", buf_arr);

    printf("\n===============\n");

    return 0;
}