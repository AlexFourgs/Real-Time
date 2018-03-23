#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>
#include <math.h>
#include <rtai.h>
#include <rtai_sched.h>
#include "rtai_shm.h"

#include "struct_array.h"

#define TICK_PERIOD 1000000
#define TASK_PRIO 1
#define STACK_SIZE 10000

static RT_TASK writetab;
static RT_TASK heartbeat;

ArrayShared *shared_memory ;
volatile int heartbeat_value = 0 ;


/*
 *	TASK FOR WRITE IN THE TAB
 */
static void write(int t){
	int i = 0 ;	
	int heartbeat = 0 ;
	
	printk("write in shared memory\n");
	
	while (1) {
		for(i = 0 ; i < SIZE_ARRAY ; i++){
			shared_memory->array[i] = heartbeat ;	
		}
		heartbeat++ ;
		rt_task_wait_period();
	}
}

/*
 *	TASK FOR HEARTBEAT
 */
static void heartbeat_func(){
	while(1){
		heartbeat_value++ ;
		rt_task_wait_period() ;
	}
}

/*
 * Initialisation du module.
 */
int init_module(void){
	long tick_period;
	printk("inserting\n");

	shared_memory = rtai_kmalloc(101, sizeof(ArrayShared));
	
	rt_task_init(&writetab,write,1,STACK_SIZE,TASK_PRIO,1,0);
	tick_period = start_rt_timer(nano2count(TICK_PERIOD));
	rt_task_make_periodic(&writetab, rt_get_time()+tick_period, tick_period);

	return 0;
}

void cleanup_module(void){
	stop_rt_timer();
	rt_task_delete(&writetab);
	rtai_kfree(101);	
	printk("removing module\n");
	return;
}

