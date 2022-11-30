	.file	"led.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0_a2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.globl	main
	.type	main, @function
main:
.LFB0:
	.file 1 "src/led.c"
	.loc 1 14 1
	.cfi_startproc
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 16 2
	.loc 1 16 47 is_stmt 0
	li	a5,268509184
	lw	a4,56(a5)
	andi	a4,a4,-33
	sw	a4,56(a5)
	.loc 1 17 2 is_stmt 1
	.loc 1 17 46 is_stmt 0
	lw	a4,4(a5)
	andi	a4,a4,-33
	sw	a4,4(a5)
	.loc 1 18 2 is_stmt 1
	.loc 1 18 46 is_stmt 0
	lw	a4,8(a5)
	ori	a4,a4,32
	sw	a4,8(a5)
	.loc 1 19 2 is_stmt 1
	.loc 1 19 46 is_stmt 0
	lw	a4,12(a5)
	ori	a4,a4,32
	sw	a4,12(a5)
	.loc 1 21 2 is_stmt 1
	.loc 1 21 20 is_stmt 0
	sw	zero,12(sp)
	j	.L6
.L8:
	.loc 1 29 3 is_stmt 1
	.loc 1 29 47 is_stmt 0
	li	a4,268509184
	lw	a5,12(a4)
	ori	a5,a5,32
	sw	a5,12(a4)
	.loc 1 30 3 is_stmt 1
	.loc 1 30 10 is_stmt 0
	sw	zero,12(sp)
.L4:
	.loc 1 30 17 discriminator 1
	lw	a4,12(sp)
	.loc 1 30 3 discriminator 1
	li	a5,184320
	addi	a5,a5,-111
	bleu	a4,a5,.L5
.L6:
	.loc 1 22 2 is_stmt 1
	.loc 1 25 3
	.loc 1 25 47 is_stmt 0
	li	a4,268509184
	lw	a5,12(a4)
	andi	a5,a5,-33
	sw	a5,12(a4)
	.loc 1 27 4 is_stmt 1
	.loc 1 27 11 is_stmt 0
	sw	zero,12(sp)
.L2:
	.loc 1 27 18 discriminator 1
	lw	a4,12(sp)
	.loc 1 27 4 discriminator 1
	li	a5,184320
	addi	a5,a5,-111
	bgtu	a4,a5,.L8
	.loc 1 27 33 is_stmt 1 discriminator 3
	.loc 1 27 29 is_stmt 0 discriminator 3
	lw	a5,12(sp)
	addi	a5,a5,1
	sw	a5,12(sp)
	j	.L2
.L5:
	.loc 1 30 32 is_stmt 1 discriminator 3
	.loc 1 30 28 is_stmt 0 discriminator 3
	lw	a5,12(sp)
	addi	a5,a5,1
	sw	a5,12(sp)
	j	.L4
	.cfi_endproc
.LFE0:
	.size	main, .-main
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x69
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.byte	0x1
	.4byte	.LASF1
	.byte	0xc
	.4byte	.LASF2
	.4byte	.LASF3
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.byte	0x2
	.4byte	.LASF4
	.byte	0x1
	.byte	0x1
	.byte	0x16
	.4byte	0x36
	.byte	0x3
	.4byte	0x25
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.byte	0x5
	.4byte	.LASF5
	.byte	0x1
	.byte	0xd
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.4byte	0x65
	.byte	0x6
	.string	"i"
	.byte	0x1
	.byte	0x15
	.byte	0x14
	.4byte	0x31
	.byte	0x2
	.byte	0x91
	.byte	0x7c
	.byte	0
	.byte	0x7
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0x1b
	.byte	0xe
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x10
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x35
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x6
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF0:
	.string	"unsigned int"
.LASF2:
	.string	"src/led.c"
.LASF5:
	.string	"main"
.LASF3:
	.string	"/home/dubsky/embedded/workspace/led"
.LASF4:
	.string	"uint32_t"
.LASF1:
	.string	"GNU C17 8.3.0 -march=rv32imac -mabi=ilp32 -mcmodel=medlow -g2 -ggdb2 -Og -fno-builtin-printf"
	.ident	"GCC: (SiFive GCC 8.3.0-2019.08.0) 8.3.0"
