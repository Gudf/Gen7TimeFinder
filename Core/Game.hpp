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

#ifndef GAME_HPP
#define GAME_HPP

enum Game
{
    Sun         = 1 << 0,
    Moon        = 1 << 1,
    SM          = Sun | Moon,
    UltraSun    = 1 << 2,
    UltraMoon   = 1 << 3,
    USUM        = UltraSun | UltraMoon
};

#endif // GAME_HPP
