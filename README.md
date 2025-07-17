### 🌀 UART-Style Circular Buffer in C

This project implements a **fixed-size circular buffer (ring buffer)** in C, commonly used in embedded systems for UART data reception. It supports:

* Efficient FIFO storage with constant-time insert/read
* Overwrite-on-full behavior (oldest data is discarded)
* Modular design with `init`, `write`, `read`, and status-check functions

The `uart_receive_ISR()` simulates how incoming bytes from a UART ISR are stored in the buffer, while `read_buffer()` reads data sequentially in FIFO order.

This is ideal for learning how real-time embedded drivers handle asynchronous data safely and efficiently.
