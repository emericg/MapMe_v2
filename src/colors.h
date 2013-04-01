/*
    This file is a part of MapMe.

    MapMe is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
 * \file colors.h
 * \brief Colors for terminal output.
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2013
 */

#ifndef COLORS_H_
#define COLORS_H_
/* ************************************************************************** */

#include "cmake_options.h"

#if ENABLE_COLORS == ON

#define CLR_RESET  "\e[0m"    //!< Reset colored output to default terminal color

#define CLR_BLACK  "\e[0;30m"
#define CLR_RED    "\e[0;31m"
#define CLR_GREEN  "\e[0;32m"
#define CLR_YELLOW "\e[0;33m"
#define CLR_BLUE   "\e[0;34m"
#define CLR_PURPLE "\e[0;35m"
#define CLR_CYAN   "\e[0;36m"
#define CLR_WHITE  "\e[0;37m"

#define BLD_BLACK  "\e[1;30m"
#define BLD_RED    "\e[1;31m"
#define BLD_GREEN  "\e[1;32m"
#define BLD_YELLOW "\e[1;33m"
#define BLD_BLUE   "\e[1;34m"
#define BLD_PURPLE "\e[1;35m"
#define BLD_CYAN   "\e[1;36m"
#define BLD_WHITE  "\e[1;37m"

#define OUT_BLACK
#define OUT_RED
#define OUT_GREEN
#define OUT_YELLOW
#define OUT_BLUE
#define OUT_PURPLE
#define OUT_CYAN
#define OUT_WHITE

#else // ENABLE_COLORS

#define CLR_RESET

#define CLR_BLACK
#define CLR_RED
#define CLR_GREEN
#define CLR_YELLOW
#define CLR_BLUE
#define CLR_PURPLE
#define CLR_CYAN
#define CLR_WHITE

#define BLD_BLACK
#define BLD_RED
#define BLD_GREEN
#define BLD_YELLOW
#define BLD_BLUE
#define BLD_PURPLE
#define BLD_CYAN
#define BLD_WHITE

#define OUT_BLACK
#define OUT_RED
#define OUT_GREEN
#define OUT_YELLOW
#define OUT_BLUE
#define OUT_PURPLE
#define OUT_CYAN
#define OUT_WHITE

#endif // ENABLE_COLORS

/* ************************************************************************** */
#endif // COLORS_H_
