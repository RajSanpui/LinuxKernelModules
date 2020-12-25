
SCHED_FIFO and SCHED_RR belong to the real time scheduling algorithms "class". SCHED_OTHER is nothing but the scheduling algorithm for normal processes in the system, more popularly known as the CFS(Completely Fair Scheduler) algorithm.

SCHED_OTHER has a much lower priority

CFS (Complete fair scheduling) is the scheduling for non-realtime processes.
All schedule classes CFS, RT etc should be instance of sched_class.

(Ref: https://stackoverflow.com/questions/15670460/linux-cfs-volunteer-context-switches-sched-other-sched-fifo)


https://elixir.bootlin.com/linux/latest/source/kernel/sched/sched.h


	struct sched_class {
     			.
     			.
     			.
     			extern const struct sched_class stop_sched_class;
     			extern const struct sched_class dl_sched_class;
     			extern const struct sched_class rt_sched_class;
     			extern const struct sched_class fair_sched_class;
     			extern const struct sched_class idle_sched_class;

	}


Following Members for scheduling are part of 

	struct task_struct {
		sched_class
        	struct sched_info	sched_info;
  		int				prio;
		int				static_prio;
		int				normal_prio;
		unsigned int			rt_priority;
	}

To set the scheduler use the following:

   	struct sched_param param = { .sched_priority = prio };
   	sched_setscheduler(current, SCHED_OTHER, &param); // SCHED_OTHER is for CFS type
	
To attach scheduler to kernel threads use the following:

	default_task = kthread_create(default_task_handler_fn,
				(void*)"arguments as char pointer","thread_name"); // kthread_create returns task_struct
	kthread_bind(default_task,set_current_cpu);

	/*@brief set scheduler priority to default task
	*/
	sched_setscheduler(default_task, SCHED_FIFO, &task_sched_params); // Attach scheduler to kernel thread



https://stackoverflow.com/questions/15670460/linux-cfs-volunteer-context-switches-sched-other-sched-fifo?rq=1
https://stackoverflow.com/questions/27076350/what-does-sched-priority-in-struct-sched-param-refer-to
https://stackoverflow.com/questions/16042123/in-linux-kernel-is-the-following-way-right-to-create-a-real-time-kthread

Reference: https://embetronicx.com/tutorials/linux/device-drivers/linux-device-drivers-tutorial-kernel-thread/

Process Priority: 
The nice value of any normal process ranges between 19 (lowest priority) and -20 (highest priority), with 0 being the default value. A higher nice value indicates a lower priority (the process is being nicer to other processes). Real-time processes are prioritized between 0 and 99 (static priority). All these priority ranges are from the perspective of the user.


Kernel's perspective of priorities:
Linux however looks at process priorities from its own perspective. It adds a lot more computation for arriving at the priority of a process. Basically, it scales all priorities between 0 to 139, where 0 to 99 is assigned for real-time processes and 100 to 139 represents the nice value range (-20 to 19).

