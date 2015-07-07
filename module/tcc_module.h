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

int open(struct inode *inode, struct file *flip);
int release(struct inode *inode, struct file *flip);
ssize_t read(struct file *flip, char *buff, size_t count, loff_t *offp);
ssize_t write(struct file *flip, const char *buff, size_t count, loff_t *offp);
