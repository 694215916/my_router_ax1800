#include	<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include	<signal.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#define BUF_LEN 4096

struct erase_info_user {
	unsigned int start;
	unsigned int length;
};

struct mtd_info_user {
	unsigned char type;
	unsigned int flags;
	unsigned int size;
	unsigned int erasesize;
	unsigned int oobblock;  
	unsigned int oobsize;  
	unsigned int ecctype;
	unsigned int eccsize;
};

#define MEMGETINFO 				_IOR('M', 1, struct mtd_info_user)
#define MEMERASE 					_IOW('M', 2, struct erase_info_user)
#define MEMUNLOCK               _IOW('M', 6, struct erase_info_user)

static int fd;
static char *mtd_d = "/dev/mtd3";

static unsigned char EeBuffer0[BUF_LEN];
static unsigned char pbuf[BUF_LEN];
static char mtd_dev[20];
static struct mtd_info_user mtdInfo;
static struct erase_info_user mtdEraseInfo;

	
void mtd_erase(void){
	
	int i;

	fd = open(mtd_dev, O_RDWR | O_SYNC);
	if(fd < 0) {
		fprintf(stderr, "Could not open mtd device: %s\n", mtd_dev);
		exit(1);
	}

	if(ioctl(fd, MEMGETINFO, &mtdInfo)) {
		fprintf(stderr, "Could not get MTD device info from %s\n", mtd_dev);
		close(fd);
		exit(1);
	}

	mtdEraseInfo.length = mtdInfo.erasesize;
	mtdEraseInfo.start = 0;
	
	for (mtdEraseInfo.start; mtdEraseInfo.start < mtdInfo.size; mtdEraseInfo.start += mtdInfo.erasesize) {
		ioctl(fd, MEMUNLOCK, &mtdEraseInfo);
		if(ioctl(fd, MEMERASE, &mtdEraseInfo)){
			fprintf(stderr, "Failed to erase block on %s at 0x%x\n", mtd_dev, mtdEraseInfo.start);
			close(fd);
			exit(1);
		}
	}		
	close(fd);
}

void mtd_write(unsigned int wlen){
	
	int val = 0;
	int i, j;
	unsigned char rn;

	srand(time(0));
	
	fd = open(mtd_dev, O_RDWR | O_SYNC);
	if(fd < 0) {
		printf("Could not open mtd device: %s\n",mtd_dev);
		exit(1);
	}

	rn = (unsigned char)rand();
	printf("rn = %x\n", rn);
	for (i = 0; i < mtdInfo.size; i+= wlen)
	{
		for (j = 0; j < wlen; j++)
			EeBuffer0[j] = (unsigned char) (rn + (i/wlen) + j);
		val = write(fd, EeBuffer0, wlen);
	}
	
	lseek(fd,0,SEEK_SET);

	for (i = 0; i < mtdInfo.size; i+= wlen) {
		if(read(fd, pbuf, wlen) != wlen){
			printf("read() failed\n");
			close(fd);
			exit(1);
		}
		for (j = 0; j < wlen; j++)
		{
			if (pbuf[j] != (unsigned char) (rn + (i/wlen) + j)) {
				printf("Test Fail\n");
				printf("i = %x, rn = %x, pbuf[%d] = %x\n", (unsigned int)i, rn, j, pbuf[j]);
				close(fd);
				exit(1);
			}

		}
	}
	
	close(fd);
}

void usage(char *cmd)
{
	printf("Usage:\n");
	printf("%s <mtd#> <writesize> <loop>\n", cmd);
	printf("write size should be page size for nand flash\n");
	printf("if loop == 0, the test times will be infinite\n");
	printf("Example: %s mtd3 2048 1\n", cmd);
}

int main(int argc, char *argv[])
{
	unsigned int wlen, loop;

	if (argc < 4) {
		usage(argv[0]);
	}
	
	sprintf(mtd_dev, "\/dev\/%s", argv[1]);
	printf("%s\n", mtd_dev);

	wlen = strtoul(argv[2], NULL, 10);
	if (wlen > BUF_LEN) {
		printf("write size should not > %d\n", BUF_LEN);
		return 0;
	}
	loop = strtoul(argv[3], NULL, 10);

	if (loop == 0) {
		while(1){
			mtd_erase();
			mtd_write(wlen);
			sleep(1);
		}
	} else {
		int i;
		for (i = 0; i < loop; i++) {
			mtd_erase();
			mtd_write(wlen);
			sleep(1);
		}
	}
	/* Erase the partition to clean state */
	mtd_erase();
	printf("Test pass\n");
	
	return 0;
}
