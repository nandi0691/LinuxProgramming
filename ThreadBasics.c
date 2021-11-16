#include<stdio.h>
#include<pthread.h>
#include<unistd.h> //For func's such as pause() and sleep()
//Compilation steps are as below
//gcc -g -c ThreadBasics.c -o thread.o
//gcc thread.o -o threadBasic -lpthread

//Multiple threads - stack will not shared among threads
//Heap Memory sockets ,FD,Global variables can all be shared
//Kernel will schedule thread and not process
//Signals will be sent per process and not per thread
//If any thread gets SegFault then all the threads will be terminated

//Below is the syntax for thread_fn_callback
static void * thread_fn_callback(void * arg)
{
	char * input = (char *)arg;
	int a = 0;
	while(a < 10)
	{
		printf("Messge from thread 1 %s\n",input);
		sleep(1);
		if(a++ == 6)
			pthread_exit(0); //This will allow thread terminate
	}
	//Thread will get terminated now
}

void thread1_create()
{
	pthread_t t1;//It is opaque DS
	static char * input = "All the best Nandeesh";
	int rc = pthread_create(&t1,NULL,thread_fn_callback,(void *)input);

	if(rc!= 0)
		printf("something is wrong in thread creation\n");
}
int main(int argc,char **argv)
{
	thread1_create();
	printf("main function will exit now\n");
	//pause();
	pthread_exit(0);//This will allow execution of all other threads , even though main thread terminates
	printf("Main function");
	//When main thread terminates all other threads will terminate, but vice versa is not true
	return 0;
}
