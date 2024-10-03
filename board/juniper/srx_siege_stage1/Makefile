#/***********************license start***************
# * Copyright (c) 2003-2014  Cavium Inc. (support@cavium.com). All rights
# * reserved.
# *
# *
# * Redistribution and use in source and binary forms, with or without
# * modification, are permitted provided that the following conditions are
# * met:
# *
# *     * Redistributions of source code must retain the above copyright
# *       notice, this list of conditions and the following disclaimer.
# *
# *     * Redistributions in binary form must reproduce the above
# *       copyright notice, this list of conditions and the following
# *       disclaimer in the documentation and/or other materials provided
# *       with the distribution.
# *
# *     * Neither the name of Cavium Inc. nor the names of
# *       its contributors may be used to endorse or promote products
# *       derived from this software without specific prior written
# *       permission.
# *
# * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
# * AND WITH ALL FAULTS AND CAVIUM NETWORKS MAKES NO PROMISES, REPRESENTATIONS
# * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
# * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
# * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
# * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
# * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
# * PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET
# * POSSESSION OR CORRESPONDENCE TO DESCRIPTION.  THE ENTIRE RISK ARISING OUT
# * OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
# *
# *
# * For any questions regarding licensing please contact marketing@cavium.com
# *
# ***********************license end**************************************/


# Juniper, get object target directory by -O option 
ifdef O
ifeq ("$(origin O)", "command line")
BUILD_DIR := $(O)
endif
endif

# Call a source code checker (by default, "sparse") as part of the
# C compilation.
#
# Use 'make C=1' to enable checking of re-compiled files.
#
# See the linux kernel file "Documentation/sparse.txt" for more details,
# including where to get the "sparse" utility.

ifdef C
ifeq ("$(origin C)", "command line")
CHECKSRC := $(C)
endif
endif
ifndef CHECKSRC
  CHECKSRC = 0
endif
export CHECKSRC

ifneq ($(BUILD_DIR),)
saved-output := $(BUILD_DIR)

# Attempt to create a output directory.
$(shell [ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR})

# Verify if it was successful.
BUILD_DIR := $(shell cd $(BUILD_DIR) && /bin/pwd)
$(if $(BUILD_DIR),,$(error output directory "$(saved-output)" does not exist))
endif # ifneq ($(BUILD_DIR),)

OBJTREE     := $(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))

FLAGS=-mabi=64 -mno-abicalls -fno-pic -g -W -Wall -static -ffreestanding \
	-static -msym32

# FLAGS+=-DDEBUG
# LDFLAGS=-nostartfiles -Wl,-Ttext,0xffffffff81000000 \
#	-Wl,-Bstatic -Wl,-e,__start \
#	-nostdlib -Wl,--gc-sections -Wl,-T,spi-boot.lds

# Juniper, change the tools chain 
NM=$(CROSS_COMPILE)nm
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
LDBFD=$(CROSS_COMPILE)ld.bfd
OBJCOPY=$(CROSS_COMPILE)objcopy

SB_OBJTOP   := $(SB_OBJROOT)$(MACHINE)

obj := $(BUILD_DIR)/

SB_SRCTOP   := $(SRCTOP)

LDFLAGS=-EB -Bstatic --gc-sections -G 0 -n -nostdlib

#by juniper change march=octeon3 to march=octeon
CFLAGS=${FLAGS} -Os -I$(UBOOT_STAGE1_SRCTOP) \
    -I$(UBOOT_SRCTOP)/arch/mips/include/asm/arch-octeon/ \
    -I$(UBOOT_SRCTOP)/arch/mips/include/ \
    -I$(UBOOT_SRCTOP)/include/ \
    -finline-functions \
    -fno-reorder-functions -march=octeon -EB \
	-nodefaultlibs -mno-check-zero-division -DOCTEON_MODEL=OCTEON_CN70XX \
	-fwhole-program -msoft-float


# Juniper, use header files in u-boot
ASFLAGS=${FLAGS} -I$(UBOOT_STAGE1_SRCTOP) \
                 -I$(UBOOT_SRCTOP)/arch/mips/include/asm/ \
                 -I$(UBOOT_SRCTOP)/arch/mips/include/ -EB \
                 -O -march=octeon

SPI_SRCS=spi-boot.c

SYSTEM_MAP = \
	$(NM) $1 | \
	grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | \
	LC_ALL=C sort

.PHONY: all
all: depend $(obj)System-spi-boot.map $(obj)spi-boot.bin

$(obj)System-spi-boot.map: $(obj)spi-boot.elf
	echo "obj = $(obj)"
	echo " UBOOT_STAGE1_OBJTOP = $(UBOOT_STAGE1_OBJTOP)"
	@$(call SYSTEM_MAP,$<) > $@

$(obj)spi-boot.elf:	$(obj)spi-boot-start.o $(obj)spi-boot.o spi-boot.lds
	$(LD) ${LDFLAGS} \
		-T spi-boot.lds -o $@ $^ -Map $(obj)spi-boot.map \
		-Ttext 0xffffffff81000000

$(obj)spi-boot-start.o: spi-boot-start.S spi-config.h
	echo "obj = $(obj)"
	echo " UBOOT_STAGE1_OBJTOP = $(UBOOT_STAGE1_OBJTOP)"
	$(CC) ${ASFLAGS} -c -o $@ spi-boot-start.S

$(obj)spi-boot.o: spi-boot.c depend
	$(CC) ${CFLAGS} -c -o $@ $(SPI_SRCS)

$(obj)spi-boot.bin: $(obj)spi-boot.elf
	$(OBJCOPY) $^ -R .MIPS.options -O binary $@

depend:	.depend

.depend: $(SPI_SRCS)
	rm -f ./.depend
	$(CC) -MM -I. -I../stage1-common $^ > ./.depend

include .depend

.PHONY: clean
clean:
	rm -f *.bin *.elf *.o *.map

distclean:
	rm -f *.bin *.elf *.o *.map .depend

tftp: /tftpboot/spi-boot.bin

/tftpboot/spi-boot.bin: spi-boot.bin
	cp $^ $@

# DO NOT DELETE
