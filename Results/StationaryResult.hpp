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

#ifndef STATIONARYRESULT_HPP
#define STATIONARYRESULT_HPP

#include <QDateTime>
#include <Core/Global.hpp>

class StationaryResult
{

public:
    StationaryResult() = default;
    StationaryResult(u32 seed, u16 tid, u16 sid);
    QString getDateTime() const;
    void setTarget(const QDateTime &value);
    u32 getSeed() const;
    u32 getPID() const;
    void setPID(const u32 &value);
    u32 getEC() const;
    void setEC(const u32 &value);
    u32 getFrame() const;
    void setFrame(const u32 &value);
    u16 getPSV() const;
    u8 getHiddenPower() const;
    void calcHiddenPower();
    u8 getAbility() const;
    void setAbility(const u8 &value);
    u8 getNature() const;
    void setNature(const u8 &value);
    QString getGenderString() const;
    u8 getGender() const;
    void setGender(const u8 &value);
    u8 getIV(u8 i) const;
    void setIV(const u8 &i, const u8 &value);
    bool getShiny() const;
    void setShiny(bool value);
    bool getSynch() const;
    void setSynch(bool value);

private:
    QDateTime target;
    u32 seed{}, pid{}, ec{}, frame{};
    u16 psv{}, tsv{};
    u8 hiddenPower{}, ability{}, nature{}, gender{};
    u8 ivs[6] {};
    bool shiny{}, synch{};

};

#endif // STATIONARYRESULT_HPP
