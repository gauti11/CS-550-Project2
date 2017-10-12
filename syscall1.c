#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include<linux/time.h>


int main()
{
	struct timespec time;
	
         long int amma = syscall(326,&time);
         printf("the sys call is %ld\n",amma);
	 printf("seconds %ld nanoseconds %ld \n",time.tv_sec,time.tv_nsec);	

 return 0;
}
