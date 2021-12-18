#!/bin/bash

while read line; do
	key=$(echo ${line} | cut -f1 -d':')
	value=$(echo ${line} | cut -f2 -d':')

	case "${key}" in
	"UUID")
		UUID=${value}
		;;
	"Data blocks")
		DATA_BLOCKS=${value}
		;;
	"Data block size")
		DATA_BLOCK_SIZE=${value}
		;;
	"Hash block size")
		HASH_BLOCK_SIZE=${value}
		;;
	"Hash algorithm")
		HASH_ALG=${value}
		;;
	"Salt")
		SALT=${value}
		;;
	"Root hash")
		ROOT_HASH=${value}
		;;
	esac
done

#
# dm=<name>,<uuid>,<mode>,<num>:
#    <start>,<length>,<type>,
#    <version>,<data_dev>,<hash_dev>,<data_block_size>,<hash_block_size>,
#    <num_data_blocks><hash_start_block>,<algorithm>,<root_hash>,<root_salt>:
#
# <uuid>   ::= xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx | "none"
# <mode>   ::= "ro" | "rw"
# <num>    ::= number of target device, set as 1
#
# More detail in field you can ref.
# https://www.kernel.org/doc/html/latest/admin-guide/device-mapper/verity.html
# https://gitlab.com/cryptsetup/cryptsetup/wikis/DMVerity
#

BOOTARGS=$( printf 'console=ttyS0,115200n1 root=/dev/dm-0 rootfstype=squashfs loglevel=8 dm="vroot none ro 1,0 %s verity 1 /dev/mtdblock6 /dev/mtdblock6 %s %s %s %s %s %s %s,"' \
                   $((${DATA_BLOCKS} * 8)) ${DATA_BLOCK_SIZE} ${HASH_BLOCK_SIZE} ${DATA_BLOCKS} $((${DATA_BLOCKS} + 1)) ${HASH_ALG} ${ROOT_HASH} ${SALT} )

echo setenv bootargs ${BOOTARGS}
