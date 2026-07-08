#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "shell.h"

const uint LED_PIN = 25;

void vBlinkTask(void *pvParameters);
void vHelloTask(void *pvParameters);
void vShellTask(void *pvParameters);

int main() {
	stdio_init_all();

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	xTaskCreate(vBlinkTask, "vBlinkTask", 256, NULL, 1, NULL);
	xTaskCreate(vHelloTask, "vHelloTask", 512, NULL, 1, NULL);
	xTaskCreate(vShellTask, "vShellTask", 512, NULL, 1, NULL);

	vTaskStartScheduler();

	// code shouldn't reach here
	while(1) {
		;
	}
}

void vBlinkTask(void *pvParameters) {
	for (;;) {
		gpio_put(LED_PIN, 1);
		vTaskDelay(pdMS_TO_TICKS(250));
		gpio_put(LED_PIN, 0);
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

void vHelloTask(void *pvParameters) {
	// task that does nothing useful
	volatile int num = 0;
	for (;;) {
		for (int i = 0; i < 12312; i++) {
			num += i;
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void vShellTask(void *pvParameters) {
	shell_init();

	shell_execute();
	
	// shell_execute contains a infinite loop so we shouldn't reach here
	for (;;) {
		// idk :0
	}
}