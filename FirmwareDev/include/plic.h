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
#ifndef PLIC_H_
#define PLIC_H_

#include "type.h"
#include "io.h"

/* Description: Configure the priority of interrupts 
 * for the PLIC controller. */
extern void plic_set_priority(u32 plic, u32 gateway, u32 priority);

/* Description: Enable the PLIC interrupt controller. */
extern void plic_set_enable(u32 plic, u32 target,u32 gateway, u32 enable);

/* Description: Mask or enable individual interrupt sources for HART. */
extern void plic_set_threshold(u32 plic, u32 target, u32 threshold);

/* Description: Claim the interrupt source from the PLIC. */ 
extern u32 plic_claim(u32 plic, u32 target);

/* Description: Release the interrupt source from the PLIC. */ 
extern void plic_release(u32 plic, u32 target, u32 gateway);

#endif /* PLIC_H_ */


