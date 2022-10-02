#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/sched.h>

static int __init solution_start(void)
{
	printk(KERN_INFO "Loading hello module...\n");
	printk(KERN_INFO "The process is \"%s\" (pid %i)\n",
			current->comm, current->pid);
	printk(KERN_INFO "Hello world\n");
	return 0;
}

static void __exit solution_end(void)
{
	printk(KERN_INFO "Goodbye.\n");
}

MODULE_AUTHOR("Anthony Emeltsev");
MODULE_LICENSE("GPL");
module_init(solution_start);
module_exit(solution_end);
