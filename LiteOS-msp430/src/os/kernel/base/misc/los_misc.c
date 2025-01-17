/*----------------------------------------------------------------------------
 * Copyright (c) <2013-2015>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#include <src/os/arch/include/los_hwi.h>
#include <src/os/kernel/base/include/los_base.ph>
#include <src/os/kernel/base/include/los_sys.ph>
#include <src/os/kernel/base/include/los_task.ph>

LITE_OS_SEC_TEXT UINT32 LOS_Align(UINT32 uwAddr, UINT32 uwBoundary)
{
    if (uwAddr + uwBoundary - 1 > uwAddr) {
        return (uwAddr + uwBoundary - 1) & ~(uwBoundary - 1);
    } else {
        return uwAddr & ~(uwBoundary - 1);
    }
}

LITE_OS_SEC_TEXT_MINOR VOID LOS_Msleep(UINT32 uwMsecs)
{
    UINT32 uwInterval = 0;

    if (OS_INT_ACTIVE)
    {
        return;
    }

    if (uwMsecs == 0)
    {
        uwInterval = 0;
    }
    else
    {
        uwInterval = LOS_MS2Tick(uwMsecs);
        if (uwInterval == 0)
        {
             uwInterval = 1;
        }
    }

    (VOID)LOS_TaskDelay(uwInterval);
}

#if defined (__ICC430__) || defined (__TI_COMPILER_VERSION__)
static const uint8_t clz_table_4bit[16] = { 4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
int __clz ( unsigned long x )
{
  int n;
  if ((x & 0xFFFF0000) == 0) {n  = 16; x <<= 16;} else {n = 0;}
  if ((x & 0xFF000000) == 0) {n +=  8; x <<=  8;}
  if ((x & 0xF0000000) == 0) {n +=  4; x <<=  4;}
  n += (int)clz_table_4bit[x >> (32-4)];
  return n;
}

#endif

