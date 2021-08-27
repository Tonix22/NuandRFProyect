/*
 *      Dupin BSP
 *
 *  Copyright (C) 2021  Diego Hernandez <dhdezr@fpgaparadox.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#pragma once

#include "type.h"
#include "soc.h"

static inline u32 read_u32(u32 address){
	return *((volatile u32*) address);
}

static inline void write_u32(u32 data, u32 address){
	*((volatile u32*) address) = data;
}

static inline u16 read_u16(u32 address){
	return *((volatile u16*) address);
}

static inline void write_u16(u16 data, u32 address){
	*((volatile u16*) address) = data;
}

static inline u8 read_u8(u32 address){
	return *((volatile u8*) address);
}

static inline void write_u8(u8 data, u32 address){
	*((volatile u8*) address) = data;
}

static inline void write_u32_ad(u32 address, u32 data){
	*((volatile u32*) address) = data;
}

#if defined(SYSTEM_MACHINE_TIMER_APB)
static void io_udelay(u32 usec){
	u32 mTimePerUsec = DUPIN_SOC_MACHINE_TIMER_HZ/1000000;
	u32 limit = read_u32(DUPIN_SOC_MACHINE_TIMER_APB) + usec*mTimePerUsec;
	while((int32_t)(limit-(read_u32(DUPIN_SOC_MACHINE_TIMER_APB))) >= 0);
}
#endif




