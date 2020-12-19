#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>          // for_each_process(), task_lock(), task_unlock()
#include <linux/sched/signal.h>   // for_each_process(), task_lock(), task_unlock()

#define DRIVER_AUTHOR "Raj Kumar Sanpui"
#define DRIVER_DESC   "Process List: Kernel module"


static int my_init_module(void)
{
   printk(KERN_ALERT "Process check: Started\n");
   struct task_struct *task;

   for_each_process(task)
   {
     printk("Process Name: %s, \t PID: %d, \t Process state: %ld\n", task->comm, task->pid, task->state);
     // // The details of the different task structure  and its variables like state etc can be seen from header: linux/sched.h
   }
   return 0;
}


static void my_cleanup_module(void)
{
   printk(KERN_ALERT "Proces check: Exiting.\n");
}


module_init(my_init_module);
module_exit(my_cleanup_module);


MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("testdevice");

// Tested with Ubuntu Kernel 5.3.0-28-generic
