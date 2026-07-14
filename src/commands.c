#include "commands.h"

// function prototypes for commands
static BaseType_t prvCmdFrecho(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

const CLI_Command_Definition_t xCmdFrecho = {
    "frecho",
    "frecho: Echoes fred\r\n",
    prvCmdFrecho,
    0
};

static BaseType_t prvCmdFrecho(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    snprintf(pcWriteBuffer, xWriteBufferLen, "Fred\r\n");
    // return pdFalse to indicate completed execution
    return pdFALSE;
}

void register_commands() {
    FreeRTOS_CLIRegisterCommand(&xCmdFrecho);
}