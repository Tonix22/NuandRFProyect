
build/blink.elf:     file format elf32-littleriscv


Disassembly of section .init:

80000000 <_start>:

_start:
#ifdef USE_GP
.option push
.option norelax
	la gp, __global_pointer$
80000000:	00001197          	auipc	gp,0x1
80000004:	af018193          	addi	gp,gp,-1296 # 80000af0 <__global_pointer$>
.option pop
#endif
	la sp, _sp
80000008:	c1018113          	addi	sp,gp,-1008 # 80000700 <_sp>


	/* Load data section */
	la a0, _data_lma
8000000c:	80c18513          	addi	a0,gp,-2036 # 800002fc <__init_array_end>
	la a1, _data
80000010:	80c18593          	addi	a1,gp,-2036 # 800002fc <__init_array_end>
	la a2, _edata
80000014:	81018613          	addi	a2,gp,-2032 # 80000300 <__bss_start>
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
80000030:	81018513          	addi	a0,gp,-2032 # 80000300 <__bss_start>
	la a1, _end
80000034:	81018593          	addi	a1,gp,-2032 # 80000300 <__bss_start>
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
80000048:	22c000ef          	jal	ra,80000274 <__libc_init_array>
	call main
8000004c:	14c000ef          	jal	ra,80000198 <main>

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

80000058 <spi_cmdAvailability>:
#define SPI_MODE_CPOL (1 << 0)
#define SPI_MODE_CPHA (1 << 1)


static u32 spi_cmdAvailability(Spi_Reg *reg){
	return reg->BUFFER & 0xFFFF;
80000058:	00452503          	lw	a0,4(a0)
}
8000005c:	01051513          	slli	a0,a0,0x10
80000060:	01055513          	srli	a0,a0,0x10
80000064:	00008067          	ret

80000068 <spi_write>:
static u32 spi_rspOccupancy(Spi_Reg *reg){
	return reg->BUFFER >> 16;
}

static void spi_write(Spi_Reg *reg, u8 data){
80000068:	ff010113          	addi	sp,sp,-16
8000006c:	00112623          	sw	ra,12(sp)
80000070:	00812423          	sw	s0,8(sp)
80000074:	00912223          	sw	s1,4(sp)
80000078:	00050413          	mv	s0,a0
8000007c:	00058493          	mv	s1,a1
	while(spi_cmdAvailability(reg) == 0);
80000080:	00040513          	mv	a0,s0
80000084:	fd5ff0ef          	jal	ra,80000058 <spi_cmdAvailability>
80000088:	fe050ce3          	beqz	a0,80000080 <spi_write+0x18>
	reg->DATA = data | SPI_CMD_WRITE;
8000008c:	1004e493          	ori	s1,s1,256
80000090:	00942023          	sw	s1,0(s0)
}
80000094:	00c12083          	lw	ra,12(sp)
80000098:	00812403          	lw	s0,8(sp)
8000009c:	00412483          	lw	s1,4(sp)
800000a0:	01010113          	addi	sp,sp,16
800000a4:	00008067          	ret

800000a8 <spi_select>:
	reg->DATA = SPI_CMD_READ;
	while(spi_rspOccupancy(reg) == 0);
	return reg->DATA;
}

static void spi_select(Spi_Reg *reg, u32 slaveId){
800000a8:	ff010113          	addi	sp,sp,-16
800000ac:	00112623          	sw	ra,12(sp)
800000b0:	00812423          	sw	s0,8(sp)
800000b4:	00912223          	sw	s1,4(sp)
800000b8:	00050413          	mv	s0,a0
800000bc:	00058493          	mv	s1,a1
	while(spi_cmdAvailability(reg) == 0);
800000c0:	00040513          	mv	a0,s0
800000c4:	f95ff0ef          	jal	ra,80000058 <spi_cmdAvailability>
800000c8:	fe050ce3          	beqz	a0,800000c0 <spi_select+0x18>
	reg->DATA = slaveId | 0x80 | SPI_CMD_SS;
800000cc:	000017b7          	lui	a5,0x1
800000d0:	88078793          	addi	a5,a5,-1920 # 880 <__stack_size+0x480>
800000d4:	00f4e4b3          	or	s1,s1,a5
800000d8:	00942023          	sw	s1,0(s0)
}
800000dc:	00c12083          	lw	ra,12(sp)
800000e0:	00812403          	lw	s0,8(sp)
800000e4:	00412483          	lw	s1,4(sp)
800000e8:	01010113          	addi	sp,sp,16
800000ec:	00008067          	ret

800000f0 <spi_deselect>:

static void spi_deselect(Spi_Reg *reg, u32 slaveId){
800000f0:	ff010113          	addi	sp,sp,-16
800000f4:	00112623          	sw	ra,12(sp)
800000f8:	00812423          	sw	s0,8(sp)
800000fc:	00912223          	sw	s1,4(sp)
80000100:	00050413          	mv	s0,a0
80000104:	00058493          	mv	s1,a1
	while(spi_cmdAvailability(reg) == 0);
80000108:	00040513          	mv	a0,s0
8000010c:	f4dff0ef          	jal	ra,80000058 <spi_cmdAvailability>
80000110:	fe050ce3          	beqz	a0,80000108 <spi_deselect+0x18>
	reg->DATA = slaveId | 0x00 | SPI_CMD_SS;
80000114:	000017b7          	lui	a5,0x1
80000118:	80078793          	addi	a5,a5,-2048 # 800 <__stack_size+0x400>
8000011c:	00f4e4b3          	or	s1,s1,a5
80000120:	00942023          	sw	s1,0(s0)
}
80000124:	00c12083          	lw	ra,12(sp)
80000128:	00812403          	lw	s0,8(sp)
8000012c:	00412483          	lw	s1,4(sp)
80000130:	01010113          	addi	sp,sp,16
80000134:	00008067          	ret

80000138 <spi_applyConfig>:

static void spi_applyConfig(Spi_Reg *reg, Spi_Config *config){
	reg->CONFIG = (config->cpol << 0) | (config->cpha << 1) | (config->mode << 4);
80000138:	0005a783          	lw	a5,0(a1)
8000013c:	0045a703          	lw	a4,4(a1)
80000140:	00171713          	slli	a4,a4,0x1
80000144:	00e7e7b3          	or	a5,a5,a4
80000148:	0085a703          	lw	a4,8(a1)
8000014c:	00471713          	slli	a4,a4,0x4
80000150:	00e7e7b3          	or	a5,a5,a4
80000154:	00f52423          	sw	a5,8(a0)
	reg->CLK_DIVIDER = config->clkDivider;
80000158:	00c5a783          	lw	a5,12(a1)
8000015c:	02f52023          	sw	a5,32(a0)
	reg->SS_SETUP = config->ssSetup;
80000160:	0105a783          	lw	a5,16(a1)
80000164:	02f52223          	sw	a5,36(a0)
	reg->SS_HOLD = config->ssHold;
80000168:	0145a783          	lw	a5,20(a1)
8000016c:	02f52423          	sw	a5,40(a0)
	reg->SS_DISABLE = config->ssDisable;
80000170:	0185a783          	lw	a5,24(a1)
80000174:	02f52623          	sw	a5,44(a0)
}
80000178:	00008067          	ret

8000017c <delay>:

#include "dupin.h"

void delay()
{
    for(uint32_t idx = 0;idx < 5000000;idx++) asm volatile("");
8000017c:	00000713          	li	a4,0
80000180:	0080006f          	j	80000188 <delay+0xc>
80000184:	00170713          	addi	a4,a4,1
80000188:	004c57b7          	lui	a5,0x4c5
8000018c:	b3f78793          	addi	a5,a5,-1217 # 4c4b3f <__stack_size+0x4c473f>
80000190:	fee7fae3          	bleu	a4,a5,80000184 <delay+0x8>
}
80000194:	00008067          	ret

80000198 <main>:

int main(void)
{
80000198:	fd010113          	addi	sp,sp,-48
8000019c:	02112623          	sw	ra,44(sp)
800001a0:	02812423          	sw	s0,40(sp)
    uint8_t dataTxSPI = 0;
    Spi_Config spiConfig;

    spiConfig.cpol = 1;
800001a4:	00100793          	li	a5,1
800001a8:	00f12223          	sw	a5,4(sp)
    spiConfig.cpha = 1;
800001ac:	00f12423          	sw	a5,8(sp)
    spiConfig.mode = 0;
800001b0:	00012623          	sw	zero,12(sp)
    spiConfig.clkDivider = 10;
800001b4:	00a00713          	li	a4,10
800001b8:	00e12823          	sw	a4,16(sp)
    spiConfig.ssSetup = 2;
800001bc:	00200713          	li	a4,2
800001c0:	00e12a23          	sw	a4,20(sp)
    spiConfig.ssHold = 2;
800001c4:	00e12c23          	sw	a4,24(sp)
    spiConfig.ssDisable = 2;
800001c8:	00e12e23          	sw	a4,28(sp)

    // Set GPIO LSB as outputs
    GPIO1->OUTPUT_ENABLE = 0x00000001;
800001cc:	10050737          	lui	a4,0x10050
800001d0:	00f72423          	sw	a5,8(a4) # 10050008 <__stack_size+0x1004fc08>

    // Set initial value of GPIO
    GPIO1->OUTPUT = 0x00000001;
800001d4:	00f72223          	sw	a5,4(a4)

    spi_applyConfig(SPI0_BASE, &spiConfig);
800001d8:	00410593          	addi	a1,sp,4
800001dc:	10070537          	lui	a0,0x10070
800001e0:	f59ff0ef          	jal	ra,80000138 <spi_applyConfig>

    dataTxSPI = 0x55;
    spi_select(SPI0_BASE, 0);
800001e4:	00000593          	li	a1,0
800001e8:	10070537          	lui	a0,0x10070
800001ec:	ebdff0ef          	jal	ra,800000a8 <spi_select>
    spi_write(SPI0_BASE, dataTxSPI);
800001f0:	05500593          	li	a1,85
800001f4:	10070537          	lui	a0,0x10070
800001f8:	e71ff0ef          	jal	ra,80000068 <spi_write>
    spi_deselect(SPI0_BASE, 0);
800001fc:	00000593          	li	a1,0
80000200:	10070537          	lui	a0,0x10070
80000204:	eedff0ef          	jal	ra,800000f0 <spi_deselect>

    dataTxSPI = 0xaa;
    spi_select(SPI0_BASE, 0);
80000208:	00000593          	li	a1,0
8000020c:	10070537          	lui	a0,0x10070
80000210:	e99ff0ef          	jal	ra,800000a8 <spi_select>
    spi_write(SPI0_BASE, dataTxSPI);
80000214:	0aa00593          	li	a1,170
80000218:	10070537          	lui	a0,0x10070
8000021c:	e4dff0ef          	jal	ra,80000068 <spi_write>
    spi_deselect(SPI0_BASE, 0);
80000220:	00000593          	li	a1,0
80000224:	10070537          	lui	a0,0x10070
80000228:	ec9ff0ef          	jal	ra,800000f0 <spi_deselect>
    dataTxSPI = 0xaa;
8000022c:	0aa00413          	li	s0,170

    while(1)
    {
        GPIO1->OUTPUT ^= 0x0000000F;
80000230:	10050737          	lui	a4,0x10050
80000234:	00472783          	lw	a5,4(a4) # 10050004 <__stack_size+0x1004fc04>
80000238:	00f7c793          	xori	a5,a5,15
8000023c:	00f72223          	sw	a5,4(a4)
        delay();
80000240:	f3dff0ef          	jal	ra,8000017c <delay>

        dataTxSPI = ~dataTxSPI;
80000244:	fff44413          	not	s0,s0
80000248:	0ff47413          	andi	s0,s0,255

        spi_select(SPI0_BASE, 0);
8000024c:	00000593          	li	a1,0
80000250:	10070537          	lui	a0,0x10070
80000254:	e55ff0ef          	jal	ra,800000a8 <spi_select>
        spi_write(SPI0_BASE, dataTxSPI);
80000258:	00040593          	mv	a1,s0
8000025c:	10070537          	lui	a0,0x10070
80000260:	e09ff0ef          	jal	ra,80000068 <spi_write>
        spi_deselect(SPI0_BASE, 0);
80000264:	00000593          	li	a1,0
80000268:	10070537          	lui	a0,0x10070
8000026c:	e85ff0ef          	jal	ra,800000f0 <spi_deselect>
80000270:	fc1ff06f          	j	80000230 <main+0x98>

80000274 <__libc_init_array>:
80000274:	ff010113          	addi	sp,sp,-16
80000278:	00812423          	sw	s0,8(sp)
8000027c:	00912223          	sw	s1,4(sp)
80000280:	80c18413          	addi	s0,gp,-2036 # 800002fc <__init_array_end>
80000284:	80c18493          	addi	s1,gp,-2036 # 800002fc <__init_array_end>
80000288:	408484b3          	sub	s1,s1,s0
8000028c:	01212023          	sw	s2,0(sp)
80000290:	00112623          	sw	ra,12(sp)
80000294:	4024d493          	srai	s1,s1,0x2
80000298:	00000913          	li	s2,0
8000029c:	02991c63          	bne	s2,s1,800002d4 <__libc_init_array+0x60>
800002a0:	80c18413          	addi	s0,gp,-2036 # 800002fc <__init_array_end>
800002a4:	80c18493          	addi	s1,gp,-2036 # 800002fc <__init_array_end>
800002a8:	408484b3          	sub	s1,s1,s0
800002ac:	da9ff0ef          	jal	ra,80000054 <_init>
800002b0:	4024d493          	srai	s1,s1,0x2
800002b4:	00000913          	li	s2,0
800002b8:	02991863          	bne	s2,s1,800002e8 <__libc_init_array+0x74>
800002bc:	00c12083          	lw	ra,12(sp)
800002c0:	00812403          	lw	s0,8(sp)
800002c4:	00412483          	lw	s1,4(sp)
800002c8:	00012903          	lw	s2,0(sp)
800002cc:	01010113          	addi	sp,sp,16
800002d0:	00008067          	ret
800002d4:	00042783          	lw	a5,0(s0)
800002d8:	00190913          	addi	s2,s2,1
800002dc:	00440413          	addi	s0,s0,4
800002e0:	000780e7          	jalr	a5
800002e4:	fb9ff06f          	j	8000029c <__libc_init_array+0x28>
800002e8:	00042783          	lw	a5,0(s0)
800002ec:	00190913          	addi	s2,s2,1
800002f0:	00440413          	addi	s0,s0,4
800002f4:	000780e7          	jalr	a5
800002f8:	fc1ff06f          	j	800002b8 <__libc_init_array+0x44>
