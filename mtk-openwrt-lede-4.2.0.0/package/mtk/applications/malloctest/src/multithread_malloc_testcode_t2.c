#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

#define TDATA_SIZE 64
#define TEST_SIZE 1000
//#define TEST_SIZE 500
//#define TEST_SIZE 100

int t1_run = 0;
int t2_run = 0;
int t3_run = 0;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void t_Test01(void)
{
	int i;
	char *buff1[TEST_SIZE] = {0,};
	char *buff2[TEST_SIZE] = {0,};
	char *buff3[TEST_SIZE*2] = {0,};

	unsigned int seed;
	int size = 0;
	char *p = NULL;
	unsigned int tot = 0;

	seed = time(NULL) + 1;
	size = rand_r(&seed) % TDATA_SIZE + 4;
	
	printf("t_Test01 : size[%d]\n", size);
	t1_run = 1;
	memset(buff1, 0, sizeof(char *)*TEST_SIZE);
	for(i=0; i<TEST_SIZE; i++)
	{
		size += 1;
		//printf("test01 size[%d, %d]\n", i, size);
	//pthread_mutex_lock(&mutex);
		p = NULL;
		//usleep(1000);
		p = (char *)malloc(size);
		if ( p == NULL) {
			printf("test01 => malloc[%d, %d] fail[%s]\n", i, size, strerror(errno));
			break;
		}
	//pthread_mutex_unlock(&mutex);
		buff1[i] = p;
		tot = tot + size;

		//printf("[TEST] t_Test01 : [%d][%d][0x%X]\n", i, size, buff[i]);
	}
	printf("t_Test01 : malloc end[%ld]\n", tot);


	seed = time(NULL) + 2;
	size = rand_r(&seed) % TDATA_SIZE + 4;

	printf("t_Test02 : size[%d]\n", size);
	t2_run = 1;
	memset(buff2, 0, sizeof(char *)*TEST_SIZE);
	for(i=0; i<TEST_SIZE; i++)
	{
		size += 1;
		//printf("test02 size[%d, %d]\n", i, size);
	//pthread_mutex_lock(&mutex);
		p = NULL;
		//usleep(1000);
		p = (char *)malloc(size);
		if ( p = NULL) {
			printf("test02 => malloc[%d, %d] fail[%s]\n", i, size, strerror(errno));
			break;
		}
		buff2[i] = p;
		tot = tot + size;

	//pthread_mutex_unlock(&mutex);

		//printf("[TEST] t_Test02 : [%d][%d][0x%X]\n", i, size, buff[i]);
	}
	printf("t_Test02 : malloc end[%ld]\n", tot);

	seed = time(NULL) + 3;
	size = rand_r(&seed) % TDATA_SIZE + 4;

	printf("t_Test03 : size[%d]\n", size);
	t3_run = 1;
	memset(buff3, 0, sizeof(char *)*TEST_SIZE*2);
	for(i=0; i<TEST_SIZE*2; i++)
	{
		size += 1;
		//printf("test03 size[%d, %d]\n", i, size);
	//pthread_mutex_lock(&mutex);
		p = NULL;
		//usleep(1000);
		p = (char *)malloc(size);
		if ( p == NULL) {
			printf("test03 => malloc[%d, %d] fail[%s]\n", i, size, strerror(errno));
			break;
		}
		buff3[i] = p;
		tot = tot + size;

	//pthread_mutex_unlock(&mutex);

		//printf("[TEST] t_Test01 : [%d][%d][0x%X]\n", i, size, buff[i]);
	}
	printf("t_Test03 : malloc end[%ld]\n", tot);
		

	for(i=0; i<TEST_SIZE; i++)
	{
		if(buff1[i])
		{
	//pthread_mutex_lock(&mutex);
		//usleep(1000);
			free(buff1[i]);
	//pthread_mutex_unlock(&mutex);
			buff1[i] = NULL;
		}
	}
	t1_run = 0;
	printf("t_Test01 : end\n");


	for(i=0; i<TEST_SIZE; i++)
	{
		if(buff2[i])
		{
	//pthread_mutex_lock(&mutex);
		//usleep(1000);
			free(buff2[i]);
	//pthread_mutex_unlock(&mutex);
			buff2[i] = NULL;
		}
	}
	t2_run = 0;
	printf("t_Test02 : end\n");


	for(i=0; i<TEST_SIZE*2; i++)
	{
		if(buff3[i])
		{
	//pthread_mutex_lock(&mutex);
		//usleep(1000);
			free(buff3[i]);
	//pthread_mutex_unlock(&mutex);
			buff3[i] = NULL;
		}
	}
	t3_run = 0;
	printf("t_Test03 : end\n");
	
}

int main(int argc, char *argv[])
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	int id = 0;

	printf("start[%s]\n", __TIME__);
#if 0
		id = pthread_create(&tid1, NULL, t_Test01, NULL);
		if ( id < 0 ) {
			printf("pthread_create tid1 fail\n");
			return 1;
		}
		pthread_detach(tid1);
		t1_run = 1;
#endif
#if 0
		id  = pthread_create(&tid2, NULL, t_Test02, NULL);
		if ( id < 0 ) {
			printf("pthread_create tid2 fail\n");
			return 1;
		}
		pthread_detach(tid2);
		t2_run = 1;
#endif
#if 0
		id  = pthread_create(&tid3, NULL, t_Test03, NULL);
		if ( id < 0 ) {
			printf("pthread_create tid3 fail\n");
			return 1;
		}
		pthread_detach(tid3);
		t3_run = 1;
#endif

	t_Test01();
	
	while(t1_run == 1 || t2_run == 1 || t3_run == 1 ) {
		printf("run[%d, %d, %d]\n", t1_run, t2_run, t3_run);
		sleep(1);
	}

	printf("end\n");

	//pthread_mutex_destroy(&mutex);
	return 1;
}
