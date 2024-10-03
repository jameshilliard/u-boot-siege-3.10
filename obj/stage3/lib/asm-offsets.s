	.section .mdebug.abiN32
	.previous
	.abicalls
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
	.section	.text.main,"ax",@progbits
	.align	2
	.globl	main
.LFB198:
	.file 1 "/homes/markli/u-boot-siege-git/u-boot/lib/asm-offsets.c"
	.loc 1 20 0
	.ent	main
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.loc 1 22 0
 #APP
	
->GENERATED_GBL_DATA_SIZE 352 (sizeof(struct global_data) + 15) & ~15
	.loc 1 25 0
	
->GENERATED_BD_INFO_SIZE 80 (sizeof(struct bd_info) + 15) & ~15
	.loc 1 28 0
	
->GD_SIZE 352 sizeof(struct global_data)
	.loc 1 30 0
	
->GD_BD 0 offsetof(struct global_data, bd)
	.loc 1 43 0
 #NO_APP
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0
	.set	macro
	.set	reorder

	.end	main
.LFE198:
	.size	main, .-main
	.section	.debug_frame,"",@progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.byte	0x1f
	.byte	0xc
	.uleb128 0x1d
	.uleb128 0x0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB198
	.4byte	.LFE198-.LFB198
	.align	2
.LEFDE0:
	.align	0
	.text
.Letext0:
	.file 2 "/homes/markli/u-boot-siege-git/u-boot/include/common.h"
	.file 3 "/homes/markli/u-boot-siege-git/u-boot/obj/stage3/include2/asm/types.h"
	.file 4 "/homes/markli/u-boot-siege-git/u-boot/include/linux/types.h"
	.file 5 "/homes/markli/u-boot-siege-git/u-boot/obj/stage3/include2/asm/u-boot.h"
	.file 6 "/homes/markli/u-boot-siege-git/u-boot/obj/stage3/include2/asm/arch/octeon_eeprom_types.h"
	.file 7 "/homes/markli/u-boot-siege-git/u-boot/obj/stage3/include2/asm/global_data.h"
	.file 8 "/homes/markli/u-boot-siege-git/u-boot/include/asm-generic/global_data.h"
	.file 9 "/homes/markli/u-boot-siege-git/u-boot/include/net.h"
	.file 10 "/homes/markli/u-boot-siege-git/u-boot/obj/stage3/include2/asm/u-boot-mips.h"
	.section	.debug_info
	.4byte	0x9a6
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x1
	.4byte	.LASF159
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF3
	.byte	0x2
	.byte	0x10
	.4byte	0x24
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x2
	.4byte	.LASF4
	.byte	0x3
	.byte	0x15
	.4byte	0x44
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF5
	.uleb128 0x2
	.4byte	.LASF6
	.byte	0x3
	.byte	0x16
	.4byte	0x24
	.uleb128 0x2
	.4byte	.LASF7
	.byte	0x3
	.byte	0x18
	.4byte	0x61
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x2
	.4byte	.LASF9
	.byte	0x3
	.byte	0x19
	.4byte	0x32
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.4byte	.LASF10
	.byte	0x3
	.byte	0x1c
	.4byte	0x85
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF12
	.uleb128 0x2
	.4byte	.LASF13
	.byte	0x3
	.byte	0x27
	.4byte	0x9e
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF14
	.uleb128 0x5
	.ascii	"u64\000"
	.byte	0x3
	.byte	0x49
	.4byte	0x9e
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x3
	.byte	0x53
	.4byte	0xa5
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF16
	.uleb128 0x7
	.byte	0x4
	.4byte	0xcb
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF17
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x4
	.byte	0x59
	.4byte	0x2b
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x4
	.byte	0x5f
	.4byte	0x39
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x4
	.byte	0x61
	.4byte	0x56
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x4
	.byte	0x67
	.4byte	0x4b
	.uleb128 0x2
	.4byte	.LASF22
	.byte	0x4
	.byte	0x68
	.4byte	0x68
	.uleb128 0x2
	.4byte	.LASF23
	.byte	0x4
	.byte	0x69
	.4byte	0x7a
	.uleb128 0x2
	.4byte	.LASF24
	.byte	0x4
	.byte	0x6c
	.4byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 0x7
	.byte	0x4
	.4byte	0x127
	.uleb128 0x9
	.uleb128 0xa
	.4byte	.LASF47
	.byte	0x50
	.byte	0x5
	.byte	0x19
	.4byte	0x215
	.uleb128 0xb
	.4byte	.LASF25
	.byte	0x5
	.byte	0x1a
	.4byte	0x85
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.4byte	.LASF26
	.byte	0x5
	.byte	0x1b
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0xb
	.4byte	.LASF27
	.byte	0x5
	.byte	0x1d
	.4byte	0x215
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF28
	.byte	0x5
	.byte	0x1f
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0xb
	.4byte	.LASF29
	.byte	0x5
	.byte	0x20
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x14
	.uleb128 0xb
	.4byte	.LASF30
	.byte	0x5
	.byte	0x25
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0xc
	.ascii	"pad\000"
	.byte	0x5
	.byte	0x26
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.uleb128 0xb
	.4byte	.LASF31
	.byte	0x5
	.byte	0x28
	.4byte	0xb0
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0xb
	.4byte	.LASF32
	.byte	0x5
	.byte	0x2c
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x28
	.uleb128 0xb
	.4byte	.LASF33
	.byte	0x5
	.byte	0x2d
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x2c
	.uleb128 0xb
	.4byte	.LASF34
	.byte	0x5
	.byte	0x35
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x30
	.uleb128 0xb
	.4byte	.LASF35
	.byte	0x5
	.byte	0x37
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x34
	.uleb128 0xb
	.4byte	.LASF36
	.byte	0x5
	.byte	0x38
	.4byte	0x114
	.byte	0x2
	.byte	0x10
	.uleb128 0x38
	.uleb128 0xb
	.4byte	.LASF37
	.byte	0x5
	.byte	0x3a
	.4byte	0xd2
	.byte	0x2
	.byte	0x10
	.uleb128 0x40
	.uleb128 0xb
	.4byte	.LASF38
	.byte	0x5
	.byte	0x3c
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x44
	.uleb128 0xb
	.4byte	.LASF39
	.byte	0x5
	.byte	0x3d
	.4byte	0x109
	.byte	0x2
	.byte	0x10
	.uleb128 0x48
	.byte	0x0
	.uleb128 0xd
	.4byte	0x24
	.4byte	0x225
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x5
	.byte	0x0
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x5
	.byte	0x3f
	.4byte	0x128
	.uleb128 0x7
	.byte	0x4
	.4byte	0x225
	.uleb128 0xf
	.byte	0x8
	.byte	0x6
	.byte	0x6a
	.4byte	0x285
	.uleb128 0xb
	.4byte	.LASF41
	.byte	0x6
	.byte	0x6b
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.4byte	.LASF42
	.byte	0x6
	.byte	0x6c
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0x2
	.uleb128 0xb
	.4byte	.LASF43
	.byte	0x6
	.byte	0x6d
	.4byte	0xf3
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0xb
	.4byte	.LASF44
	.byte	0x6
	.byte	0x70
	.4byte	0xf3
	.byte	0x2
	.byte	0x10
	.uleb128 0x5
	.uleb128 0xb
	.4byte	.LASF45
	.byte	0x6
	.byte	0x73
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0x6
	.byte	0x0
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x6
	.byte	0x74
	.4byte	0x236
	.uleb128 0xa
	.4byte	.LASF48
	.byte	0x10
	.byte	0x6
	.byte	0x91
	.4byte	0x2e3
	.uleb128 0xb
	.4byte	.LASF49
	.byte	0x6
	.byte	0x92
	.4byte	0x285
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.4byte	.LASF50
	.byte	0x6
	.byte	0x93
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF51
	.byte	0x6
	.byte	0x94
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0xa
	.uleb128 0xb
	.4byte	.LASF52
	.byte	0x6
	.byte	0x95
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0xb
	.4byte	.LASF53
	.byte	0x6
	.byte	0x96
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0xe
	.byte	0x0
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0x6
	.byte	0xa1
	.4byte	0x290
	.uleb128 0xa
	.4byte	.LASF55
	.byte	0x24
	.byte	0x6
	.byte	0xb1
	.4byte	0x36b
	.uleb128 0xb
	.4byte	.LASF49
	.byte	0x6
	.byte	0xb2
	.4byte	0x285
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.4byte	.LASF56
	.byte	0x6
	.byte	0xb3
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF57
	.byte	0x6
	.byte	0xb4
	.4byte	0xf3
	.byte	0x2
	.byte	0x10
	.uleb128 0xa
	.uleb128 0xb
	.4byte	.LASF58
	.byte	0x6
	.byte	0xb5
	.4byte	0xf3
	.byte	0x2
	.byte	0x10
	.uleb128 0xb
	.uleb128 0xb
	.4byte	.LASF59
	.byte	0x6
	.byte	0xb6
	.4byte	0xfe
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0xb
	.4byte	.LASF60
	.byte	0x6
	.byte	0xb7
	.4byte	0xf3
	.byte	0x2
	.byte	0x10
	.uleb128 0xe
	.uleb128 0xb
	.4byte	.LASF61
	.byte	0x6
	.byte	0xb8
	.4byte	0xf3
	.byte	0x2
	.byte	0x10
	.uleb128 0xf
	.uleb128 0xb
	.4byte	.LASF62
	.byte	0x6
	.byte	0xb9
	.4byte	0x36b
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.byte	0x0
	.uleb128 0xd
	.4byte	0xf3
	.4byte	0x37b
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x13
	.byte	0x0
	.uleb128 0x2
	.4byte	.LASF63
	.byte	0x6
	.byte	0xbd
	.4byte	0x2ee
	.uleb128 0x10
	.4byte	.LASF64
	.byte	0x10
	.byte	0x6
	.2byte	0x105
	.4byte	0x3c1
	.uleb128 0x11
	.4byte	.LASF49
	.byte	0x6
	.2byte	0x106
	.4byte	0x285
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0x11
	.4byte	.LASF65
	.byte	0x6
	.2byte	0x107
	.4byte	0x3c1
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0x11
	.4byte	.LASF66
	.byte	0x6
	.2byte	0x108
	.4byte	0xf3
	.byte	0x2
	.byte	0x10
	.uleb128 0xe
	.byte	0x0
	.uleb128 0xd
	.4byte	0xf3
	.4byte	0x3d1
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x5
	.byte	0x0
	.uleb128 0x12
	.4byte	.LASF67
	.byte	0x6
	.2byte	0x10c
	.4byte	0x386
	.uleb128 0xa
	.4byte	.LASF68
	.byte	0x10
	.byte	0x7
	.byte	0x41
	.4byte	0x421
	.uleb128 0xb
	.4byte	.LASF69
	.byte	0x7
	.byte	0x42
	.4byte	0x114
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.4byte	.LASF70
	.byte	0x7
	.byte	0x43
	.4byte	0x73
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF71
	.byte	0x7
	.byte	0x44
	.4byte	0xe8
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0xc
	.ascii	"id\000"
	.byte	0x7
	.byte	0x45
	.4byte	0xe8
	.byte	0x2
	.byte	0x10
	.uleb128 0xe
	.byte	0x0
	.uleb128 0xa
	.4byte	.LASF72
	.byte	0xd8
	.byte	0x7
	.byte	0x48
	.4byte	0x599
	.uleb128 0xb
	.4byte	.LASF73
	.byte	0x7
	.byte	0x4c
	.4byte	0x37b
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.4byte	.LASF74
	.byte	0x7
	.byte	0x4d
	.4byte	0x2e3
	.byte	0x2
	.byte	0x10
	.uleb128 0x24
	.uleb128 0xb
	.4byte	.LASF75
	.byte	0x7
	.byte	0x4e
	.4byte	0x3d1
	.byte	0x2
	.byte	0x10
	.uleb128 0x34
	.uleb128 0xb
	.4byte	.LASF76
	.byte	0x7
	.byte	0x50
	.4byte	0x599
	.byte	0x2
	.byte	0x10
	.uleb128 0x44
	.uleb128 0xb
	.4byte	.LASF77
	.byte	0x7
	.byte	0x52
	.4byte	0x109
	.byte	0x2
	.byte	0x10
	.uleb128 0x54
	.uleb128 0xb
	.4byte	.LASF78
	.byte	0x7
	.byte	0x53
	.4byte	0x109
	.byte	0x2
	.byte	0x10
	.uleb128 0x58
	.uleb128 0xb
	.4byte	.LASF79
	.byte	0x7
	.byte	0x54
	.4byte	0x109
	.byte	0x2
	.byte	0x10
	.uleb128 0x5c
	.uleb128 0xb
	.4byte	.LASF80
	.byte	0x7
	.byte	0x55
	.4byte	0x114
	.byte	0x2
	.byte	0x10
	.uleb128 0x60
	.uleb128 0xb
	.4byte	.LASF81
	.byte	0x7
	.byte	0x57
	.4byte	0xc5
	.byte	0x2
	.byte	0x10
	.uleb128 0x68
	.uleb128 0xb
	.4byte	.LASF82
	.byte	0x7
	.byte	0x59
	.4byte	0xd2
	.byte	0x2
	.byte	0x10
	.uleb128 0x6c
	.uleb128 0xb
	.4byte	.LASF83
	.byte	0x7
	.byte	0x5a
	.4byte	0xd2
	.byte	0x2
	.byte	0x10
	.uleb128 0x70
	.uleb128 0xb
	.4byte	.LASF84
	.byte	0x7
	.byte	0x5b
	.4byte	0x5a9
	.byte	0x2
	.byte	0x10
	.uleb128 0x74
	.uleb128 0xb
	.4byte	.LASF85
	.byte	0x7
	.byte	0x5c
	.4byte	0x109
	.byte	0x3
	.byte	0x10
	.uleb128 0x94
	.uleb128 0xb
	.4byte	.LASF86
	.byte	0x7
	.byte	0x5d
	.4byte	0x109
	.byte	0x3
	.byte	0x10
	.uleb128 0x98
	.uleb128 0xb
	.4byte	.LASF87
	.byte	0x7
	.byte	0x61
	.4byte	0xf3
	.byte	0x3
	.byte	0x10
	.uleb128 0x9c
	.uleb128 0xb
	.4byte	.LASF88
	.byte	0x7
	.byte	0x62
	.4byte	0xf3
	.byte	0x3
	.byte	0x10
	.uleb128 0x9d
	.uleb128 0xb
	.4byte	.LASF89
	.byte	0x7
	.byte	0x63
	.4byte	0xf3
	.byte	0x3
	.byte	0x10
	.uleb128 0x9e
	.uleb128 0xb
	.4byte	.LASF90
	.byte	0x7
	.byte	0x64
	.4byte	0xf3
	.byte	0x3
	.byte	0x10
	.uleb128 0x9f
	.uleb128 0xb
	.4byte	.LASF91
	.byte	0x7
	.byte	0x66
	.4byte	0x109
	.byte	0x3
	.byte	0x10
	.uleb128 0xa0
	.uleb128 0xb
	.4byte	.LASF92
	.byte	0x7
	.byte	0x6d
	.4byte	0x5b9
	.byte	0x3
	.byte	0x10
	.uleb128 0xa8
	.uleb128 0xb
	.4byte	.LASF93
	.byte	0x7
	.byte	0x6f
	.4byte	0xfe
	.byte	0x3
	.byte	0x10
	.uleb128 0xc8
	.uleb128 0xb
	.4byte	.LASF94
	.byte	0x7
	.byte	0x70
	.4byte	0xf3
	.byte	0x3
	.byte	0x10
	.uleb128 0xca
	.uleb128 0xb
	.4byte	.LASF95
	.byte	0x7
	.byte	0x71
	.4byte	0xdd
	.byte	0x3
	.byte	0x10
	.uleb128 0xcb
	.uleb128 0xb
	.4byte	.LASF96
	.byte	0x7
	.byte	0x72
	.4byte	0xf3
	.byte	0x3
	.byte	0x10
	.uleb128 0xcc
	.uleb128 0xb
	.4byte	.LASF97
	.byte	0x7
	.byte	0x7d
	.4byte	0x11f
	.byte	0x3
	.byte	0x10
	.uleb128 0xd0
	.byte	0x0
	.uleb128 0xd
	.4byte	0x109
	.4byte	0x5a9
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x3
	.byte	0x0
	.uleb128 0xd
	.4byte	0xcb
	.4byte	0x5b9
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x1d
	.byte	0x0
	.uleb128 0xd
	.4byte	0x3dd
	.4byte	0x5c9
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x1
	.byte	0x0
	.uleb128 0x13
	.4byte	.LASF98
	.2byte	0x160
	.byte	0x8
	.byte	0x18
	.4byte	0x743
	.uleb128 0xc
	.ascii	"bd\000"
	.byte	0x8
	.byte	0x19
	.4byte	0x230
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xc
	.ascii	"jt\000"
	.byte	0x8
	.byte	0x1b
	.4byte	0x743
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.uleb128 0xb
	.4byte	.LASF99
	.byte	0x8
	.byte	0x1d
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF100
	.byte	0x8
	.byte	0x1e
	.4byte	0x85
	.byte	0x2
	.byte	0x10
	.uleb128 0xc
	.uleb128 0xb
	.4byte	.LASF101
	.byte	0x8
	.byte	0x20
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0xb
	.4byte	.LASF102
	.byte	0x8
	.byte	0x21
	.4byte	0xb0
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0xb
	.4byte	.LASF103
	.byte	0x8
	.byte	0x22
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0xb
	.4byte	.LASF104
	.byte	0x8
	.byte	0x23
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x24
	.uleb128 0xb
	.4byte	.LASF105
	.byte	0x8
	.byte	0x24
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x28
	.uleb128 0xb
	.4byte	.LASF106
	.byte	0x8
	.byte	0x26
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x2c
	.uleb128 0xb
	.4byte	.LASF107
	.byte	0x8
	.byte	0x27
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x30
	.uleb128 0xb
	.4byte	.LASF108
	.byte	0x8
	.byte	0x29
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x34
	.uleb128 0xb
	.4byte	.LASF109
	.byte	0x8
	.byte	0x2a
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x38
	.uleb128 0xb
	.4byte	.LASF56
	.byte	0x8
	.byte	0x34
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x3c
	.uleb128 0xb
	.4byte	.LASF110
	.byte	0x8
	.byte	0x45
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x40
	.uleb128 0xb
	.4byte	.LASF111
	.byte	0x8
	.byte	0x47
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x44
	.uleb128 0xb
	.4byte	.LASF112
	.byte	0x8
	.byte	0x4b
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x48
	.uleb128 0xb
	.4byte	.LASF113
	.byte	0x8
	.byte	0x4c
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x4c
	.uleb128 0xb
	.4byte	.LASF114
	.byte	0x8
	.byte	0x4d
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x50
	.uleb128 0xb
	.4byte	.LASF115
	.byte	0x8
	.byte	0x51
	.4byte	0x749
	.byte	0x2
	.byte	0x10
	.uleb128 0x54
	.uleb128 0xb
	.4byte	.LASF116
	.byte	0x8
	.byte	0x52
	.4byte	0x121
	.byte	0x2
	.byte	0x10
	.uleb128 0x58
	.uleb128 0xb
	.4byte	.LASF117
	.byte	0x8
	.byte	0x53
	.4byte	0x11f
	.byte	0x2
	.byte	0x10
	.uleb128 0x5c
	.uleb128 0xb
	.4byte	.LASF118
	.byte	0x8
	.byte	0x54
	.4byte	0x2b
	.byte	0x2
	.byte	0x10
	.uleb128 0x60
	.uleb128 0xb
	.4byte	.LASF119
	.byte	0x8
	.byte	0x58
	.4byte	0x74f
	.byte	0x2
	.byte	0x10
	.uleb128 0x64
	.uleb128 0xb
	.4byte	.LASF120
	.byte	0x8
	.byte	0x5d
	.4byte	0x73
	.byte	0x3
	.byte	0x10
	.uleb128 0x84
	.uleb128 0xb
	.4byte	.LASF121
	.byte	0x8
	.byte	0x63
	.4byte	0x421
	.byte	0x3
	.byte	0x10
	.uleb128 0x88
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x11f
	.uleb128 0x7
	.byte	0x4
	.4byte	0x5c9
	.uleb128 0xd
	.4byte	0xcb
	.4byte	0x75f
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x1f
	.byte	0x0
	.uleb128 0xa
	.4byte	.LASF122
	.byte	0x40
	.byte	0x9
	.byte	0x51
	.4byte	0x814
	.uleb128 0xb
	.4byte	.LASF123
	.byte	0x9
	.byte	0x52
	.4byte	0x814
	.byte	0x2
	.byte	0x10
	.uleb128 0x0
	.uleb128 0xb
	.4byte	.LASF124
	.byte	0x9
	.byte	0x53
	.4byte	0x215
	.byte	0x2
	.byte	0x10
	.uleb128 0x10
	.uleb128 0xb
	.4byte	.LASF125
	.byte	0x9
	.byte	0x54
	.4byte	0x73
	.byte	0x2
	.byte	0x10
	.uleb128 0x18
	.uleb128 0xb
	.4byte	.LASF126
	.byte	0x9
	.byte	0x55
	.4byte	0x73
	.byte	0x2
	.byte	0x10
	.uleb128 0x1c
	.uleb128 0xb
	.4byte	.LASF127
	.byte	0x9
	.byte	0x57
	.4byte	0x83f
	.byte	0x2
	.byte	0x10
	.uleb128 0x20
	.uleb128 0xb
	.4byte	.LASF128
	.byte	0x9
	.byte	0x58
	.4byte	0x85f
	.byte	0x2
	.byte	0x10
	.uleb128 0x24
	.uleb128 0xb
	.4byte	.LASF129
	.byte	0x9
	.byte	0x59
	.4byte	0x875
	.byte	0x2
	.byte	0x10
	.uleb128 0x28
	.uleb128 0xb
	.4byte	.LASF130
	.byte	0x9
	.byte	0x5a
	.4byte	0x887
	.byte	0x2
	.byte	0x10
	.uleb128 0x2c
	.uleb128 0xb
	.4byte	.LASF131
	.byte	0x9
	.byte	0x5e
	.4byte	0x875
	.byte	0x2
	.byte	0x10
	.uleb128 0x30
	.uleb128 0xb
	.4byte	.LASF132
	.byte	0x9
	.byte	0x5f
	.4byte	0x839
	.byte	0x2
	.byte	0x10
	.uleb128 0x34
	.uleb128 0xb
	.4byte	.LASF133
	.byte	0x9
	.byte	0x60
	.4byte	0x73
	.byte	0x2
	.byte	0x10
	.uleb128 0x38
	.uleb128 0xb
	.4byte	.LASF134
	.byte	0x9
	.byte	0x61
	.4byte	0x11f
	.byte	0x2
	.byte	0x10
	.uleb128 0x3c
	.byte	0x0
	.uleb128 0xd
	.4byte	0xcb
	.4byte	0x824
	.uleb128 0xe
	.4byte	0xbb
	.byte	0xf
	.byte	0x0
	.uleb128 0x14
	.byte	0x1
	.4byte	0x73
	.4byte	0x839
	.uleb128 0x15
	.4byte	0x839
	.uleb128 0x15
	.4byte	0x230
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x75f
	.uleb128 0x7
	.byte	0x4
	.4byte	0x824
	.uleb128 0x14
	.byte	0x1
	.4byte	0x73
	.4byte	0x85f
	.uleb128 0x15
	.4byte	0x839
	.uleb128 0x15
	.4byte	0x11f
	.uleb128 0x15
	.4byte	0x73
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x845
	.uleb128 0x14
	.byte	0x1
	.4byte	0x73
	.4byte	0x875
	.uleb128 0x15
	.4byte	0x839
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x865
	.uleb128 0x16
	.byte	0x1
	.4byte	0x887
	.uleb128 0x15
	.4byte	0x839
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x87b
	.uleb128 0xd
	.4byte	0x19
	.4byte	0x89d
	.uleb128 0xe
	.4byte	0xbb
	.byte	0x5
	.byte	0x0
	.uleb128 0x17
	.4byte	.LASF145
	.byte	0x4
	.byte	0x9
	.2byte	0x1b6
	.4byte	0x8ff
	.uleb128 0x18
	.4byte	.LASF135
	.sleb128 0
	.uleb128 0x18
	.4byte	.LASF136
	.sleb128 1
	.uleb128 0x19
	.ascii	"ARP\000"
	.sleb128 2
	.uleb128 0x18
	.4byte	.LASF137
	.sleb128 3
	.uleb128 0x18
	.4byte	.LASF138
	.sleb128 4
	.uleb128 0x18
	.4byte	.LASF139
	.sleb128 5
	.uleb128 0x19
	.ascii	"DNS\000"
	.sleb128 6
	.uleb128 0x19
	.ascii	"NFS\000"
	.sleb128 7
	.uleb128 0x19
	.ascii	"CDP\000"
	.sleb128 8
	.uleb128 0x18
	.4byte	.LASF140
	.sleb128 9
	.uleb128 0x18
	.4byte	.LASF141
	.sleb128 10
	.uleb128 0x18
	.4byte	.LASF142
	.sleb128 11
	.uleb128 0x18
	.4byte	.LASF143
	.sleb128 12
	.uleb128 0x18
	.4byte	.LASF144
	.sleb128 13
	.byte	0x0
	.uleb128 0x17
	.4byte	.LASF146
	.byte	0x4
	.byte	0x9
	.2byte	0x203
	.4byte	0x925
	.uleb128 0x18
	.4byte	.LASF147
	.sleb128 0
	.uleb128 0x18
	.4byte	.LASF148
	.sleb128 1
	.uleb128 0x18
	.4byte	.LASF149
	.sleb128 2
	.uleb128 0x18
	.4byte	.LASF150
	.sleb128 3
	.byte	0x0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF160
	.byte	0x1
	.byte	0x14
	.byte	0x1
	.4byte	0x73
	.4byte	.LFB198
	.4byte	.LFE198
	.4byte	.LSFDE0
	.byte	0x1
	.byte	0x6d
	.uleb128 0x1b
	.byte	0x1
	.4byte	0xcb
	.uleb128 0x1c
	.4byte	.LASF151
	.byte	0xa
	.byte	0x9
	.4byte	0x940
	.byte	0x1
	.byte	0x1
	.uleb128 0x1c
	.4byte	.LASF152
	.byte	0xa
	.byte	0xf
	.4byte	0xd2
	.byte	0x1
	.byte	0x1
	.uleb128 0x1c
	.4byte	.LASF153
	.byte	0xa
	.byte	0x15
	.4byte	0x940
	.byte	0x1
	.byte	0x1
	.uleb128 0x1c
	.4byte	.LASF154
	.byte	0x9
	.byte	0x6b
	.4byte	0x839
	.byte	0x1
	.byte	0x1
	.uleb128 0x1d
	.4byte	.LASF155
	.byte	0x9
	.2byte	0x1d1
	.4byte	0x988
	.byte	0x1
	.byte	0x1
	.uleb128 0x1e
	.4byte	0x88d
	.uleb128 0x1d
	.4byte	.LASF156
	.byte	0x9
	.2byte	0x209
	.4byte	0x8ff
	.byte	0x1
	.byte	0x1
	.uleb128 0x1d
	.4byte	.LASF157
	.byte	0x9
	.2byte	0x23b
	.4byte	0x89d
	.byte	0x1
	.byte	0x1
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x16
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x17
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x19
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x2001
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1b
	.uleb128 0x1
	.byte	0x0
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x1e
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.4byte	0x17
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x9aa
	.4byte	0x925
	.ascii	"main\000"
	.4byte	0x0
	.section	.debug_aranges,"",@progbits
	.4byte	0x24
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.LFB198
	.4byte	.LFE198-.LFB198
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF66:
	.ascii	"count\000"
.LASF18:
	.ascii	"ulong\000"
.LASF29:
	.ascii	"bi_boot_params\000"
.LASF145:
	.ascii	"proto_t\000"
.LASF150:
	.ascii	"NETLOOP_FAIL\000"
.LASF31:
	.ascii	"bi_memsize\000"
.LASF45:
	.ascii	"checksum\000"
.LASF24:
	.ascii	"uint64_t\000"
.LASF50:
	.ascii	"ddr_clock_mhz\000"
.LASF65:
	.ascii	"mac_addr_base\000"
.LASF71:
	.ascii	"bus_num\000"
.LASF148:
	.ascii	"NETLOOP_RESTART\000"
.LASF41:
	.ascii	"type\000"
.LASF127:
	.ascii	"init\000"
.LASF108:
	.ascii	"pci_clk\000"
.LASF4:
	.ascii	"__s8\000"
.LASF14:
	.ascii	"long long unsigned int\000"
.LASF124:
	.ascii	"enetaddr\000"
.LASF9:
	.ascii	"__u16\000"
.LASF34:
	.ascii	"bi_uboot_ram_used_size\000"
.LASF157:
	.ascii	"net_loop_last_protocol\000"
.LASF53:
	.ascii	"spi_clock_mhz\000"
.LASF54:
	.ascii	"octeon_eeprom_clock_desc_t\000"
.LASF132:
	.ascii	"next\000"
.LASF103:
	.ascii	"reloc_off\000"
.LASF79:
	.ascii	"ddr_alt_ref_MHz\000"
.LASF97:
	.ascii	"api_sig_addr\000"
.LASF137:
	.ascii	"TFTPGET\000"
.LASF102:
	.ascii	"ram_size\000"
.LASF20:
	.ascii	"int16_t\000"
.LASF92:
	.ascii	"i2c_busses\000"
.LASF12:
	.ascii	"long long int\000"
.LASF5:
	.ascii	"signed char\000"
.LASF135:
	.ascii	"BOOTP\000"
.LASF28:
	.ascii	"bi_arch_number\000"
.LASF89:
	.ascii	"mcu_rev_maj\000"
.LASF126:
	.ascii	"state\000"
.LASF119:
	.ascii	"env_buf\000"
.LASF16:
	.ascii	"long int\000"
.LASF81:
	.ascii	"err_msg\000"
.LASF90:
	.ascii	"mcu_rev_min\000"
.LASF129:
	.ascii	"recv\000"
.LASF72:
	.ascii	"arch_global_data\000"
.LASF22:
	.ascii	"uint16_t\000"
.LASF73:
	.ascii	"board_desc\000"
.LASF76:
	.ascii	"ram_sizes\000"
.LASF149:
	.ascii	"NETLOOP_SUCCESS\000"
.LASF144:
	.ascii	"LINKLOCAL\000"
.LASF109:
	.ascii	"mem_clk\000"
.LASF82:
	.ascii	"uboot_flash_address\000"
.LASF94:
	.ascii	"current_i2c_mux_bus\000"
.LASF32:
	.ascii	"bi_flashstart\000"
.LASF11:
	.ascii	"unsigned int\000"
.LASF40:
	.ascii	"bd_t\000"
.LASF116:
	.ascii	"fdt_blob\000"
.LASF6:
	.ascii	"__u8\000"
.LASF1:
	.ascii	"long unsigned int\000"
.LASF10:
	.ascii	"__u32\000"
.LASF152:
	.ascii	"__bss_end\000"
.LASF123:
	.ascii	"name\000"
.LASF60:
	.ascii	"chip_rev_major\000"
.LASF96:
	.ascii	"i2c_initialized\000"
.LASF37:
	.ascii	"bi_bootflags\000"
.LASF2:
	.ascii	"short unsigned int\000"
.LASF113:
	.ascii	"irq_sp\000"
.LASF48:
	.ascii	"octeon_eeprom_clock_desc_v2\000"
.LASF105:
	.ascii	"env_valid\000"
.LASF121:
	.ascii	"arch\000"
.LASF151:
	.ascii	"__bss_start\000"
.LASF106:
	.ascii	"cpu_clk\000"
.LASF55:
	.ascii	"octeon_eeprom_board_desc_v1\000"
.LASF70:
	.ascii	"node\000"
.LASF26:
	.ascii	"bi_ip_addr\000"
.LASF153:
	.ascii	"__image_copy_end\000"
.LASF141:
	.ascii	"SNTP\000"
.LASF27:
	.ascii	"bi_enetaddr\000"
.LASF146:
	.ascii	"net_loop_state\000"
.LASF7:
	.ascii	"__s16\000"
.LASF118:
	.ascii	"fdt_size\000"
.LASF104:
	.ascii	"env_addr\000"
.LASF93:
	.ascii	"ddr_int_initialized\000"
.LASF101:
	.ascii	"have_console\000"
.LASF120:
	.ascii	"cur_i2c_bus\000"
.LASF68:
	.ascii	"octeon_i2c_bus\000"
.LASF154:
	.ascii	"eth_current\000"
.LASF77:
	.ascii	"console_uart\000"
.LASF87:
	.ascii	"tlv_addr\000"
.LASF25:
	.ascii	"bi_baudrate\000"
.LASF64:
	.ascii	"octeon_eeprom_mac_addr_v1\000"
.LASF128:
	.ascii	"send\000"
.LASF47:
	.ascii	"bd_info\000"
.LASF35:
	.ascii	"bi_i2c_id\000"
.LASF59:
	.ascii	"chip_type\000"
.LASF85:
	.ascii	"flash_base_address\000"
.LASF158:
	.ascii	"GNU C 4.2.1 (for JUNOS) -g\000"
.LASF3:
	.ascii	"uchar\000"
.LASF134:
	.ascii	"priv\000"
.LASF57:
	.ascii	"rev_major\000"
.LASF156:
	.ascii	"net_state\000"
.LASF39:
	.ascii	"bi_uboot_map_size\000"
.LASF143:
	.ascii	"TFTPPUT\000"
.LASF91:
	.ascii	"pal_addr\000"
.LASF136:
	.ascii	"RARP\000"
.LASF125:
	.ascii	"iobase\000"
.LASF0:
	.ascii	"unsigned char\000"
.LASF111:
	.ascii	"relocaddr\000"
.LASF8:
	.ascii	"short int\000"
.LASF44:
	.ascii	"major_version\000"
.LASF159:
	.ascii	"/homes/markli/u-boot-siege-git/u-boot/lib/asm-offsets.c\000"
.LASF142:
	.ascii	"TFTPSRV\000"
.LASF131:
	.ascii	"write_hwaddr\000"
.LASF58:
	.ascii	"rev_minor\000"
.LASF51:
	.ascii	"cpu_ref_clock_mhz_x_8\000"
.LASF63:
	.ascii	"octeon_eeprom_board_desc_t\000"
.LASF56:
	.ascii	"board_type\000"
.LASF100:
	.ascii	"baudrate\000"
.LASF23:
	.ascii	"uint32_t\000"
.LASF69:
	.ascii	"regs\000"
.LASF13:
	.ascii	"__u64\000"
.LASF80:
	.ascii	"dfm_ram_size\000"
.LASF88:
	.ascii	"node_mask\000"
.LASF17:
	.ascii	"char\000"
.LASF61:
	.ascii	"chip_rev_minor\000"
.LASF33:
	.ascii	"bi_flashsize\000"
.LASF74:
	.ascii	"clock_desc\000"
.LASF133:
	.ascii	"index\000"
.LASF98:
	.ascii	"global_data\000"
.LASF140:
	.ascii	"NETCONS\000"
.LASF83:
	.ascii	"uboot_flash_size\000"
.LASF114:
	.ascii	"start_addr_sp\000"
.LASF78:
	.ascii	"ddr_ref_hertz\000"
.LASF117:
	.ascii	"new_fdt\000"
.LASF46:
	.ascii	"octeon_eeprom_header_t\000"
.LASF84:
	.ascii	"tmp_str\000"
.LASF19:
	.ascii	"int8_t\000"
.LASF86:
	.ascii	"flash_size\000"
.LASF147:
	.ascii	"NETLOOP_CONTINUE\000"
.LASF107:
	.ascii	"bus_clk\000"
.LASF139:
	.ascii	"PING\000"
.LASF15:
	.ascii	"phys_size_t\000"
.LASF67:
	.ascii	"octeon_eeprom_mac_addr_t\000"
.LASF110:
	.ascii	"ram_top\000"
.LASF30:
	.ascii	"bi_memstart\000"
.LASF21:
	.ascii	"uint8_t\000"
.LASF62:
	.ascii	"serial_str\000"
.LASF112:
	.ascii	"mon_len\000"
.LASF43:
	.ascii	"minor_version\000"
.LASF99:
	.ascii	"flags\000"
.LASF42:
	.ascii	"length\000"
.LASF130:
	.ascii	"halt\000"
.LASF138:
	.ascii	"DHCP\000"
.LASF36:
	.ascii	"bi_uboot_ram_addr\000"
.LASF155:
	.ascii	"NetCDPAddr\000"
.LASF122:
	.ascii	"eth_device\000"
.LASF52:
	.ascii	"dfa_ref_clock_mhz_x_8\000"
.LASF95:
	.ascii	"num_i2c_busses\000"
.LASF115:
	.ascii	"new_gd\000"
.LASF160:
	.ascii	"main\000"
.LASF75:
	.ascii	"mac_desc\000"
.LASF38:
	.ascii	"bi_flashoffset\000"
.LASF49:
	.ascii	"header\000"
	.ident	"GCC: (GNU) 4.2.1 (for JUNOS)"
