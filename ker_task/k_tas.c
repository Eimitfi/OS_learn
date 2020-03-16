#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/sched.h>
#include <linux/kernel.h>

struct task_struct *task;

static int init_mod(void){
	printk(KERN_INFO "process name:    state:      id:");
	for_each_process(task){
		printk(KERN_INFO "%s   %ld   %d\n",task->comm,task->state,task->pid);
	}
	return 0;
}

static void exit_mod(void){
	printk(KERN_INFO "module removed succesfully\n");
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List current tasks");
MODULE_AUTHOR("licantropo");
