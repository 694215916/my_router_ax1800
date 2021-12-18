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

void *t_Test01(void *arg)
{
	int i;
	char *buff[TEST_SIZE] = {0,};
	unsigned int seed;
	int size = 0;
	char *p = NULL;
	unsigned int tot = 0;

	seed = time(NULL) + 1;
	size = rand_r(&seed) % TDATA_SIZE + 4;
	
	printf("t_Test01 : size[%d]\n", size);
	t1_run = 1;
	memset(buff, 0, sizeof(char *)*TEST_SIZE);
	for(i=0; i<TEST_SIZE; i++)
	{
		size += 1;
		//printf("test01 size[%d, %d]\n", i, size);
//	pthread_mutex_lock(&mutex);
		p = NULL;
		//usleep(1000);
		p = (char *)malloc(size);
		if ( !p ) {
			printf("test01 => malloc[%d, %d] fail[%s]\n", i, size, strerror(errno));
			break;
		}
//	pthread_mutex_unlock(&mutex);
		buff[i] = p;
		tot = tot + size;

		//printf("[TEST] t_Test01 : [%d][%d][0x%X]\n", i, size, buff[i]);
	}
	printf("t_Test01 : malloc end[%ld]\n", tot);

	for(i=0; i<TEST_SIZE; i++)
	{
		if(buff[i])
		{
//	pthread_mutex_lock(&mutex);
		//usleep(1000);
			free(buff[i]);
//	pthread_mutex_unlock(&mutex);
			buff[i] = NULL;
		}
	}
	t1_run = 0;
	printf("t_Test01 : end\n");

}

void *t_Test02(void *arg)
{
	int i;
	char *buff[TEST_SIZE] = {0,};
	unsigned int seed;
	int size = 0;
	char *p = NULL;
	unsigned int tot = 0;

	seed = time(NULL) + 2;
	size = rand_r(&seed) % TDATA_SIZE + 4;

	printf("t_Test02 : size[%d]\n", size);
	t2_run = 1;
	memset(buff, 0, sizeof(char *)*TEST_SIZE);
	for(i=0; i<TEST_SIZE; i++)
	{
		size += 1;
		//printf("test02 size[%d, %d]\n", i, size);
//	pthread_mutex_lock(&mutex);
		p = NULL;
		//usleep(1000);
		p = (char *)malloc(size);
		if ( !p ) {
			printf("test02 => malloc[%d, %d] fail[%s]\n", i, size, strerror(errno));
			break;
		}
		buff[i] = p;
		tot = tot + size;

//	pthread_mutex_unlock(&mutex);

		//printf("[TEST] t_Test02 : [%d][%d][0x%X]\n", i, size, buff[i]);
	}
	printf("t_Test02 : malloc end[%ld]\n", tot);

	for(i=0; i<TEST_SIZE; i++)
	{
		if(buff[i])
		{
//	pthread_mutex_lock(&mutex);
		//usleep(1000);
			free(buff[i]);
//	pthread_mutex_unlock(&mutex);
			buff[i] = NULL;
		}
	}
	t2_run = 0;
	printf("t_Test02 : end\n");
}

void *t_Test03(void *arg)
{
	int i;
	char *buff[TEST_SIZE*2] = {0,};
	unsigned int seed;
	int size = 0;
	char *p = NULL;
	unsigned int tot = 0;

	seed = time(NULL) + 3;
	size = rand_r(&seed) % TDATA_SIZE + 4;

	printf("t_Test03 : size[%d]\n", size);
	t3_run = 1;
	memset(buff, 0, sizeof(char *)*TEST_SIZE*2);
	for(i=0; i<TEST_SIZE*2; i++)
	{
		size += 1;
		//printf("test03 size[%d, %d]\n", i, size);
//	pthread_mutex_lock(&mutex);
		p = NULL;
		//usleep(1000);
		p = (char *)malloc(size);
		if ( !p ) {
			printf("test03 => malloc[%d, %d] fail[%s]\n", i, size, strerror(errno));
			break;
		}
		buff[i] = p;
		tot = tot + size;

//	pthread_mutex_unlock(&mutex);

		//printf("[TEST] t_Test01 : [%d][%d][0x%X]\n", i, size, buff[i]);
	}
	printf("t_Test03 : malloc end[%ld]\n", tot);

	for(i=0; i<TEST_SIZE*2; i++)
	{
		if(buff[i])
		{
//	pthread_mutex_lock(&mutex);
		//usleep(1000);
			free(buff[i]);
//	pthread_mutex_unlock(&mutex);
			buff[i] = NULL;
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
#if 1
		id = pthread_create(&tid1, NULL, t_Test01, NULL);
		if ( id < 0 ) {
			printf("pthread_create tid1 fail\n");
			return 1;
		}
		pthread_detach(tid1);
		t1_run = 1;
#endif
#if 1
		id  = pthread_create(&tid2, NULL, t_Test02, NULL);
		if ( id < 0 ) {
			printf("pthread_create tid2 fail\n");
			return 1;
		}
		pthread_detach(tid2);
		t2_run = 1;
#endif
#if 1
		id  = pthread_create(&tid3, NULL, t_Test03, NULL);
		if ( id < 0 ) {
			printf("pthread_create tid3 fail\n");
			return 1;
		}
		pthread_detach(tid3);
		t3_run = 1;
#endif

	while(t1_run == 1 || t2_run == 1 || t3_run == 1 ) {
		printf("run[%d, %d, %d]\n", t1_run, t2_run, t3_run);
		sleep(1);
	}

	printf("end\n");

//	pthread_mutex_destroy(&mutex);
	return 1;
}
