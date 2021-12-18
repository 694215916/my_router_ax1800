#!/bin/sh

OPTION=$1
usage()
{
	echo "Usage: sd_rw_test.sh [OPTION] [file]/[count]"
	echo " OPTION are:"
	echo "    lo       loopback test, please specify a file name in your mounted dir[file]"
	echo "    rw       use lmdd to do read/write test for [count] times(default is 1)"
	echo "    ro       use lmdd to do read only test for [count] times(default is 1)"
	echo "    wo       use lmdd to do write only test for [count] times(default is 1)"
	echo " example:"
	echo "	loopback test: sd_rw_test.sh lo /mnt/mmcblk0p1/test.txt"
	echo "	read/write test: sd_rw_test.sh rw 10"
	echo "	read only: sd_rw_test.sh ro 10"
	echo "	write only: sd_rw_test.sh wo 10"
	exit 1
}

if [ "$OPTION" != "lo" -a "$OPTION" != "rw" -a "$OPTION" != "ro" -a "$OPTION" != "wo" ]; then
	usage
	exit 1
fi

if [ "$OPTION" == "lo" ]; then
	if [ ! -f "$2" ]; then
		usage
		exit 1
	fi
	if [ -z $3 ]; then
		INPUT_COUNT=1
        else
		INPUT_COUNT=$3
	fi
	PASS=0
	FAIL=0
	TestFile=$2
	TestFileCRC=`md5sum $TestFile | sed 's/\/mnt\/.*//'`
else
# rw/ro/wo , $2 is count
	if [ -z $2 ]; then
		INPUT_COUNT=1
	else
		INPUT_COUNT=$2
	fi
fi

COUNT=1
MOUNT=`mount | grep mmc | sed 's/^\/dev.*\/mnt/\/mnt/g' | sed 's/\ type.*$//g'`

echo 3 > /proc/sys/vm/drop_caches
echo 8192 > /proc/sys/vm/min_free_kbytes

doLoopBackTest()
{
	echo "#Date : `date`"
	echo "#--- The Loopback test Run $COUNT ---"
	rm -rf $MOUNT/backup
	sync
	mkdir $MOUNT/backup
	echo "cp $TestFile $MOUNT/backup"
#	time cp $TestFile $MOUNT/backup
	cp $TestFile $MOUNT/backup
	sync
	bk_file=`ls $MOUNT/backup`
#	ls -l $TestFile
#	ls -l $MOUNT/backup/$bk_file
	bk_file_crc=`md5sum $MOUNT/backup/$bk_file | sed 's/\/mnt\/.*//'`
	if [ "$bk_file_crc" != "$TestFileCRC" ]; then
		FAIL=`expr $FAIL + 1`
	else
		PASS=`expr $PASS + 1`
	fi
	rm -rf $MOUNT/backup
	sync
	echo "`date` --- Loopback Test: Pass-$PASS ,Failed-$FAIL ---"
}

doRWTest()
{
	echo "#Date : `date`"
	echo "#--- R/W test Run $COUNT ---"
	if [ "$OPTION" == "rw" -o "$OPTION" == "wo" ]; then
	echo "# Memory ===> SD"
		for i in 16m 32m 64m 128m 256m 512m 1024m
		do
			echo "...Start writing filesize=$i to SD..."
			rm -rf $MOUNT/DDFile*
			sync
			lmdd if=internal of=$MOUNT/DDFile$i move=$i fsync=1
		done
	fi
	if [ ! -f $MOUNT/DDFile1024m ]; then
		echo "... Generating filesize=1024m in SD..."
		lmdd if=internal of=$MOUNT/DDFile1024m move=1024m fsync=1
	fi
	if [ "$OPTION" == "rw" -o "$OPTION" == "ro" ]; then
		echo "# SD ===> Memory"
		for i in 16m 32m 64m 128m 256m 512m 1024m
		do
			echo "...Start reading filesize=$i from SD..."
			lmdd if=$MOUNT/DDFile1024m of=internal move=$i fsync=1
		done
	fi
	rm -rf $MOUNT/DDFile*
}

echo "***** Start Test (Total $INPUT_COUNT Runs)*****"
while [ $COUNT -le $INPUT_COUNT ]
do
	if [ "$OPTION" == "lo" ]; then
		if [ -d "$MOUNT" ]; then
			doLoopBackTest 
		else
			echo "*** Error: mount device fail ***"
			exit 1
		fi
	fi
	if [ "$OPTION" == "rw" -o "$OPTION" == "wo" -o "$OPTION" == "ro" ]; then
		if [ -d "$MOUNT" ]; then
			doRWTest
		else
			echo "*** Error: mount device fail ***"
			exit 1
		fi
	fi
	COUNT=`expr $COUNT + 1`
done
