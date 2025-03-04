#ifndef UART_H
#define UART_H

// Base addr
#define SC1F_UART0_PORT 0xff010000

#define UART_115200_CLK_DIVISOR (25000000 / 115200 + 7) / 16

// UART regs
#define SC1F_UART_RXD       (0x00) // receive data
#define SC1F_UART_TXD       (0x00) // transmit data
#define SC1F_UART_IER       (0x04) // interrupt enable register
#define SC1F_UART_FCR       (0x08) // FIFO control register
#define SC1F_UART_CONTROL   (0x0c) // line control register
#define SC1F_UART_MCR       (0x10) // modem control register
#define SC1F_UART_STATUS    (0x14) // status register
#define SC1F_UART_DIV_LO    (0x00) // baud rate divisor register, low
#define SC1F_UART_DIV_HI    (0x04) // baud rate divisor register, low

// UART FIFO control register bits
#define SC1F_UART_FCR_RT_1  (0 << 6) // RX FIFO trigger level: 1 byte
#define SC1F_UART_FCR_RT_4  (1 << 6) // RX FIFO trigger level: 4 bytes
#define SC1F_UART_FCR_RT_8  (2 << 6) // RX FIFO trigger level: 8 bytes
#define SC1F_UART_FCR_RT_14 (3 << 6) // RX FIFO trigger level: 14 bytes
#define SC1F_UART_FCR_RMASK (3 << 6) // RX FIFO trigger level mask bits
#define SC1F_UART_FCR_T_RST (1 << 2) // reset TX FIFO
#define SC1F_UART_FCR_R_RST (1 << 1) // reset RX FIFO
#define SC1F_UART_FCR_EN    (1 << 0) // FIFO enable

// UART status register bits
#define SC1F_UART_ST_TEMPTY (1 << 6) // tx empty
#define SC1F_UART_ST_TRDY   (1 << 5) // tx not full
#define SC1F_UART_ST_RRDY   (1 << 0) // rx not empty

// UART line control register bits
#define SC1F_UART_LCR_DIVL  (1 << 7) // divisor latch access
#define SC1F_UART_LCR_SP    (1 << 5) // sticky parity
#define SC1F_UART_LCR_EPS   (1 << 4) // even parity select
#define SC1F_UART_LCR_PE    (1 << 3) // parity enable
#define SC1F_UART_LCR_SBN   (1 << 2) // number of stop bits (0 - 1, 1 - 1.5/2)
#define SC1F_UART_LCR_CL8   (3 << 0) // character length: 8
#define SC1F_UART_LCR_CL7   (2 << 0) // character length: 7
#define SC1F_UART_LCR_CL6   (1 << 0) // character length: 6
#define SC1F_UART_LCR_CL5   (0 << 0) // character length: 5

#endif