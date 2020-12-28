#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/wait.h>
 
#define ENTER() printk(KERN_DEBUG "%s() Enter", __func__)
#define EXIT() printk(KERN_DEBUG "%s() Exit", __func__)
#define ERR(fmt, args...) printk(KERN_ERR "%s()-%d: " fmt "\n", __func__, __LINE__, ##args)
#define DBG(fmt, args...) printk(KERN_DEBUG "%s()-%d: " fmt "\n", __func__, __LINE__, ##args)
 
MODULE_LICENSE("GPL");
 
 
struct work {
    char name[64];
    void (*work_func)(void *data);
    void *data;
};
 
static void do_work(void *data)
{
    int num = (int)data;
    DBG("work num is %d", num);
    msleep_interruptible(1000);
}
 
static struct task_struct *producer = NULL;
static struct task_struct *consumer = NULL;
static wait_queue_head_t prod_wq;
static wait_queue_head_t cons_wq;
 
static struct work *work = NULL;
 
static int producer_thr(void *arg)
{
    int num = 0;
    ENTER();
    while (!kthread_should_stop()) {
        int ret = wait_event_interruptible(prod_wq, (work == NULL));
        if (ret == -ERESTARTSYS) {
            DBG("wake up by signal");
            continue;
        }
 
        // DBG("ret = %d", ret);
        work = kzalloc(sizeof(struct work), GFP_KERNEL);
        if (!work) {
            ERR("kzalloc fail");
            break;
        }
        num++;
        snprintf(work->name, sizeof(work->name), "debug-work");
        work->work_func = do_work;
        work->data = (void *)num;
       
        wake_up_interruptible(&cons_wq);
    }
 
    EXIT();
    return 0;
}
 
static int consumer_thr(void *arg)
{
    ENTER();
    wake_up_interruptible(&prod_wq);
   
    while (!kthread_should_stop()) {
        int ret = wait_event_interruptible(cons_wq, (work != NULL));
        if (ret == -ERESTARTSYS) {
            DBG("wait_up by signal");
            continue;
        }
        // DBG("ret = %d", ret);
        DBG("excute work: %s", work->name);
        work->work_func(work->data);
        kfree(work);
        work = NULL;
        wake_up_interruptible(&prod_wq);
    }
 
    EXIT();
    return 0;
}
 
 
static __init int wq_demo_init(void)
{
    ENTER();
    init_waitqueue_head(&prod_wq);
    init_waitqueue_head(&cons_wq);
 
    producer = kthread_run(producer_thr, NULL, "producer-thr");
    if (!producer) {
        ERR("kthread_run fail");
        goto _fail;
    }
 
    consumer = kthread_run(consumer_thr, NULL, "consumer-thr");
    if (!consumer) {
        ERR("kthread_run fail");
        goto _fail;
    }
 
    EXIT();
    return 0;
 
_fail:
    if (producer)
        kthread_stop(producer);
    if (consumer)
        kthread_stop(consumer);
    return -ECHILD;
}
 
static __exit void wq_demo_exit(void)
{
    ENTER();
    if (producer)
        kthread_stop(producer);
    if (consumer)
        kthread_stop(consumer);
   
    EXIT();
}
 
module_init(wq_demo_init);
module_exit(wq_demo_exit);
