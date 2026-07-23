#include "commands.h"

// function prototypes for commands
static BaseType_t prvCmdPs(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCmdVersion(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCmdReboot(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

const CLI_Command_Definition_t xCmdPs = {
    "ps",
    "ps:\r\n Prints formatted data of all tasks\r\n\r\n",
    prvCmdPs,
    0
};

const CLI_Command_Definition_t xCmdVersion = {
    "version",
    "version:\r\n Prints version of project (not very useful rn)\r\n\r\n",
    prvCmdVersion,
    0
};

const CLI_Command_Definition_t xCmdReboot = {
    "reboot",
    "reboot:\r\n Resets RP2350 mcu\r\n\r\n",
    prvCmdReboot,
    0
};

static BaseType_t prvCmdPs(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *header = "Name          State   Priority  Stack  Num\r\n";
    strcpy(pcWriteBuffer, header);
    vTaskList(pcWriteBuffer + strlen(header));
    // return pdFalse to indicate completed execution
    return pdFALSE;
}

static BaseType_t prvCmdVersion(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *versionString = "v1.0.0\r\n";
    strcpy(pcWriteBuffer, versionString);
    // return pdFalse to indicate completed execution
    return pdFALSE;
}

static BaseType_t prvCmdReboot(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    // reboot after 100 milliseconds
    watchdog_reboot(0, 0, 100); 
    while (1) {
        tight_loop_contents();
    }
    return pdFALSE;
}

void register_commands() {
    FreeRTOS_CLIRegisterCommand(&xCmdPs);
    FreeRTOS_CLIRegisterCommand(&xCmdVersion);
    FreeRTOS_CLIRegisterCommand(&xCmdReboot);
}