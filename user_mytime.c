#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<stdlib.h>
#include<fcntl.h>
#define N 3
int main()
{
struct timeval gtodTimes[N];
char procClockTimes[N][800];
int fd, bytes_read;
/* allocate memory for character buffers HERE before you use them */

fd = open("/dev/mytime", O_RDONLY);
/* check for errors HERE */
if(fd<0)
{
printf("failed to open the device");
return -1;
}


for(int i=0; i < N; i++)
{
	gettimeofday(&gtodTimes[i], 0);
	bytes_read = read(fd,procClockTimes[i], sizeof(procClockTimes));
	/* check for errors HERE */
	if (bytes_read<0)
{
	printf("failed to read from the device");
	return -1;
}

}

close(fd);

for(int i=0; i < N; i++) {
	printf("gettimeoftheday: \t%ld\t%ld\ncurrent_kernel_time: \t%s\n", gtodTimes[i].tv_sec, gtodTimes[i].tv_usec*1000,procClockTimes[i]);
	/* fix the output format appropriately in the above line */
}
}
