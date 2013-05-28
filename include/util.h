/* Copyright (c) Citrix Systems Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, 
 * with or without modification, are permitted provided 
 * that the following conditions are met:
 * 
 * *   Redistributions of source code must retain the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer.
 * *   Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer in the documentation and/or other 
 *     materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 */

#ifndef _UTIL_H
#define _UTIL_H

#include <ntddk.h>

#define	P2ROUNDUP(_x, _a)   \
        (-(-(_x) & -(_a)))

static FORCEINLINE LONG
__ffs(
    IN  unsigned long long  mask
    )
{
    unsigned char           *array = (unsigned char *)&mask;
    unsigned int            byte;
    unsigned int            bit;
    unsigned char           val;

    val = 0;

    byte = 0;
    while (byte < 8) {
        val = array[byte];

        if (val != 0)
            break;

        byte++;
    }
    if (byte == 8)
        return -1;

    bit = 0;
    while (bit < 8) {
        if (val & 0x01)
            break;

        val >>= 1;
        bit++;
    }

    return (byte * 8) + bit;
}

#define __ffu(_mask)  \
        __ffs(~(_mask))

static FORCEINLINE LONG
__InterlockedAdd(
    IN  LONG    *Value,
    IN  LONG    Delta
    )
{
    LONG        New;
    LONG        Old;

    do {
        Old = *Value;
        New = Old + Delta;
    } while (InterlockedCompareExchange(Value, New, Old) != Old);

    return New;
}

static FORCEINLINE LONG
__InterlockedSubtract(
    IN  LONG    *Value,
    IN  LONG    Delta
    )
{
    LONG        New;
    LONG        Old;

    do {
        Old = *Value;
        New = Old - Delta;
    } while (InterlockedCompareExchange(Value, New, Old) != Old);

    return New;
}

#endif  // _UTIL_H
