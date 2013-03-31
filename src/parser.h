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
 * \file parser.h
 * \brief Database parser (HEADER).
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Used to parse differents elements databases used by the game.
 */

#ifndef PARSER_H
#define PARSER_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <string>
#include <fstream>

// C standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TinyXML library
#include "tinyxml2/tinyxml2.h"

// Local file(s)
#include "managers/ConfigurationManager.hpp"
#include "elements.h"

/* ************************************************************************** */

/*!
 * \class Parser
 * \brief Database parser.
 *
 * Used to parse differents elements databases used by the game.
 */
class Parser
{
public:
    Parser();
    ~Parser();

    bool dbCheck();
    virtual bool dbParse(element *elements[], short nb, short lv) = 0;
    void elementsPrint(element *elements[]);

private:
    bool dbStat;
    char dbPath[512];
    char dbLng[4];
    tinyxml2::XMLElement *infos;
};

/* ************************************************************************** */

/*!
 * \class CityParser
 * \brief City Database parser.
 */
class CityParser : public Parser
{
public:
    bool ParseDb(element *elements[], short nb, short lv);

private:
    tinyxml2::XMLElement *citynode;
};

/* ************************************************************************** */
#endif // PARSER_H
