#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
 
/* Below are attributes variables */
static int attr_fr; /* read and write attribute */
static int attr_sec; /* read only attribute */
 
/*
 * This function are use for reading the attributes
 */
static ssize_t attr_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int var;
 
    if (strcmp(attr->attr.name, "attr_fr") == 0)
        var = attr_fr;
    else
        var = attr_sec;
    return sprintf(buf, "%d\n", var);
}
 
 
/*
 * This function are use for writing the attributes
 */
static ssize_t attr_store(struct kobject *kobj, struct kobj_attribute *attr, 
                          const char *buf, size_t count)
{
    int var, ret;
 
    ret = kstrtoint(buf, 10, &var);
    if (ret < 0)
        return ret;
 
    if (strcmp(attr->attr.name, "attr_fr") == 0)
        attr_fr = var;
    else
        attr_sec = var;
    return count;
}
 
static struct kobj_attribute attr_fr_attribute = __ATTR(attr_fr, S_IRUGO | S_IWUSR, attr_show, attr_store);
static struct kobj_attribute attr_sec_attribute = __ATTR(attr_sec, S_IRUGO, attr_show, attr_store);
 
/*
 * Create attributes group
 */
static struct attribute *attrs[] = {
    &attr_fr_attribute.attr,
    &attr_sec_attribute.attr,
    NULL,   
    /* need to NULL terminate the list of attributes */
};
 
 
static struct attribute_group attr_group = {
    .attrs = attrs,
};
 
static struct kobject *sol_kobj = NULL;
 
static int __init sol_init(void)
{
    int retval = 0;
 
    /*
     * Create a simple kobject and create directory located under /sys/kernel/
     */
    sol_kobj = kobject_create_and_add("solution_module", kernel_kobj);
    if(!sol_kobj)
    {
          return -ENOMEM;
    }
 
    /* 
     * Create the files associated with this kobject under directory /sys/kernel/solution_module 
     */
    retval = sysfs_create_group(sol_kobj, &attr_group);
    if(retval)
    {
          kobject_put(sol_kobj);
    }
 
    pr_info("device driver insert...done!!!\n");
 
    return retval;
}
 
static void __exit sol_exit(void)
{
    kobject_put(sol_kobj);
    pr_info("device driver remove...done!!!\n");
}
 
module_init(sol_init);
module_exit(sol_exit);
 
MODULE_AUTHOR("Anthony Emeltsev");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("kobject and sysfs example device driver");
