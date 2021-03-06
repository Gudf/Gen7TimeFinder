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

#ifndef STATIONARYFILTER_HPP
#define STATIONARYFILTER_HPP

#include <QVector>
#include <Results/StationaryResult.hpp>

class StationaryFilter
{

public:
    StationaryFilter() = default;
    StationaryFilter(const QVector<u8> &minIV, const QVector<u8> &maxIV, const QVector<bool> &nature, const QVector<bool> &hiddenPower, u8 ability, bool shiny, u8 gender);
    bool compare(const StationaryResult &frame);

private:
    QVector<u8> minIV, maxIV;
    QVector<bool> nature, hiddenPower;
    u8 ability{}, gender{};
    bool shiny{};

};

#endif // STATIONARYFILTER_HPP
