#!/bin/sh

OPTION=$1
HASH_NUMBER=$2
PKEY_HASH_FILE=$3

MTK_SMC_DIR="/sys/kernel/debug/mtk_smc"
MTK_SMC_PARAMETERS_DIR="${MTK_SMC_DIR}/parameters"
MTK_SMC_RESULTS_DIR="${MTK_SMC_DIR}/results"
RED_FONT_YELLOW_BKG_ST="\033[31;43m"
RED_FONT_YELLOW_BKG_RST="\033[0m"

usage()
{
	echo "Usage: efuse_tool.sh [OPTION] [HASH_NUMBER] [PKEY_HASH_FILE]"
	echo " OPTION are:"
	echo "    wh       write hash [PKEY_HASH_FILE] into the one"
	echo "             [HASH_NUMBER] of four efuse hash fields"
	echo "    rh       read hash from one [HASH_NUMBER] of four efuse"
	echo "             hash fields"
	echo "    lh       lock one [HASH_NUMBER] of four efuse hash fields"
	echo "    cl       check if lock one [HASH_NUMBER] of four efuse hash"
	echo "             fields"
	echo "    dh       disable one [HASH_NUMBER] of four efuse hash fields"
	echo "    cd       check if disable one [HASH_NUMBER] of four efuse"
	echo "             hash fields"
	echo "    es       enable secure boot of BROM"
	echo "    cs       check if enable secure boot of BROM"
	echo "    dj       disable JTAG"
	echo "    cj       check if disable JTAG"
	echo " example:"
	echo "    efuse_tool.sh wh 0 bl2.img.signkeyhash"
	echo "    efuse_tool.sh rh 0"
	echo "    efuse_tool.sh lh 0"
	echo "    efuse_tool.sh es"
	exit 1
}

if [ "${OPTION}" != "wh" -a "${OPTION}" != "rh" -a \
     "${OPTION}" != "lh" -a "${OPTION}" != "cl" -a \
     "${OPTION}" != "dh" -a "${OPTION}" != "cd" -a \
     "${OPTION}" != "es" -a "${OPTION}" != "cs" -a \
     "${OPTION}" != "dj" -a "${OPTION}" != "cj" ]; then
	echo -e "${RED_FONT_YELLOW_BKG_ST}"\
		"[OPTION] must be set"\
		"${RED_FONT_YELLOW_BKG_RST}"
	usage
	exit 1
fi

if [ "$OPTION" == "wh" ]; then
	if [ "${HASH_NUMBER}" != "0" -a "${HASH_NUMBER}" != "1" -a \
	     "${HASH_NUMBER}" != "2" -a "${HASH_NUMBER}" != "3" ]; then
		echo -e "${RED_FONT_YELLOW_BKG_ST}"\
			"[HASH_NUMBER] must be set as 0, 1, 2, or 3"\
			"${RED_FONT_YELLOW_BKG_RST}"
		usage
		exit 1
	fi
	if [ ! -f "${PKEY_HASH_FILE}" ]; then
		echo -e "${RED_FONT_YELLOW_BKG_ST}"\
			"[PKEY_HASH_FILE] must be set an existed keyhash file"\
			"${RED_FONT_YELLOW_BKG_RST}"
		usage
		exit 1
	fi
fi

if [ "${OPTION}" == "rh" -o "${OPTION}" == "lh" -o \
     "${OPTION}" == "cl" -o "${OPTION}" == "dh" -o \
     "${OPTION}" == "cd" ]; then
	if [ "${HASH_NUMBER}" != "0" -a "${HASH_NUMBER}" != "1" -a \
	     "${HASH_NUMBER}" != "2" -a "${HASH_NUMBER}" != "3" ]; then
		echo -e "${RED_FONT_YELLOW_BKG_ST}"\
			"[HASH_NUMBER] must be set as 0, 1, 2, or 3"\
			"${RED_FONT_YELLOW_BKG_RST}"
		usage
		exit 1
	fi
fi

if [ ! -d ${MTK_SMC_DIR} ]; then
	echo -e "${RED_FONT_YELLOW_BKG_ST}"\
		"${MTK_SMC_DIR} NOT EXIST"\
		"${RED_FONT_YELLOW_BKG_RST}"
	echo "please install mtk_smc module first"
	exit 1
fi

get_public_key_hash_from_file()
{
	PKEY_HASH1=$(hexdump -e '/4 "%X\n"' -s 0  -n 4 ${PKEY_HASH_FILE})
	PKEY_HASH2=$(hexdump -e '/4 "%X\n"' -s 4  -n 4 ${PKEY_HASH_FILE})
	PKEY_HASH3=$(hexdump -e '/4 "%X\n"' -s 8  -n 4 ${PKEY_HASH_FILE})
	PKEY_HASH4=$(hexdump -e '/4 "%X\n"' -s 12 -n 4 ${PKEY_HASH_FILE})
	PKEY_HASH5=$(hexdump -e '/4 "%X\n"' -s 16 -n 4 ${PKEY_HASH_FILE})
	PKEY_HASH6=$(hexdump -e '/4 "%X\n"' -s 20 -n 4 ${PKEY_HASH_FILE})
	PKEY_HASH7=$(hexdump -e '/4 "%X\n"' -s 24 -n 4 ${PKEY_HASH_FILE})
	PKEY_HASH8=$(hexdump -e '/4 "%X\n"' -s 28 -n 4 ${PKEY_HASH_FILE})

	echo PKEY_HASH1 = 0x${PKEY_HASH1}
	echo PKEY_HASH2 = 0x${PKEY_HASH2}
	echo PKEY_HASH3 = 0x${PKEY_HASH3}
	echo PKEY_HASH4 = 0x${PKEY_HASH4}
	echo PKEY_HASH5 = 0x${PKEY_HASH5}
	echo PKEY_HASH6 = 0x${PKEY_HASH6}
	echo PKEY_HASH7 = 0x${PKEY_HASH7}
	echo PKEY_HASH8 = 0x${PKEY_HASH8}
}

setup_smc_parameters()
{
	echo $1 > ${MTK_SMC_PARAMETERS_DIR}/a0
	echo $2 > ${MTK_SMC_PARAMETERS_DIR}/a1
	echo $3 > ${MTK_SMC_PARAMETERS_DIR}/a2
	echo $4 > ${MTK_SMC_PARAMETERS_DIR}/a3
	echo $5 > ${MTK_SMC_PARAMETERS_DIR}/a4
}

clean_smc_results()
{
	echo 0x0 > ${MTK_SMC_RESULTS_DIR}/r0
	echo 0x0 > ${MTK_SMC_RESULTS_DIR}/r1
	echo 0x0 > ${MTK_SMC_RESULTS_DIR}/r2
	echo 0x0 > ${MTK_SMC_RESULTS_DIR}/r3
}

issue_smc()
{
	echo 1 > ${MTK_SMC_DIR}/issue
}

get_smc_results()
{
	R0=$(cat ${MTK_SMC_RESULTS_DIR}/r0)
	R1=$(cat ${MTK_SMC_RESULTS_DIR}/r1)
	R2=$(cat ${MTK_SMC_RESULTS_DIR}/r2)
	R3=$(cat ${MTK_SMC_RESULTS_DIR}/r3)

	R0_HEX=$(printf "%X" ${R0})
	R1_HEX=$(printf "%X" ${R1})
	R2_HEX=$(printf "%X" ${R2})
	R3_HEX=$(printf "%X" ${R3})
}

if [ "${OPTION}" == "wh" ]; then
	case ${HASH_NUMBER} in
		0) SMC_FUNCTION_ID=C2000510
			;;
		1) SMC_FUNCTION_ID=C2000511
			;;
		2) SMC_FUNCTION_ID=C2000512
			;;
		3) SMC_FUNCTION_ID=C2000513
			;;
		*) SMC_FUNCTION_ID=0
			;;
	esac
	get_public_key_hash_from_file

	echo -e "${RED_FONT_YELLOW_BKG_ST}"\
		"Please check the above hash if correct or not.\n"\
		"HASH#${HASH_NUMBER} will be written."\
		"${RED_FONT_YELLOW_BKG_RST}"
	read -p "Continue? <y/n>" prompt
	[ ${prompt} != "y" ] && exit 1

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${PKEY_HASH2}${PKEY_HASH1} \
			     0x${PKEY_HASH4}${PKEY_HASH3} \
			     0x${PKEY_HASH6}${PKEY_HASH5} \
			     0x${PKEY_HASH8}${PKEY_HASH7}
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 0 ] 2>/dev/null; then
		echo "Write HASH#${HASH_NUMBER} SUCCESS"
	else
		echo "Write HASH#${HASH_NUMBER} FAIL"
		echo "R0 = 0x${R0_HEX}"
	fi
fi

if [ "${OPTION}" == "rh" ]; then
	SMC_FUNCTION_ID=C2000501
	case ${HASH_NUMBER} in
		0) EFUSE_INDEX=8
			;;
		1) EFUSE_INDEX=9
			;;
		2) EFUSE_INDEX=A
			;;
		3) EFUSE_INDEX=B
			;;
		*) EFUSE_INDEX=FF
			;;
	esac

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x20 \
			     0x0 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -ne 0 ] 2>/dev/null; then
		echo "PKEY_HASH1 = 0x${R0_HEX:8:16}"
		echo "PKEY_HASH2 = 0x${R0_HEX:0:8}"
		echo "PKEY_HASH3 = 0x${R1_HEX:8:16}"
		echo "PKEY_HASH4 = 0x${R1_HEX:0:8}"
		echo "PKEY_HASH5 = 0x${R2_HEX:8:16}"
		echo "PKEY_HASH6 = 0x${R2_HEX:0:8}"
		echo "PKEY_HASH7 = 0x${R3_HEX:8:16}"
		echo "PKEY_HASH8 = 0x${R3_HEX:0:8}"
	else
		echo "HASH#${HASH_NUMBER} is empty"
	fi
fi

if [ "${OPTION}" == "lh" ]; then
	SMC_FUNCTION_ID=C2000502
	case ${HASH_NUMBER} in
		0) EFUSE_INDEX=10
			;;
		1) EFUSE_INDEX=11
			;;
		2) EFUSE_INDEX=12
			;;
		3) EFUSE_INDEX=13
			;;
		*) EFUSE_INDEX=FF
			;;
	esac

	echo -e "${RED_FONT_YELLOW_BKG_ST}"\
		"HASH#${HASH_NUMBER} will be locked."\
		"${RED_FONT_YELLOW_BKG_RST}"
	read -p "Continue? <y/n>" prompt
	[ ${prompt} != "y" ] && exit 1

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x1 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 0 ] 2>/dev/null; then
		echo "Lock Hash#${HASH_NUMBER} SUCCESS"
	else
		echo "Lock Hash#${HASH_NUMBER} FAIL"
		echo "R0 = 0x${R0_HEX}"
	fi
fi

if [ "${OPTION}" == "cl" ]; then
	SMC_FUNCTION_ID=C2000501
	case ${HASH_NUMBER} in
		0) EFUSE_INDEX=10
			;;
		1) EFUSE_INDEX=11
			;;
		2) EFUSE_INDEX=12
			;;
		3) EFUSE_INDEX=13
			;;
		*) EFUSE_INDEX=FF
			;;
	esac

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x0 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 1 ] 2>/dev/null; then
		echo "Hash#${HASH_NUMBER} is locked"
	else
		echo "Hash#${HASH_NUMBER} is unlocked"
	fi
fi

if [ "${OPTION}" == "dh" ]; then
	SMC_FUNCTION_ID=C2000502
	case ${HASH_NUMBER} in
		0) EFUSE_INDEX=15
			;;
		1) EFUSE_INDEX=16
			;;
		2) EFUSE_INDEX=17
			;;
		3) EFUSE_INDEX=18
			;;
		*) EFUSE_INDEX=FF
			;;
	esac

	echo -e "${RED_FONT_YELLOW_BKG_ST}"\
		"HASH#${HASH_NUMBER} will be disabled."\
		"${RED_FONT_YELLOW_BKG_RST}"
	read -p "Continue? <y/n>" prompt
	[ ${prompt} != "y" ] && exit 1

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x1 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 0 ] 2>/dev/null; then
		echo "Disable Hash#${HASH_NUMBER} SUCCESS"
	else
		echo "Disable Hash#${HASH_NUMBER} FAIL"
		echo "R0 = 0x${R0_HEX}"
	fi
fi

if [ "${OPTION}" == "cd" ]; then
	SMC_FUNCTION_ID=C2000501
	case ${HASH_NUMBER} in
		0) EFUSE_INDEX=15
			;;
		1) EFUSE_INDEX=16
			;;
		2) EFUSE_INDEX=17
			;;
		3) EFUSE_INDEX=18
			;;
		*) EFUSE_INDEX=FF
			;;
	esac

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x0 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 1 ] 2>/dev/null; then
		echo "Hash#${HASH_NUMBER} is disabled"
	else
		echo "Hash#${HASH_NUMBER} is enabled"
	fi
fi

if [ "${OPTION}" == "es" ]; then
	SMC_FUNCTION_ID=C2000502
	EFUSE_INDEX=1A

	echo -e "${RED_FONT_YELLOW_BKG_ST}"\
		"Secur boot will be enabled."\
		"${RED_FONT_YELLOW_BKG_RST}"
	read -p "Continue? <y/n>" prompt
	[ ${prompt} != "y" ] && exit 1

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x1 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 0 ] 2>/dev/null; then
		echo "Enable secure boot SUCCESS"
	else
		echo "Enable secure boot FAIL"
		echo "R0 = 0x${R0_HEX}"
	fi
fi

if [ "${OPTION}" == "cs" ]; then
	SMC_FUNCTION_ID=C2000501
	EFUSE_INDEX=1A

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x0 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 1 ] 2>/dev/null; then
		echo "Secure boot is enabled"
	else
		echo "Secure boot is disabled"
	fi
fi

if [ "${OPTION}" == "dj" ]; then
	SMC_FUNCTION_ID=C2000502
	EFUSE_INDEX=19

	echo -e "${RED_FONT_YELLOW_BKG_ST}"\
		"JTAG will be disabled."\
		"${RED_FONT_YELLOW_BKG_RST}"
	read -p "Continue? <y/n>" prompt
	[ ${prompt} != "y" ] && exit 1

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x1 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 0 ] 2>/dev/null; then
		echo "Disable JTAG SUCCESS"
	else
		echo "Disable JTAG FAIL"
		echo "R0 = 0x${R0_HEX}"
	fi
fi

if [ "${OPTION}" == "cj" ]; then
	SMC_FUNCTION_ID=C2000501
	EFUSE_INDEX=19

	setup_smc_parameters 0x${SMC_FUNCTION_ID} \
			     0x${EFUSE_INDEX} \
			     0x1 \
			     0x0 \
			     0x0
	clean_smc_results
	issue_smc

	get_smc_results
	if [ ${R0} -eq 1 ] 2>/dev/null; then
		echo "JTAG is disabled"
	else
		echo "JTAG is enabled"
	fi
fi
