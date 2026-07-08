#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"

// uart peripheral to use
#define UART_PERI uart0
#define UART_IRQ UART0_IRQ
#define UART_BAUDRATE 115200

#define SHELL_INPUT_BUF_LEN 64
#define SHELL_RECV_QUEUE_LEN 32

void uart_rx_handler();

void shell_init();
void shell_execute();
#endif