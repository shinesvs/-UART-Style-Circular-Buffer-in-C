#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 10

typedef struct {
    int data[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

CircularBuffer uart_rx_instance;          // Static instance
CircularBuffer* uart_rx = &uart_rx_instance;  // Pointer to it

void init_buffer() {
    uart_rx->head = 0;
    uart_rx->tail = 0;
    uart_rx->count = 0;
}

bool is_full() {
    return uart_rx->count == BUFFER_SIZE;
}

bool is_empty() {
    return uart_rx->count == 0;
}

void uart_receive_ISR(int data) {
    if (is_full()) {
        uart_rx->tail = (uart_rx->tail + 1) % BUFFER_SIZE; // overwrite oldest
        uart_rx->count--;
    }

    uart_rx->data[uart_rx->head] = data;
    uart_rx->head = (uart_rx->head + 1) % BUFFER_SIZE;
    uart_rx->count++;
}

int read_buffer() {
    if (is_empty()) {
        printf("Buffer is Empty\n");
        return -1;
    }

    int val = uart_rx->data[uart_rx->tail];
    uart_rx->tail = (uart_rx->tail + 1) % BUFFER_SIZE;
    uart_rx->count--;
    return val;
}

int main() {
    init_buffer();

    // Simulate UART receiving 12 values
    for (int i = 0; i < 12; i++) {
        uart_receive_ISR(i + 100);
    }

    // Read all available values
    while (!is_empty()) {
        int val = read_buffer();
        printf("Read: %d\n", val);
    }

    return 0;
}
