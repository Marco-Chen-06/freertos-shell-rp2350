#include "commands.h"

// function prototypes for commands
static BaseType_t prvCmdPs(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCmdVersion(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCmdReboot(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCmdSetPriority(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

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

const CLI_Command_Definition_t xCmdSetPriority = {
    "setpriority",
    "setpriority:\r\n Sets priority of a task \r\n Usage: setpriority <task_name> <priority>\r\n\r\n",
    prvCmdSetPriority,
    2
};

static BaseType_t prvCmdPs(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *header = "Name          State   Priority  Stack  Num\r\n";
    strcpy(pcWriteBuffer, header);
    vTaskList(pcWriteBuffer + strlen(header));
    strcat(pcWriteBuffer, "\r\n");
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

static BaseType_t prvCmdSetPriority(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *pcTaskNameParameter, *pcPriorityParameter;
    BaseType_t xTaskNameLength;
    BaseType_t xPriorityLength;
    pcTaskNameParameter = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xTaskNameLength);
    pcPriorityParameter = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xPriorityLength);

    // get task handle from pcTaskNameParameter
    char taskNameBuf[configMAX_TASK_NAME_LEN]; 
    if (xTaskNameLength >= configMAX_TASK_NAME_LEN) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: task name not found. See task names with the \"ps\" command.\r\n\r\n");
        return pdFALSE;
    }
    memcpy(taskNameBuf, pcTaskNameParameter, xTaskNameLength);
    taskNameBuf[xTaskNameLength] = '\0';
    TaskHandle_t xTaskHandle = xTaskGetHandle(taskNameBuf);
    if (xTaskHandle == NULL) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: task name not found. See task names with the \"ps\" command.\r\n\r\n");
        return pdFALSE;
    }

    // get priority as a long from pcPriorityParameter
    char *endPtr;
    errno = 0;
    long priority = strtol(pcPriorityParameter, &endPtr, 10);
    if (errno == ERANGE) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: priority out of range. Please choose priority between 0 and %d.\r\n\r\n", configMAX_PRIORITIES - 1);
        return pdFALSE;
    }
    if (endPtr == pcPriorityParameter) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: entered priority not a number. Please make sure <priority> is a number.\r\n");
        return pdFALSE;
    }
    if ((priority < 0) || (priority > configMAX_PRIORITIES - 1)) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: priority out of range. Please choose priority between 0 and %d.\r\n\r\n", configMAX_PRIORITIES - 1);
        return pdFALSE;
    }

    vTaskPrioritySet(xTaskHandle, priority);
    snprintf(pcWriteBuffer, xWriteBufferLen, "Updated priority of %s to %d\r\n\r\n", taskNameBuf, priority);
    return pdFALSE;
}

void register_commands() {
    FreeRTOS_CLIRegisterCommand(&xCmdPs);
    FreeRTOS_CLIRegisterCommand(&xCmdVersion);
    FreeRTOS_CLIRegisterCommand(&xCmdReboot);
    FreeRTOS_CLIRegisterCommand(&xCmdSetPriority);
}