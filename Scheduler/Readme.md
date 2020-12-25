
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


Following Members for scheduling are part of task_struct.
  - sched_class
  - struct sched_info	sched_info;
  - int				prio;
	int				static_prio;
	int				normal_prio;
	unsigned int			rt_priority;


To set the scheduler use the following:
   struct sched_param param = { .sched_priority = prio };
   sched_setscheduler(current, SCHED_FIFO, &param);



https://stackoverflow.com/questions/15670460/linux-cfs-volunteer-context-switches-sched-other-sched-fifo?rq=1
https://stackoverflow.com/questions/27076350/what-does-sched-priority-in-struct-sched-param-refer-to
https://stackoverflow.com/questions/16042123/in-linux-kernel-is-the-following-way-right-to-create-a-real-time-kthread

