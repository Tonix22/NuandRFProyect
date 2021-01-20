PROJ_NAME=ad9361_project

BAREMETAL = ../bsp/CinvestavDupin/libraries

PLATFORM=src/platform_generic
CFLAGS=-I$(PLATFORM)

SRCS = main.c
SRCS += $(filter-out main.c, $(wildcard *.c)) $(wildcard $(PLATFORM)/*.c)

SRCS =  $(wildcard src/*.c) \
		$(wildcard src/platform_generic/*.c) \
		$(wildcard src/*.cpp) \
    	${BAREMETAL}/common/start.S \

include ${BAREMETAL}/common/bsp.mk
include ${BAREMETAL}/common/riscv64-unknown-elf.mk
include ${BAREMETAL}/common/standalone.mk
