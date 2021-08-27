
build/blink.elf:     file format elf32-littleriscv


Disassembly of section .init:

80000000 <_start>:

_start:
#ifdef USE_GP
.option push
.option norelax
	la gp, __global_pointer$
80000000:	00001197          	auipc	gp,0x1
80000004:	92018193          	addi	gp,gp,-1760 # 80000920 <__global_pointer$>
.option pop
#endif
	la sp, _sp
80000008:	c1018113          	addi	sp,gp,-1008 # 80000530 <_sp>


	/* Load data section */
	la a0, _data_lma
8000000c:	81018513          	addi	a0,gp,-2032 # 80000130 <__init_array_end>
	la a1, _data
80000010:	81018593          	addi	a1,gp,-2032 # 80000130 <__init_array_end>
	la a2, _edata
80000014:	81018613          	addi	a2,gp,-2032 # 80000130 <__init_array_end>
	bgeu a1, a2, 2f
80000018:	00c5fc63          	bleu	a2,a1,80000030 <_start+0x30>
1:
	lw t0, (a0)
8000001c:	00052283          	lw	t0,0(a0)
	sw t0, (a1)
80000020:	0055a023          	sw	t0,0(a1)
	addi a0, a0, 4
80000024:	00450513          	addi	a0,a0,4
	addi a1, a1, 4
80000028:	00458593          	addi	a1,a1,4
	bltu a1, a2, 1b
8000002c:	fec5e8e3          	bltu	a1,a2,8000001c <_start+0x1c>
2:

	/* Clear bss section */
	la a0, __bss_start
80000030:	81018513          	addi	a0,gp,-2032 # 80000130 <__init_array_end>
	la a1, _end
80000034:	81018593          	addi	a1,gp,-2032 # 80000130 <__init_array_end>
	bgeu a0, a1, 2f
80000038:	00b57863          	bleu	a1,a0,80000048 <_start+0x48>
1:
	sw zero, (a0)
8000003c:	00052023          	sw	zero,0(a0)
	addi a0, a0, 4
80000040:	00450513          	addi	a0,a0,4
	bltu a0, a1, 1b
80000044:	feb56ce3          	bltu	a0,a1,8000003c <_start+0x3c>
2:

	call __libc_init_array
80000048:	060000ef          	jal	ra,800000a8 <__libc_init_array>
	call main
8000004c:	028000ef          	jal	ra,80000074 <main>

80000050 <mainDone>:
mainDone:
    j mainDone
80000050:	0000006f          	j	80000050 <mainDone>

80000054 <_init>:


	.globl _init
_init:
    ret
80000054:	00008067          	ret

Disassembly of section .text:

80000058 <delay>:
#include <stdlib.h>

#include "dupin.h"
void delay()
{
	for(uint32_t idx = 0;idx < 5000000;idx++) asm volatile("");
80000058:	00000713          	li	a4,0
8000005c:	0080006f          	j	80000064 <delay+0xc>
80000060:	00170713          	addi	a4,a4,1
80000064:	004c57b7          	lui	a5,0x4c5
80000068:	b3f78793          	addi	a5,a5,-1217 # 4c4b3f <__stack_size+0x4c473f>
8000006c:	fee7fae3          	bleu	a4,a5,80000060 <delay+0x8>
}
80000070:	00008067          	ret

80000074 <main>:

void main() {
80000074:	ff010113          	addi	sp,sp,-16
80000078:	00112623          	sw	ra,12(sp)
	// Set GPIO LSB as outputs
    GPIO1->OUTPUT_ENABLE = 0x0000000F;
8000007c:	100507b7          	lui	a5,0x10050
80000080:	00f00713          	li	a4,15
80000084:	00e7a423          	sw	a4,8(a5) # 10050008 <__stack_size+0x1004fc08>

	// Set initial value of GPIO
    GPIO1->OUTPUT = 0x00000005;
80000088:	00500713          	li	a4,5
8000008c:	00e7a223          	sw	a4,4(a5)

	while(1)
	{
		GPIO1->OUTPUT ^= 0x0000000F;
80000090:	10050737          	lui	a4,0x10050
80000094:	00472783          	lw	a5,4(a4) # 10050004 <__stack_size+0x1004fc04>
80000098:	00f7c793          	xori	a5,a5,15
8000009c:	00f72223          	sw	a5,4(a4)
        delay();
800000a0:	fb9ff0ef          	jal	ra,80000058 <delay>
800000a4:	fedff06f          	j	80000090 <main+0x1c>

800000a8 <__libc_init_array>:
800000a8:	ff010113          	addi	sp,sp,-16
800000ac:	00812423          	sw	s0,8(sp)
800000b0:	00912223          	sw	s1,4(sp)
800000b4:	81018413          	addi	s0,gp,-2032 # 80000130 <__init_array_end>
800000b8:	81018493          	addi	s1,gp,-2032 # 80000130 <__init_array_end>
800000bc:	408484b3          	sub	s1,s1,s0
800000c0:	01212023          	sw	s2,0(sp)
800000c4:	00112623          	sw	ra,12(sp)
800000c8:	4024d493          	srai	s1,s1,0x2
800000cc:	00000913          	li	s2,0
800000d0:	02991c63          	bne	s2,s1,80000108 <__libc_init_array+0x60>
800000d4:	81018413          	addi	s0,gp,-2032 # 80000130 <__init_array_end>
800000d8:	81018493          	addi	s1,gp,-2032 # 80000130 <__init_array_end>
800000dc:	408484b3          	sub	s1,s1,s0
800000e0:	f75ff0ef          	jal	ra,80000054 <_init>
800000e4:	4024d493          	srai	s1,s1,0x2
800000e8:	00000913          	li	s2,0
800000ec:	02991863          	bne	s2,s1,8000011c <__libc_init_array+0x74>
800000f0:	00c12083          	lw	ra,12(sp)
800000f4:	00812403          	lw	s0,8(sp)
800000f8:	00412483          	lw	s1,4(sp)
800000fc:	00012903          	lw	s2,0(sp)
80000100:	01010113          	addi	sp,sp,16
80000104:	00008067          	ret
80000108:	00042783          	lw	a5,0(s0)
8000010c:	00190913          	addi	s2,s2,1
80000110:	00440413          	addi	s0,s0,4
80000114:	000780e7          	jalr	a5
80000118:	fb9ff06f          	j	800000d0 <__libc_init_array+0x28>
8000011c:	00042783          	lw	a5,0(s0)
80000120:	00190913          	addi	s2,s2,1
80000124:	00440413          	addi	s0,s0,4
80000128:	000780e7          	jalr	a5
8000012c:	fc1ff06f          	j	800000ec <__libc_init_array+0x44>
