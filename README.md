# freertos-shell-rp2350
This is a FreeRTOS shell built using FreeRTOS CLI.

The shell runs over the UART0 peripheral. This shell assumes that UART0RX is written to only by
the human terminal user. 

As for UART0TX, the shell task should be the only writer to this. In the near future,
this will be adjusted by making all tasks send data to some global queue, to which one 
output task will be the only task which should write to UART0TX. 

## How to Run
This guide assumes you are running linux. If you are running windows or mac, you may need to edit the "target remote localhost:3333" line in .gdbinit.

Run `sudo openocd` in one terminal

Run `gdb` in another terminal 

Exit gdb and run:

`picocom --omap crcrlf,delbs -b 115200 /dev/ttyACM0`


<img width="1504" height="1537" alt="image" src="https://github.com/user-attachments/assets/5ee7882f-25e9-40be-bbb9-22c6f85ee314" />
