#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "FreeRTOS_CLI.h"
#include "hardware/watchdog.h"

void register_commands(void);
#endif