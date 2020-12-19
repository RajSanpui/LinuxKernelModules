#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>          // for_each_process(), task_lock(), task_unlock()
#include <linux/sched/signal.h>   // for_each_process(), task_lock(), task_unlock()

#define DRIVER_AUTHOR "Raj Kumar Sanpui"
#define DRIVER_DESC   "Current Process: Kernel module"


static int my_init_module(void)
{
   struct task_struct *parent, *grandParent, *siblingTask;
   struct list_head *list_head;

   printk(KERN_ALERT "Current Process check: Started\n");

   parent = current->parent;
   grandParent = current->parent->parent;

   printk("Current Process: %s, \t PID: %d, \t Process state: %ld\n", current->comm, current->pid, current->state);
   printk("Parent Process: %s, \t PID: %d, \t Process state: %ld\n", parent->comm, parent->pid, parent->state);
   printk("GrandParent Process: %s, \t PID: %d, \t Process state: %ld\n", grandParent->comm, grandParent->pid, grandParent->state);

   // list_for_each in a loop assigns each siblings from &grandParent->sibling to list_head
   list_for_each(list_head,&grandParent->sibling) {

       // list_entry returns the pointer to the structure "task_struct" that contains the member "sibling".
       siblingTask=list_entry(list_head,struct task_struct,sibling);
       printk("Sibling Process: %s, \t PID: %d, \t Process state: %ld\n", siblingTask->comm, siblingTask->pid, siblingTask->state);
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
