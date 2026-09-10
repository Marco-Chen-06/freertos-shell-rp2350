file build/shell.elf

set architecture arm
target remote localhost:3333
mon reset halt
load
break main
continue
tui enable

define flash
mon reset halt
mon resume
detach
quit

