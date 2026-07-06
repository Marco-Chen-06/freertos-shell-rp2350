#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

const uint LED_PIN = 25;

void vBlinkTask(void *pvParameters);
void vHelloTask(void *pvParameters);

int main() {
	stdio_init_all();

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	xTaskCreate(vBlinkTask, "vBlinkTask", 256, NULL, 1, NULL);
	xTaskCreate(vHelloTask, "vHelloTask", 512, NULL, 1, NULL);

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
	for (;;) {
		printf("hello world \r\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}