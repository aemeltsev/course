#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/kobject.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/stat.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sysfs.h>

volatile int sol_var = 0;

/*
 * Global variables, define as static
 */
static dev_t dev = 0;
static struct class *sol_class;
static struct cdev sol_cdev;
struct kobject *kobj;

/* 
 * Function prototypes
 */
static int __init solution_start(void);
static void __exit solution_end(void);

/*
 * Driver functions
 */
static int solution_open(struct inode *inode, struct file *file);
static int solution_release(struct inode *inode, struct file *file);
static ssize_t solution_read(struct file *file,
                             char __user *buf, size_t lbuf, loff_t *ppos);
static ssize_t solution_write(struct file *file,
                              const char __user *buf, size_t lbuf, loff_t *ppos);

/*
 * Sysfs functions
 */
static ssize_t solution_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t solution_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);

struct kobj_attribute solution_attr = __ATTR(sol_var, S_IRUGO | S_IWUSR, solution_show, solution_store);

/*
 * File operation structure
 */
static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.read = solution_read,
	.write = solution_write,
	.open = solution_open,
	.release = solution_release
};

static ssize_t solution_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        pr_debug("sysfs - read!!!\n");
        return scnprintf(buf, PAGE_SIZE, "%d\n", sol_var);
}

static ssize_t solution_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
        pr_info("sysfs - write!!!\n");
        sscanf(buf, "%d", &sol_var);
        return count;
}

static int solution_open(struct inode *inode, struct file *file)
{
        pr_info("device file opened...!!!\n");
		return 0;
}

static int solution_release(struct inode *inode, struct file *file)
{
        pr_info("device file closed...!!!\n");
		return 0;
}

static ssize_t solution_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
        pr_info("read function\n");
		return 0;
}

static ssize_t solution_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
        pr_info("write function\n");
		return lbuf;
}

static int __init solution_start(void)
{
        if((alloc_chrdev_region(&dev, 0, 1, "sol_dev")) < 0)
        {
                pr_info("cannot allocate major number\n");
                return -1;
        }
        pr_info("major = %d minor = %d \n", MAJOR(dev), MINOR(dev));
        
        cdev_init(&sol_cdev, &mycdev_fops);
        
        if((cdev_add(&sol_cdev, dev, 1)) < 0)
        {
                pr_info("cannot add the device to the system\n");
                goto r_class;
        }
        
        if((sol_class = class_create(THIS_MODULE, "sol_class")) == NULL)
        {
                pr_info("cannot create the struct class\n");
                goto r_class;
        }
        
        if((device_create(sol_class, NULL, dev, NULL, "sol_device")) == NULL)
        {
                pr_info("cannot create the device 1\n");
                goto r_device;
        }
        
        kobj = kobject_create_and_add("sol_sysfs", kernel_kobj);
        
        if(sysfs_create_file(kobj, &solution_attr.attr))
        {
                pr_err("cannot create sysfs file......\n");
                goto r_sysfs;
        }
        
        pr_info("device driver insert...done!!!\n");        
	return 0;
	
	r_sysfs:
	        kobject_put(kobj);
	        sysfs_remove_file(kernel_kobj, &solution_attr.attr);
	
	r_device:
	        class_destroy(sol_class);
	
	r_class:
	        unregister_chrdev_region(dev, 1);
	        cdev_del(&sol_cdev);
	        return -1;
}

static void __exit solution_end(void)
{
        kobject_put(kobj);
        sysfs_remove_file(kernel_kobj, &solution_attr.attr);
        device_destroy(sol_class, dev);
        class_destroy(sol_class);
        cdev_del(&sol_cdev);
		unregister_chrdev_region(dev, 1);
		pr_info("device driver remove...done!!!\n");
}

module_init(solution_start);
module_exit(solution_end);

MODULE_AUTHOR("e4nt");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple linux device driver (sysfs)");

