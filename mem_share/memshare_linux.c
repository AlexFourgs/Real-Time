#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

static int end;
static void endme (){
	end = 1;
}


int main(){
	ArrayShared *my_array ;

	 
	if ((fifo = open("/dev/rtf0",O_RDONLY))< 0) {
		fprintf(stderr,"error opening /dev/rtf0\n");
		exit(1);
	}

	printf("fifo ouverte\n");

	signal(SIGINT, endme);

	while (!end) {
		printf("lecture...counter\n");
		read(fifo,&l_counter,sizeof(l_counter));
		printf("lecture...value\n");
		read(fifo,&l_value,sizeof(l_value));!
		fprintf(stderr,"=> %i %d \n",l_counter,l_value);
	}

	return 0 ;
}

