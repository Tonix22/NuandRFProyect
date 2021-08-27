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
#ifndef _AIP_H_
#define _AIP_H_

#include "stdint.h"

#define AIP_CONFIG_STATUS 0x1e
#define AIP_CONFIG_IPID 0x1f

typedef struct
{
	volatile uint32_t read_data;
	volatile uint32_t write_data;
	volatile uint32_t write_conf;
	volatile uint32_t start;
} aip_reg;

void aip_read (uint32_t config, uint32_t * data, uint32_t size, uint32_t offset);

void aip_write (uint32_t config, uint32_t * data, uint32_t size, uint32_t offset);

void aip_start (void);

#endif
