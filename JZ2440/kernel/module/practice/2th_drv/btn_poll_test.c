#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc,char **argv)
{
	int fd;
	unsigned char key_vals[4];
	
	fd = open("/dev/btn_poll",O_RDWR);
	if(fd<0){
		printf("cant't open it\n");
		return -1;
	}

	while(1)
	{
		read(fd,key_vals,sizeof(key_vals));
		
		if(!key_vals[0] || !key_vals[1] || !key_vals[2] || !key_vals[3])
		{
			printf("key pressed: %d %d %d %d\n",key_vals[0],key_vals[1],key_vals[2],key_vals[3]);
		}
	}

	return 0;
}

