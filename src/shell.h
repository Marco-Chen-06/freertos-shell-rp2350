#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define SHELL_INPUT_BUF_LEN 64
#define SHELL_RECV_QUEUE_LEN 32

void shell_init();
void shell_execute();
#endif