#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "FreeRTOS_CLI.h"

void register_commands(void);
#endif