obj-m += Bohemian_Rhapsody.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


old:
	make -C /lib/modules/6.8.3-200.fc39.x86_64/build M=$(PWD) modules