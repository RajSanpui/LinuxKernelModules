#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "Raj Kumar Sanpui"
#define DRIVER_DESC   "Hello World Kernel module"


static int init_hello(void)
{
   printk(KERN_ALERT "Hello World\n");
   return 0;
}


static void cleanup_hello(void)
{
   printk(KERN_ALERT "Goodbye World\n");
}


module_init(init_hello);
module_exit(cleanup_hello);


MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("Mydevice");
