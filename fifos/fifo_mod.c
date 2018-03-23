#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>
#include <math.h>
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_fifos.h>

#define TICK_PERIOD 1000000
#define TASK_PRIO 1
#define STACK_SIZE 10000
#define FIFO 0

static RT_TASK mytask;

/*
 *
 *
 *
 *
 */
static void fun(int t ){
	printk("filling fifo\n");
	int cpt = 0;
	int value ;

	while (1) {
		value = 42;
		/*ce que vous voulez ici*/
		rtf_put(FIFO,&cpt,sizeof(cpt));
		rtf_put(FIFO,&value,sizeof(value));
		cpt ++;
		rt_task_wait_period();
	}
}


/*
 *
 * Initialisation du module.
 *
 *
 */
int init_module(void){
	long tick_period;
	printk("inserting\n");

	rt_task_init(&mytask,fun,1,STACK_SIZE,TASK_PRIO,1,0);
	rtf_create(FIFO,8000);
	tick_period = start_rt_timer(nano2count(TICK_PERIOD));
	rt_task_make_periodic(&mytask, rt_get_time()+tick_period, tick_period);
	
	return 0;
}

void cleanup_module(void){
	stop_rt_timer();
	rtf_destroy(FIFO);
	rt_task_delete(&mytask);
	printk("removing module \n");
	return;
}

