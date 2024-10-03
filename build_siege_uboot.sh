#!/bin/bash
if [ "$1" = "clean" ];then

    echo "rm -rf ./obj"
    rm -rf ./obj

    echo "rm -f uboot_siege*.bin"
    rm -f uboot_siege*.bin
    exit;
fi

#copy lib files here ???
echo "====== build u-boot binaries ======= " 

#export CROSS_COMPILE=/volume/fwtools/gcc/jnpr/4.2.1/mips64-juniper-junos.8/bin/mips64-juniper-junos-
#export JUNOS_DTC=/volume/fwtools/dtc/1.2.0/bin/dtc   
export CROSS_COMPILE=/volume/hab/Linux/Ubuntu-12.04/x86_64/gcc/jnpr/4.2.1/mips64-juniper-junos.11/bin/mips64-juniper-junos-
export JUNOS_DTC=/volume/hab/Linux/Ubuntu-12.04/x86_64/dtc/1.4.1/bin/dtc
#export HOST_OS=FreeBSD
export OCTEON_MODEL=OCTEON_CN70XX
export OCTEON_N32LIB_PATH=`pwd`/gcc_depends/n32
export OCTEON_GCC_INCLUDE_PATH=`pwd`/gcc_depends/include


# svl server
MAKE=/volume/hab/Linux/Ubuntu-12.04/x86_64/gmake/3.80_20080515/bin/gmake

# junos pool server
#MAKE=gmake

export UBOOT_SRCTOP=`pwd`
export UBOOT_OBJTOP=${UBOOT_SRCTOP}/obj/
export UBOOT_STAGE1_SRCTOP=${UBOOT_SRCTOP}/board/juniper/srx_siege_stage1

echo "[Building stage1 ...]";
echo "${uboot_make} -C ${UBOOT_STAGE1_SRCTOP} O=${UBOOT_OBJTOP}/stage1/"; 
${MAKE} -C ${UBOOT_STAGE1_SRCTOP} O=${UBOOT_OBJTOP}/stage1/; 

if [ ! -f "obj/stage1/spi-boot.bin" ]; then
    echo "[Building stage1 again ...]";
    ${MAKE} -C ${UBOOT_STAGE1_SRCTOP} O=${UBOOT_OBJTOP}/stage1/; 
fi

echo "[Building stage2 ...]";
echo "${uboot_make} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage2/ juniper_srx_siege_stage2_config"; 
${MAKE} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage2/ juniper_srx_siege_stage2_config; 

echo "${uboot_make} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage2/ "; 
${MAKE} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage2/; 

echo "[Building stage3 ...]";
echo "${uboot_make} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage3/ juniper_srx_siege_config"; 
${MAKE} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage3/ juniper_srx_siege_config; 

echo "${uboot_make} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage3/ "; 
${MAKE} -C ${UBOOT_SRCTOP} O=${UBOOT_OBJTOP}/stage3/; 


#get ver_str from #define UBOOT_API_REVISION_NUMBER "3.2"
ver_str=`grep "UBOOT_API_REVISION_NUMBER" ./include/configs/juniper_srx_siege_version.h`
ver_str=${ver_str#*\"}
ver_str=${ver_str%\"*}

# /* todo */
#./siege_merge_uboot_binary.sh
echo "====== merge u-boot binaries to uboot_siege_$ver_str.bin ======= " 


find ./obj/ -name "*.bin"

cp ./obj/stage1/spi-boot.bin ./
cp ./obj/stage2/u-boot-juniper_srx_siege_stage2_crc.bin ./
cp ./obj/stage3/u-boot-juniper_srx_siege_crc.bin ./
cp ./obj/stage3/tools/siege_merge_stages ./

echo "" 

if [ -f "spi-boot.bin" ] && [ -f "u-boot-juniper_srx_siege_stage2_crc.bin" ] && [ -f "u-boot-juniper_srx_siege_crc.bin" ]; then
    echo "===== merge 3 stages to 1 file uboot-siege-3in1.bin ======="
        ./siege_merge_stages  spi-boot.bin u-boot-juniper_srx_siege_stage2_crc.bin u-boot-juniper_srx_siege_crc.bin uboot-siege-3in1.bin
        chmod 666 uboot-siege-3in1.bin
    echo "done"
    rm spi-boot.bin u-boot-juniper_srx_siege_stage2_crc.bin u-boot-juniper_srx_siege_crc.bin siege_merge_stages
else
    echo "compile error! can't find all 3 stages source file!"
    exit
fi

echo "" 

if [ -f "siege-ushell" ] && [ -f "loader_crc" ] && [ -f "uboot-siege-3in1.bin" ]; then
    echo "===== make flash 4m image siege_4m.bin ===== "
    python siege_flash_image_gen.py uboot-siege-3in1.bin loader_crc siege-ushell
        chmod 666 siege_4m.bin 
    echo "done"
fi
mv uboot-siege-3in1.bin uboot_siege_$ver_str.bin

echo "====== build finish , uboot_siege_$ver_str.bin is the target file =======" 



