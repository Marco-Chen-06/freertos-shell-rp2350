/*
 * shell.h
 * Handles the creation of a FreeRTOS shell task
*/

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "FreeRTOS_CLI.h"
#include "commands.h"

#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"

// uart peripheral to use
#define UART_PERI uart0
#define UART_IRQ UART0_IRQ
#define UART_BAUDRATE 115200

#define SHELL_INPUT_BUF_LEN 64 // max input length
#define SHELL_RECV_QUEUE_LEN 256 // max output length

void uart_rx_handler();

void shell_init();
void shell_execute();
#endif