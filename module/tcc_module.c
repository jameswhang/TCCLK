#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/slab.h>
//#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>
#include <linux/cdev.h>

#include "../libtcc.h"
#include "tcc_memory.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Northwestern University");
MODULE_DESCRIPTION("TCC_Module");

static int Major;
dev_t dev_no,tcc_dev;
struct cdev *kernel_cdev;

struct device
{
	char *user_program;
	int prog_length;
	struct semaphore sem;
} tcc_char_dev;

int open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Inside open \n");
	if(down_interruptible(&tcc_char_dev.sem)) {
		printk(KERN_INFO "could not hold semaphore\n");
		return -1;
	}
	return 0;
}

int release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Inside close\n");
	printk(KERN_INFO "Releasing semaphore");
	up(&tcc_char_dev.sem);
	return 0;
}

ssize_t read (struct file *filp, char *buff, size_t count, loff_t *offp)
{
	unsigned long ret;
	printk(KERN_INFO "Inside read\n");
	ret = copy_to_user(buff, tcc_char_dev.user_program, count);
	return ret;
}

ssize_t write (struct file *filp, const char *buff, size_t count, loff_t *offp)
{
	unsigned long ret;
	printk(KERN_INFO "Inside write\n");

	int (*func)(); // main_func has to be in the form "int main()"

	TCCState *s;
	s = tcc_new();

	if (!s) {
		printk("Could not create tcc state\n");
		return 0;
	}

	tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

	printk("Starting tcc_compile_string\n");
	if (tcc_compile_string(s, buff) == -1) {
		printk("Could not compile program\n");
		return 0;
	}

	printk("Starting tcc_relocate!\n");
	if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0) {
		printk("Could not relocate program\n");
		return 0;
	}
	func = tcc_get_symbol(s, "main");
	if(!func) {
		printk("Could not find main...\n");
		return 0;
	}
	int result = func();
	printk("Result is %d\n", result);
	printk("**** TCC : FINISHED EXECUTING *****\n");

    	//tcc_delete(s); // TODO: Do this after memory allocator is implemented
	// Free user program
	return 0;
}

struct file_operations fops = 
{
	read: read,
	write: write,
	open: open,
	release: release
};


static int __init tcc_module_init(void)
{
    int ret;
    printk(KERN_INFO "TCC Module Inited\n");

    //compilation test complete
    //initialize device now
    kernel_cdev = cdev_alloc();
    kernel_cdev->ops = &fops;
    kernel_cdev->owner = THIS_MODULE;
    ret = alloc_chrdev_region( &dev_no, 0, 1, "chr_arr_dev");
    if (ret < 0) {
	printk("Major number allocation is failed\n");
	return ret;
    }

    Major = MAJOR(dev_no);
    tcc_dev = MKDEV(Major,0);
    sema_init(&tcc_char_dev.sem, 1);
    printk("The major number for your device is %d\n", Major);
    ret = cdev_add(kernel_cdev,tcc_dev,1);
    if (ret < 0) {
	printk ("Unable to allocate cdev\n");
	return ret;
    }
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit tcc_module_deinit(void)
{
    printk(KERN_INFO "TCC Module Deinited\n");
    cdev_del(kernel_cdev);
    unregister_chrdev_region(Major,1);
}

module_init(tcc_module_init);
module_exit(tcc_module_deinit);
