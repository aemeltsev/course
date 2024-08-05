#include <linux/module.h>       /* Needed by all modules */
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>

static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0;
static struct cdev *my_cdev;

#define MYDEV_NAME "mychrdev"
#define KBUF_SIZE (size_t)((10) * PAGE_SIZE)

static struct class* class_dev;

static int mychrdev_open(struct inode *inode, struct file *file)
{
	static int counter = 0;

	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;

	pr_info("Opening device %s: \n\n", MYDEV_NAME);
	counter++;

	pr_info("counter: %d\n", counter);
	pr_info("module refcounter: %d\n", module_refcount(THIS_MODULE));

	return 0;
}

static int mychrdev_release(struct inode *inode, struct file *file)
{
	pr_info("releasing device %s: \n\n", MYDEV_NAME);

	char *kbuf = file->private_data;

	if(kbuf){
		kfree(kbuf);
	}
	kbuf = NULL;
	file->private_data = NULL;
	
	pr_info("free buffer");
	return 0;
}

static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	char *kbuf = file->private_data;

	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;

	pr_info("read device %s nbytes = %d, ppos = %d: \n\n", MYDEV_NAME, nbytes, (int)*ppos);

	return nbytes;
}

static ssize_t mychrdev_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	char *kbuf = file->private_data;

	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	*ppos += nbytes;

	pr_info("write device %s nbytes = %d, ppos = %d\n\n", MYDEV_NAME, nbytes, (int)*ppos);

	return nbytes;
}

static loff_t mychrdev_llseek(struct file *file, loff_t offset, int orig)
{
	loff_t pos;
	
	switch(orig)
	{
		case SEEK_SET:
		  pos = offset;
		  break;
		case SEEK_CUR:
		  pos = file->f_pos + offset;
		  break;
		case SEEK_END:
		  pos = KBUF_SIZE + offset;
		  break;
		default:
		  return -EINVAL;
	}
	
	pos = (pos < KBUF_SIZE) ? pos : KBUF_SIZE;
	pos = (pos >= 0) ? pos : 0;
	file->f_pos = pos;
	
	pr_info("seeking to %ld position\n", (long)pos);
	
	return pos;	
}

static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.read = mychrdev_read,
	.write = mychrdev_write,
	.open = mychrdev_open,
	.release = mychrdev_release,
	.llseek = mychrdev_llseek
};

static int __init solution_start(void)
{
	pr_info("loading solution module...\n");
	pr_info("the process is \"%s\" (pid %i)\n",
			current->comm, current->pid);

	first = MKDEV(my_major, my_minor);
	register_chrdev_region(first, count, MYDEV_NAME);

	my_cdev = cdev_alloc();

	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev, first, count);
	
	class_dev = class_create(THIS_MODULE, "chdev"); // create class_dev class
	if(IS_ERR(class_dev))
	{
		return PTR_ERR(class_dev);
	}
	
	device_create(class_dev, NULL, first, NULL, "%s", "chdev");
	pr_info("created device class %s", MYDEV_NAME);
	
	return 0;
}

static void __exit solution_end(void)
{
	pr_info("goodbye mr.\n");

	if(my_cdev){
		cdev_del(my_cdev);
	}
	
	device_destroy(class_dev, first);
	class_destroy(class_dev);
	
	unregister_chrdev_region(first, count);
}

MODULE_AUTHOR("e4nt");
MODULE_LICENSE("GPL");
module_init(solution_start);
module_exit(solution_end);
