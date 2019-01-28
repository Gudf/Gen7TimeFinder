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

#include "StationaryResult.hpp"

StationaryResult::StationaryResult(u32 seed, u16 tid, u16 sid)
{
    this->seed = seed;
    tsv = (tid ^ sid) >> 4;
    for (u8 &iv : ivs)
    {
        iv = -1;
    }
}

QString StationaryResult::getDateTime() const
{
    return target.toString("dd/MM/yyyy hh:mm:ss");
}

void StationaryResult::setTarget(const QDateTime &value)
{
    target = value;
}

u32 StationaryResult::getSeed() const
{
    return seed;
}

u32 StationaryResult::getPID() const
{
    return pid;
}

void StationaryResult::setPID(const u32 &value)
{
    pid = value;
    psv = ((pid >> 16) ^ (pid & 0xffff)) >> 4;
    shiny = psv == tsv;
}

u32 StationaryResult::getEC() const
{
    return ec;
}

void StationaryResult::setEC(const u32 &value)
{
    ec = value;
}

u32 StationaryResult::getFrame() const
{
    return frame;
}

void StationaryResult::setFrame(const u32 &value)
{
    frame = value;
}

u16 StationaryResult::getPSV() const
{
    return psv;
}

u8 StationaryResult::getHiddenPower() const
{
    return hiddenPower;
}

void StationaryResult::calcHiddenPower()
{
    hiddenPower = ((((ivs[0] & 1) + 2 * (ivs[1] & 1) + 4 * (ivs[2] & 1) + 8 * (ivs[5] & 1) + 16 * (ivs[3] & 1) + 32 * (ivs[4] & 1)) * 15) / 63);
}

u8 StationaryResult::getAbility() const
{
    return ability;
}

void StationaryResult::setAbility(const u8 &value)
{
    ability = value;
}

u8 StationaryResult::getNature() const
{
    return nature;
}

void StationaryResult::setNature(const u8 &value)
{
    nature = value;
}

QString StationaryResult::getGenderString() const
{
    return gender == 0 ? "-" : gender == 1 ? "♂" : "♀";
}

u8 StationaryResult::getGender() const
{
    return gender;
}

void StationaryResult::setGender(const u8 &value)
{
    gender = value;
}

u8 StationaryResult::getIV(u8 i) const
{
    return ivs[i];
}

void StationaryResult::setIV(const u8 &i, const u8 &value)
{
    ivs[i] = value;
}

bool StationaryResult::getShiny() const
{
    return shiny;
}

void StationaryResult::setShiny(bool value)
{
    shiny = value;
}

bool StationaryResult::getSynch() const
{
    return synch;
}

void StationaryResult::setSynch(bool value)
{
    synch = value;
}
