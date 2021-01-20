#ifndef __dupin_H__
#define __dupin_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <jtag/jtag.h>
#include <target/register.h>
#include <target/target.h>
#include <target/breakpoints.h>
#include <target/target_type.h>
#include <helper/time_support.h>
#include <helper/fileio.h>
#include "target.h"
#include "target_type.h"

#include <jtag/jtag.h>

#define NO_SINGLE_STEP		0
#define SINGLE_STEP		1

#define dupin_BREAK_INST 0x00100073
#define dupin_BREAKC_INST 0x9002

//CPU interface
static int dupin_readStatusRegister(struct target *target, bool execute, uint32_t *value);
static int dupin_writeStatusRegister(struct target *target, bool execute, uint32_t value);
static int dupin_pushInstruction(struct target *target, bool execute, uint32_t instruction);
static int dupin_readInstructionResult32(struct target *target, bool execute, uint8_t *value);
static int dupin_readInstructionResult16(struct target *target, bool execute, uint8_t *value);
static int dupin_readInstructionResult8(struct target *target, bool execute, uint8_t *value);
static int dupin_setHardwareBreakpoint(struct target *target, bool execute, uint32_t id, uint32_t enable,uint32_t pc);

//Abstractions
static int dupin_write_memory(struct target *target, target_addr_t address, uint32_t size, uint32_t count, const uint8_t *buffer);
static int dupin_read_memory(struct target *target, target_addr_t address, uint32_t size, uint32_t count, uint8_t *buffer);
//static int dupin_write32(struct target *target, uint32_t address,uint32_t data);
//static int dupin_read32(struct target *target, uint32_t address,uint32_t *data);
static int dupin_halt(struct target *target);
#endif /* __dupin_H__ */
