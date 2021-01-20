BSP_PATH ?= $(realpath ../bsp/CinvestavDupin)
CFLAGS += -I${BSP_PATH}/include
CFLAGS += -I${BSP_PATH}/app

include ${BSP_PATH}/include/soc.mk

LDSCRIPT ?= ${BSP_PATH}/linker/default.ld
