obj-m += mi_modulo.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
all: 
	gcc helloworld.c o- helloworld

clean:
	rm helloworld
