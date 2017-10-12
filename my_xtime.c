#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/time.h>
#include <linux/syscalls.h>
#include <linux/printk.h>

asmlinkage long sys_my_xtime(struct timespec  *current_time)
{
  struct timespec tspec = current_kernel_time();

  if(!access_ok(VERIFY_WRITE, current_time, sizeof(struct timespec))) {
    return -EFAULT;
  }


  current_time->tv_sec = (tspec.tv_sec);
  current_time->tv_nsec =((tspec.tv_sec)*1000000000+(tspec.tv_nsec));

        printk(KERN_INFO "current time in nanoseconds: %ld", current_time->tv_nsec);
	printk(KERN_INFO "current time in seconds: %ld", current_time->tv_sec);	
 return 0;
}   
