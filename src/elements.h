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
 * \file elements.h
 * \brief Represent game elements : city, country, etc (HEADER).
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Represent the differents game elements : city, country, etc.
 */

#ifndef ELEMENTS_H
#define ELEMENTS_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <string>

// C standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Local file(s)
#include "utils.h"

/* ************************************************************************** */

class element
{
public:
    element();

    std::string name;
    std::string getWikilink();

    int coordinates_x;
    int coordinates_y;

private:
    std::string wikilink;

    // temp
    std::string unparsed_coordinates;

    int latitude_degrees;
    int latitude_minutes;
    double latitude;
    std::string latitude_direction;

    int longitude_degrees;
    int longitude_minutes;
    double longitude;
    std::string longitude_direction;

    // fc
    void convert_coordinates();
    void print_coordinates();
};

/* ************************************************************************** */

/*!
 * \class City
 * \brief class that contain caracteristics of a city.
 */
class City : public element
{
public:
    City();
    ~City();

    std::string country;
    int population;
    int population_date;
};

/* ************************************************************************** */

/*!
 * \class Capital
 * \brief class that contain caracteristics of a capital.
 */
class Capital : public City
{
public:
    Capital();

    std::string type;
};

/* ************************************************************************** */

/*!
 * \class Battle
 * \brief class that contain caracteristics of a battle.
 */
class Battle : public element
{
public:
    Battle();

    std::string war;
    std::string date;
    int casualties;
};

/* ************************************************************************** */

/*!
 * \class Country
 * \brief class that contain caracteristics of a country.
 *
 * This class that contain caracteristics of a country :
 * name ; total area ; color (used to find it on the map)
 */
class Country
{
public:
    Country();
    ~Country();

    void country_print();

    std::string name;
    int area;
    int area_pos;
    int population;
    int population_pos;
    int population_date;
    double idh;
    int idh_pos;
    int idh_date;
    int colors[3];
};

/* ************************************************************************** */
#endif // ELEMENTS_H
