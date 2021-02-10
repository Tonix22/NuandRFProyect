PROJ_NAME=spi

BAREMETAL = ../bsp/CinvestavDupin/libraries


SRCS = 	$(wildcard src/*.c) \
		$(wildcard src/*.cpp) \
		$(wildcard src/*.S) \
    ${BAREMETAL}/common/start.S \

include ${BAREMETAL}/common/bsp.mk
include ${BAREMETAL}/common/riscv64-unknown-elf.mk
include ${BAREMETAL}/common/standalone.mk
