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
 * \file typedef.h
 * \brief Type definitions.
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2012
 *
 * Some customs types, useful to build this program under a wide range of
 * differents operating systems and compilers.
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H
/* ************************************************************************** */

// Custom color list
#include "colors.h"

/* ************************************************************************** */

// Custom return codes
#define FAILURE      0
#define SUCCESS      1
#define UNSUPPORTED  2

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Defines custom types
// int64_t/uint64_t may have already been defined by your compiler
typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
//typedef signed long long   int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
//typedef unsigned long long uint64_t;

/* ************************************************************************** */
#endif // TYPEDEF_H
