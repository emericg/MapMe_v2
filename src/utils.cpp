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
 * \file utils.cpp
 * \brief Various helpers.
 */

#include "utils.h"

/* ************************************************************************** */

template<typename T>

/*!
 * \param[in] source: A template which could be a variable of any type.
 * \param[out] dest: A string, converted from the param.
 * \return This function return true if the convertion succeed, false otherwise.
 *
 * Convertion tool which can convert 'anything' into a string, by writing it
 * into an outpout stream (std::ostringstream)
 */
std::string toString(const T & source, std::string & dest)
{
    std::ostringstream oss;

    if( oss << source )
    {
        dest = oss.str();
        return true;
    }
    else
    {
        dest.clear();
        return false;
    }
}

template<typename T>

/*!
 * \param[in] source: A reference to the string to convert.
 * \param[out] dest: A reference to a template which could be a variable of any type.
 * \return This function return true if the convertion succeed, false otherwise.
 *
 * Convertion tool which can convert a string into 'anything', by writing the source
 * string into an input stream (std::istringstream), and writing it's content into 'Dest'.
 */
bool fromString(const std::string & source, T & dest)
{
    std::istringstream iss(source);

    if( iss >> dest )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \fn std::string trim(const std::string & s);
 * \param[in] s A reference to the 'cut' string.
 * \return This function return a string, but cutted.
 *
 * Convertion tool which can cut a string when encounter the string passed in parameter.
 */
std::string trim(const std::string & s)
{
    if( s.length() == 0 )
    {
        return s;
    }

    int b = s.find_first_not_of(" \t\r");
    int e = s.find_last_not_of(" \t\r");

    if( b == -1 ) // No non-spaces
    {
        return "";
    }

    return std::string(s, b, e - b + 1);
}

/* ************************************************************************** */
