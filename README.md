# freertos-shell-rp2350
This is a FreeRTOS shell built using FreeRTOS CLI.

The shell runs over the UART0 peripheral. This shell assumes that UART0RX is written to only by
the human terminal user. 

As for UART0TX, the shell task should be the only writer to this. In the near future,
this will be adjusted by making all tasks send data to some global queue, to which one 
output task will be the only task which should write to UART0TX. 

picocom formatting:

picocom --omap crcrlf,delbs -b 115200 /dev/ttyACM0
