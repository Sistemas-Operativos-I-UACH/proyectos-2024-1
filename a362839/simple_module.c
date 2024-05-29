// simple_module.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Un módulo simple de ejemplo");
MODULE_VERSION("0.1");

// Función que se llama cuando el módulo se carga
static int __init simple_module_init(void) {
    printk(KERN_INFO "Simple Module: ¡Hola, Mundo!\n");
    return 0; // Retorna 0 para indicar una carga exitosa
}

// Función que se llama cuando el módulo se descarga
static void __exit simple_module_exit(void) {
    printk(KERN_INFO "Simple Module: Adiós, Mundo\n");
}

// Registrar las funciones de carga y descarga
module_init(simple_module_init);
module_exit(simple_module_exit);
