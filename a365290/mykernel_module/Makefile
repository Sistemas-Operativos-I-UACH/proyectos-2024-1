obj-m += whisper.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


old:
	make -C /lib/modules/6.1.13-200.fc37.x86_64/build M=$(PWD) modules
