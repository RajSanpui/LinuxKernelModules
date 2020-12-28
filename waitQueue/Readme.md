Whenever a process must wait for an event (such as the arrival of data or the termination of a process), it should go to sleep. 
Sleeping causes the process to suspend execution, freeing the processor for other uses. After some time, the process will be woken up and will continue with its job 
when the event which we are waiting for has arrived.

Wait queue is a mechanism provided in the kernel to implement the wait. As the name itself suggests, waitqueue is the list of processes waiting for an event.

Operation:
1. Definitions wait queue head
  ```
  wait_queue_head_t my_queue;
  ```


2. Initialize "wait queue head"
```init_waitqueue_head(&my_queue);```

3. Define the waiting queue
```DECLARE_WAITQUEUE(name, tsk)```

4. Add / Remove queue

```void add_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);
void add_wait_queue_exclusive(wait_queue_head_t *q, wait_queue_t *wait);
void remove_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);
```


5. Wait Event
```
wait_event(wq, condition)
wait_event_timeout(wq, condition, timeout)
wait_event_interruptible(wq, condition)
wait_event_interruptible_timeout(wq, condition, timeout)
```

6. Waking Up Queued Task
When some Tasks are in sleep mode because of waitqueue, then we can use the below function to wake up those tasks.
```
wake_up
wake_up_all
wake_up_interruptible
wake_up_sync and wake_up_interruptible_sync
```
