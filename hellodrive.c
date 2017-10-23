#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/errno.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/time.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/printk.h>


//#include <asm/uacess.h>
MODULE_LICENSE("GPL");


static int deviceNumber;
static int fileopened=0;
static struct miscdevice my_misc_device;
static struct file_operations fops;
static ssize_t read_mydevice(struct file *filenode1, char *buffer, size_t blength, loff_t *offset);
static int open_mydevice(struct inode *filenode, struct file *fileptr);
static int close_mydevice(struct inode *filenode, struct file *fileptr);

static struct miscdevice my_misc_device = {
.minor = MISC_DYNAMIC_MINOR,
.name = "mytime",
.fops = &fops
};

static struct file_operations fops = {
  .open = open_mydevice,
  .read = read_mydevice,
  .release = close_mydevice
};


static int __init my_module_init(void)
{

deviceNumber=misc_register(&my_misc_device);
printk("the device number is %d",deviceNumber);
if (deviceNumber < 0) 
	{
		printk("Driver registration failed");
		return deviceNumber;
	}
return 0;	
}

static void __exit my_exit(void)
{
misc_deregister(&my_misc_device); //unregister the device
}

static int open_mydevice(struct inode *filenode, struct file *fileptr)
{

fileopened++;

//if (open_device) return -EBUSY;

printk("Device Drive accessed: %d" , fileopened);
return 0;
}

static ssize_t read_mydevice(struct file *filenode1, char *buffer, size_t blength, loff_t *offset)
{

struct timespec t1, t2;
int err_read = 0;
t1=current_kernel_time();
getnstimeofday(&t2);
if (!access_ok(VERIFY_WRITE, buffer, sizeof(buffer)))
	{
	return -EFAULT;
	}
char buf[100];
sprintf(buf,"%ld %ld %ld %ld",t1.tv_sec , t1.tv_nsec, t2.tv_sec, t2.tv_nsec);
err_read = copy_to_user(buffer,buf,sizeof(buf)+1);
if(err_read==0)
	{
	printk("Time is Correct: %s", buf);
	return 0;
	}
else{
	printk("Time error");
	return -EFAULT;
	}
}
static int close_mydevice(struct inode *filenode, struct file *fileptr)
{

fileopened--;
printk("Device is now closed");
return 0;
}
module_init(my_module_init);
module_exit(my_exit);
