#include "shell.h"

QueueHandle_t xRecvQueue;
static uint8_t inputBuf[SHELL_INPUT_BUF_LEN];
static uint8_t *inputBufPtr;
static uint8_t outputBuf[configCOMMAND_INT_MAX_OUTPUT_SIZE];

void shell_init() {
    inputBufPtr = inputBuf;
    xRecvQueue = xQueueCreate(SHELL_RECV_QUEUE_LEN, sizeof(uint8_t));
    configASSERT(xRecvQueue);

    printf("welcome to rp2350 freertos shell \r\n");
}

void shell_execute() {
    // will probably register commands here

    // end of where i will probably register commands here

    for (;;) {
        
    }
}