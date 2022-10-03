#include <linux/module.h>       /* Needed by all modules */
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/sched.h>

/*
 * Global variables, define as static
 */
static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0; /* Ddevice numbers */
static struct cdev *my_cdev;

#define MYDEV_NAME "mychrdev"                 /* Name device, display in /proc/devices */
#define KBUF_SIZE (size_t)((10) * PAGE_SIZE)  /* Max buffer length */

/* 
 * Called when a process tries to open a device file, like so "cat /dev/chardev"
 */
static int mychrdev_open(struct inode *inode, struct file *file)
{
	static int counter = 0;

	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;

	printk(KERN_INFO "Opening device %s: \n\n", MYDEV_NAME);
	counter++;

	printk(KERN_INFO "counter: %d\n", counter);
	printk(KERN_INFO "module refcounter: %d\n", module_refcount(THIS_MODULE));

	return 0;
}

/*
 * Called when a process closes the device file
 */
static int mychrdev_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Releasing device %s: \n\n", MYDEV_NAME);

	char *kbuf = file->private_data;

	printk(KERN_INFO "Free buffer");
	if(kbuf){
		kfree(kbuf);
	}
	kbuf = NULL;
	file->private_data = NULL;

	return 0;
}

/* 
 * Called when a process tries to read an already open device file
 */
static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	char *kbuf = file->private_data;

	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;

	printk(KERN_INFO "Read device %s nbytes = %d, ppos = %d: \n\n", MYDEV_NAME, nbytes, (int)*ppos);

	return nbytes;
}

/*  
 * Called when a process tries to write to a device, like so: echo "hi" > /dev/chardev
 */
static ssize_t mychrdev_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	char *kbuf = file->private_data;

	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	*ppos += nbytes;

	printk(KERN_INFO "Write device %s nbytes = %d, ppos = %d\n\n", MYDEV_NAME, nbytes, (int)*ppos);

	return nbytes;
}
 /*
  * Filling file_operation structure
  */
static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.read = mychrdev_read,
	.write = mychrdev_write,
	.open = mychrdev_open,
	.release = mychrdev_release
};

static int __init solution_start(void)
{
	printk(KERN_INFO "Loading chrdev module...\n");
	printk(KERN_INFO "The process is \"%s\" (pid %i)\n",
			current->comm, current->pid);

	first = MKDEV(my_major, my_minor);
	register_chrdev_region(first, count, MYDEV_NAME);

	my_cdev = cdev_alloc();

	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev, first, count);

	return 0;
}

static void __exit solution_end(void)
{
	printk(KERN_INFO "Unloading module.\n");

	if(my_cdev){
		cdev_del(my_cdev);
	}
	unregister_chrdev_region(first, count);
}

MODULE_AUTHOR("Anthony Emeltsev");
MODULE_LICENSE("GPL");
module_init(solution_start);
module_exit(solution_end);
