#include "shell.h"

QueueHandle_t xRecvQueue;
static uint8_t inputBuf[SHELL_INPUT_BUF_LEN];
static uint8_t *inputBufPtr;
static uint8_t outputBuf[configCOMMAND_INT_MAX_OUTPUT_SIZE];

void uart_rx_handler() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    while (uart_is_readable(UART_PERI)) {
        uint8_t ch = uart_getc(UART_PERI);
        xQueueSendFromISR(xRecvQueue, &ch, &xHigherPriorityTaskWoken);
    }
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void shell_init() {
    uart_init(UART_PERI, UART_BAUDRATE);

    // set GPIO0 and GPIO1 to UART TX and RX respectively
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    irq_set_exclusive_handler(UART_IRQ, uart_rx_handler);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_PERI, true, false); // UARTRXINT on, UARTRXINT off


    inputBufPtr = inputBuf;
    xRecvQueue = xQueueCreate(SHELL_RECV_QUEUE_LEN, sizeof(uint8_t));
    configASSERT(xRecvQueue);

    printf("welcome to rp2350 freertos shell \r\n");
}

void shell_execute() {
    // will probably register commands here

    // end of where i will probably register commands here

    for (;;) {
        char ch = 0;
        xQueueReceive(xRecvQueue, &ch, portMAX_DELAY);
        printf("received %c\r\n", ch);
    }
}