#include "commands.h"

// function prototypes for commands
static BaseType_t prvCmdPs(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

const CLI_Command_Definition_t xCmdPs = {
    "ps",
    "ps: prints formatted data of all tasks \r\n",
    prvCmdPs,
    0
};

static BaseType_t prvCmdPs(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *header = "Name          State   Priority  Stack  Num\r\n";
    strcpy(pcWriteBuffer, header);
    vTaskList(pcWriteBuffer + strlen(header));
    // return pdFalse to indicate completed execution
    return pdFALSE;
}

void register_commands() {
    FreeRTOS_CLIRegisterCommand(&xCmdPs);
}