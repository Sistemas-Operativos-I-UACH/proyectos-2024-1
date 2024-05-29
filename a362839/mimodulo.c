#include <linux/init.h>
#include <linux/module.h>

static int __init mi_modulo_init(void) {
    printk(KERN_INFO "Hola, este es mi módulo de kernel\n");
    return 0;
}

static void __exit mi_modulo_exit(void) {
    printk(KERN_INFO "Saliendo del módulo de kernel\n");
}

module_init(mi_modulo_init);
module_exit(mi_modulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Un simple módulo de kernel");
