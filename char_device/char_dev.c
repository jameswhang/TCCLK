#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // required for various structures related to files liked fops.
#include <asm/uaccess.h> // required for copy_from and copy_to user functions
#include <linux/semaphore.h>
#include <linux/cdev.h>
static int Major;
dev_t dev_no,dev;
struct device
{
	char array[100];
	struct semaphore sem;
}char_dev;

int open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Inside open \n");
	if(down_interruptible(&char_dev.sem)) {
		printk(KERN_INFO " could not hold semaphore");
		return -1;
	}
	return 0;
}

int release(struct inode *inode, struct file *filp)
{
	printk (KERN_INFO "Inside close \n");
	printk(KERN_INFO "Releasing semaphore");
	up(&char_dev.sem);
	return 0;
}

ssize_t read(struct file *filp, char *buff, size_t count, loff_t *offp) 
{
	unsigned long ret;
	printk("Inside read \n");
	ret = copy_to_user(buff, char_dev.array, count);
	return ret;
}

ssize_t write(struct file *filp, const char *buff, size_t count, loff_t *offp) 
{
	unsigned long ret;
	printk(KERN_INFO "Inside write \n");
	ret = copy_from_user(char_dev.array, buff, count);
	return count;
}

struct file_operations fops = {
read:  read,
       write:  write,
       open:   open,
       release: release
};

struct cdev *kernel_cdev;

int char_dev_init (void) 
{
	int ret;
	kernel_cdev = cdev_alloc();
	kernel_cdev->ops = &fops;
	kernel_cdev->owner = THIS_MODULE;
	printk (" Inside init module\n");
	ret = alloc_chrdev_region( &dev_no , 0, 1,"chr_arr_dev");
	if (ret < 0) {
		printk("Major number allocation is failed\n");
		return ret;
	}

	Major = MAJOR(dev_no);
	dev = MKDEV(Major,0);
	sema_init(&char_dev.sem,1);
	printk (" The major number for your device is %d\n", Major);
	ret = cdev_add( kernel_cdev,dev,1);
	if(ret < 0 )
	{
		printk(KERN_INFO "Unable to allocate cdev");
		return ret;
	}
	return 0;
}

void char_dev_cleanup(void) 
{
	printk(KERN_INFO " Inside cleanup_module\n");
	cdev_del(kernel_cdev);
	unregister_chrdev_region(Major, 1);
}

MODULE_LICENSE("GPL");
module_init(char_dev_init);
module_exit(char_dev_cleanup);
