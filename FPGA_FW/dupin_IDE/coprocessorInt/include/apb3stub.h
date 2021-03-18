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

#ifndef _APB3STUB_H_
#define _APB3STUB_H_
/* @Description:
 * Base address: 0x10020000
 * Register 0 at Base address + 0x0, ro. This register returns the result.
 * Register 1 at Base address + 0x4, rw. This register drives data_a (16 bits).
 * Register 2 at Base address + 0x8, rw. This register drives data_b (16 bits).
 * This accelerator is a custom multiplier whose function is:
 * result(32) = data_a(16) * data_b(16) */
typedef struct
{
        volatile uint32_t read_result;
        volatile uint32_t write_port0;
        volatile uint32_t write_port1;
} Apb3Stub;
#endif
