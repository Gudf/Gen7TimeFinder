/*
 * This file is part of Gen7TimeFinder
 * Copyright (C) 2018-2019 by Admiral_Fish
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Core/SFMT.hpp"

#define CMSK1 0xdfffffef
#define CMSK2 0xddfecb7f
#define CMSK3 0xbffaffff
#define CMSK4 0xbffffff6
#define CSL1 18
#define CSR1 11
#define N32 624

SFMT::SFMT(u32 seed, u32 frames)
{
    initialize(seed);
    advanceFrames(frames);
}

void SFMT::initialize(u32 seed)
{
    sfmt[0] = seed;

    for (index = 1; index < N32; index++)
    {
        sfmt[index] = 0x6C078965 * (sfmt[index - 1] ^ (sfmt[index - 1] >> 30)) + index;
    }

    periodCertificaion();
    shuffle();
    index = 0;
}

void SFMT::periodCertificaion()
{
    u32 inner = 0;
    u32 work;

    for (int i = 0; i < 4; i++)
    {
        inner ^= sfmt[i] & PARITY[i];
    }
    for (int i = 16; i > 0; i >>= 1)
    {
        inner ^= inner >> i;
    }
    if ((inner & 1) == 1)
    {
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        work = 1;
        for (int j = 0; j < 32; j++)
        {
            if ((work & PARITY[i]) != 0)
            {
                sfmt[i] ^= work;
                return;
            }
            work <<= 1;
        }
    }
}

void SFMT::advanceFrames(u32 frames)
{
    u32 temp = index + (frames * 2);
    while (temp >= 624)
    {
        temp -= 624;
        shuffle();
    }
    index = temp;
}

u32 SFMT::nextUInt()
{
    // Array reshuffle check
    if (index >= N32)
    {
        shuffle();
    }

    return sfmt[index++];
}

u64 SFMT::nextULong()
{
    // Array reshuffle check
    if (index >= N32)
    {
        shuffle();
    }

    u32 high = sfmt[index++];
    u32 low = sfmt[index++];
    return high | (static_cast<u64>(low) << 32);
}

void SFMT::shuffle()
{
    int a = 0;
    int b = 488;
    int c = 616;
    int d = 620;
    do
    {
        sfmt[a + 3] = sfmt[a + 3] ^ (sfmt[a + 3] << 8) ^ (sfmt[a + 2] >> 24) ^ (sfmt[c + 3] >> 8) ^ ((sfmt[b + 3] >> CSR1) & CMSK4) ^ (sfmt[d + 3] << CSL1);
        sfmt[a + 2] = sfmt[a + 2] ^ (sfmt[a + 2] << 8) ^ (sfmt[a + 1] >> 24) ^ (sfmt[c + 3] << 24) ^ (sfmt[c + 2] >> 8) ^ ((sfmt[b + 2] >> CSR1) & CMSK3) ^ (sfmt[d + 2] << CSL1);
        sfmt[a + 1] = sfmt[a + 1] ^ (sfmt[a + 1] << 8) ^ (sfmt[a] >> 24) ^ (sfmt[c + 2] << 24) ^ (sfmt[c + 1] >> 8) ^ ((sfmt[b + 1] >> CSR1) & CMSK2) ^ (sfmt[d + 1] << CSL1);
        sfmt[a] = sfmt[a] ^ (sfmt[a] << 8) ^ (sfmt[c + 1] << 24) ^ (sfmt[c] >> 8) ^ ((sfmt[b] >> CSR1) & CMSK1) ^ (sfmt[d] << CSL1);
        c = d;
        d = a;
        a += 4;
        b += 4;
        if (b >= N32)
        {
            b = 0;
        }
    }
    while (a < N32);
    index = 0;
}
