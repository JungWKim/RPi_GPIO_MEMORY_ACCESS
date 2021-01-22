#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("webnautes");
MODULE_DESCRIPTION("helloworld module");
MODULE_INTO(intree, "Y");

int mod_init(void)
{
    printk(KERN_INFO "[helloworld module] Hello World\n");
    printk(KERN_INFO "[helloworld module] Load a module\n");
    return 0;
}

void mod_exit(void)
{
    printk(KERN_INFO "[helloworld module] Goodbye\n");
    printk(KERN_INFO "[helloworld module] Unload a module\n");
}

module_init(mod_init);
module_exit(mod_exit);
