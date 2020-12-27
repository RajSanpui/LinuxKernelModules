#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>          // for_each_process(), task_lock(), task_unlock()
#include <linux/sched/signal.h>   // for_each_process(), task_lock(), task_unlock()
#include <linux/sched/types.h>
#include <linux/kthread.h>
#include <linux/delay.h>            //used for ssleep()

#define DRIVER_AUTHOR "Raj Kumar Sanpui"
#define DRIVER_DESC   "Process check: Kernel module"

static int kthread_func(void *arg)
{

/* Every kthread has a struct task_struct associated with it.
*  Whenever a thread is schedule for execution, the kernel sets "current" pointer to
*    it's struct task_struct.
*  current->comm is the name of the command that caused creation of this thread
*  current->pid is the process of currently executing thread
*/

    while(!kthread_should_stop()){
       ssleep(5);

       printk(KERN_INFO "I am thread: %s[PID = %d]\n", current->comm, current->pid);
    }
    return 0;
}

static int my_init_module(void)
{
   struct task_struct *tid1, *tid2;
   int err;
   printk(KERN_ALERT "Thread creation: Started\n");

   tid1 = kthread_run(kthread_func, NULL, "thread-1");
    if (IS_ERR(tid1)) {
        printk(KERN_INFO "ERROR: Cannot create thread thread-1\n");
        err = PTR_ERR(tid1);
        tid1 = NULL;
        return err;
    }

    tid2 = kthread_run(kthread_func, NULL, "thread-2");
    if (IS_ERR(tid2)) {
        printk(KERN_INFO "ERROR: Cannot create thread thread-2\n");
        err = PTR_ERR(tid2);
        tid2 = NULL;
        return err;
    }

    struct sched_param task_sched_params =
    {
                .sched_priority = MAX_RT_PRIO
    };
    task_sched_params.sched_priority = 90;
    sched_setscheduler(tid1, SCHED_FIFO, &task_sched_params);

    printk(KERN_INFO "I am thread: %s[PID = %d]\n", current->comm, current->pid);
    return 0;

   return 0;
}

{
   printk(KERN_ALERT "Thread creation program: Exiting.\n");
}


module_init(my_init_module);
module_exit(my_cleanup_module);


MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("testdevice");

// Tested with Ubuntu Kernel 5.3.0-28-generic
                                                  
