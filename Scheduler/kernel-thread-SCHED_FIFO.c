#include <linux/kernel.h>           //used for do_exit()
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/types.h>      // struct sched_param.sched_priority 
#include <linux/threads.h>          //used for allow_signal
#include <linux/kthread.h>          //used for kthread_create
#include <linux/delay.h>            //used for ssleep()

static struct task_struct *worker_task,*default_task;
static int get_current_cpu,set_current_cpu;
#define WORKER_THREAD_DELAY 4
#define DEFAULT_THREAD_DELAY 6


static int worker_task_handler_fn(void *arguments)
{
        allow_signal(SIGKILL);

        while(!kthread_should_stop()){
                printk("Worker thread executing on system CPU:%d \n",get_cpu());
                ssleep(WORKER_THREAD_DELAY);


                if (signal_pending(worker_task))
                    break;
        }

        do_exit(0);

        printk("Worker task exiting\n");
        return 0;
}

static int default_task_handler_fn(void *arguments)
{
        allow_signal(SIGKILL);

        while(!kthread_should_stop())
        {
            printk("Default thread executing on system CPU:%d \n",get_cpu());
                ssleep(DEFAULT_THREAD_DELAY);


            if (signal_pending(default_task))
                break;
        }

        printk("Default task exiting\n");

        do_exit(0);

        return 0;
}

static int __init kernel_thread_init(void)
{

        struct sched_param task_sched_params =
        {
                .sched_priority = MAX_RT_PRIO
        };

        task_sched_params.sched_priority = 90;

        printk("Initializing kernel mode thread example module\n");
        printk("Creating Threads\n");

        get_current_cpu = get_cpu();
        printk("Getting current CPU %d to binding worker thread\n",get_current_cpu);

        worker_task = kthread_create(worker_task_handler_fn,
                        (void*)"arguments as char pointer","thread_name");
        kthread_bind(worker_task,get_current_cpu);

        if(worker_task)
                printk("Worker task created successfully\n");
        else
                printk("Worker task error while creating\n");

        set_current_cpu = 2;
        printk("Getting current CPU %d to binding default thread\n",set_current_cpu);

        default_task = kthread_create(default_task_handler_fn,
                                (void*)"arguments as char pointer","thread_name");
        kthread_bind(default_task,set_current_cpu);

        // Assign a scheduler SCHED_FIFO = RT scheduler
        sched_setscheduler(default_task, SCHED_FIFO, &task_sched_params);

        wake_up_process(worker_task);
        wake_up_process(default_task);
        
        // There is another function that does both processes (create and start). That is kthread_run(). 
        // You can replace both kthread_create and wake_up_process using this function.

        if(worker_task)
             printk("Worker thread running\n");
        else
             printk("Worker task can't start\n");

        
        if(default_task)
            printk("Default thread running\n");
        else
            printk("Default task can't start\n");

        return 0;
}

static void __exit kernel_thread_exit(void)
{

        printk("Module removing from kernel, threads stopping\n");


        if(worker_task)
            kthread_stop(worker_task);

        printk("Worker task stopped\n");

        if(default_task)
            kthread_stop(default_task);

        printk("Default task stopped\n");

        printk("Bye Bye\n");

}

module_init(kernel_thread_init);
module_exit(kernel_thread_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raj Kumar Sanpui");
MODULE_DESCRIPTION("Kernel thread example");
MODULE_ALIAS("Threading");

