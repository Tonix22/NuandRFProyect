OBJDIR ?= build
LIBS_ ?= ../bsp/CinvestavDupin/libraries
LDFLAGS += -lc

SIM ?= no
ifeq ($(SIM),yes)
    PROJ_NAME := $(PROJ_NAME)_sim
    CFLAGS += -DSIM
endif
CFLAGS += ${CFLAGS_ARGS}
CFLAGS += -I${LIBS_}/include
CFLAGS += -I${LIBS_}/driver
LDFLAGS += -lgcc -nostartfiles -ffreestanding -Wl,-Bstatic,-T,$(LDSCRIPT),-Map,$(OBJDIR)/$(PROJ_NAME).map,--print-memory-usage
#LDFLAGS +=  -nostdlib -lgcc -nostartfiles -ffreestanding -Wl,-Bstatic,-T,$(LDSCRIPT),-Map,$(OBJDIR)/$(PROJ_NAME).map,--print-memory-usage
DOT:= .
COLON:=:

OBJS := $(SRCS)
OBJS := $(realpath $(OBJS))
OBJS := $(subst $(COLON),,$(OBJS))
OBJS := $(OBJS:.c=.o)
OBJS := $(OBJS:.cpp=.o)
OBJS := $(OBJS:.S=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(addprefix $(OBJDIR)/,$(OBJS))


all: $(OBJDIR)/$(PROJ_NAME).elf $(OBJDIR)/$(PROJ_NAME).hex $(OBJDIR)/$(PROJ_NAME).asm $(OBJDIR)/$(PROJ_NAME).bin

$(OBJDIR)/%.elf: $(OBJS) | $(OBJDIR)
	$(RISCV_CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.hex: %.elf
	$(RISCV_OBJCOPY) -O ihex $^ $@

%.bin: %.elf
	$(RISCV_OBJCOPY) -O binary $^ $@

%.v: %.elf
	$(RISCV_OBJCOPY) -O verilog $^ $@

%.asm: %.elf
	$(RISCV_OBJDUMP) -S -d $^ > $@

define LIST_RULE
$(1)
	mkdir -p $(dir $(word 1, $(subst $(COLON), ,$(1))))
	$(RISCV_CC) -c $(CFLAGS)  $(INC) -o $(subst $(COLON), ,$(1))
endef

CAT:= $(addsuffix  $(COLON), $(OBJS))
CAT:= $(join  $(CAT), $(SRCS))
$(foreach i,$(CAT),$(eval $(call LIST_RULE,$(i))))

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)

.SECONDARY: $(OBJS)
