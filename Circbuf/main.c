#include "circbuf.h"

#include <stdio.h>

int main(void) {
    int i;
    char buf;
    char buf_arr[50];

    /* Create and initialize circular buffer */
    circbuf *ring_buffer = circbuf_init(20);


    /* Push multiple elements to buffer at once */
    circbuf_push(ring_buffer, "Hello, Circ Buffer!", 19);


    /* Push new set of elements */
    circbuf_push(ring_buffer, "12345", 6);

    /* Pop them in two parts */
    printf("Read:\n");
    circbuf_pop(ring_buffer, buf_arr, 20);
    /* Add \0 termination before printing */
    buf_arr[21] = '\0';
    printf("%s\n", buf_arr);

    printf("\n===============\n");

    return 0;
}