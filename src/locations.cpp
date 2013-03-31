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
 * \file locations.cpp
 * \brief Contains cities, capitals and countries classes.
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2008
 *
 * Contains cities, capitals and countries classes use by the game.
 */

#include "locations.h"

/* ************************************************************************** */
/* ************************************************************************** */

Country::Country()
{
	//std::cout << "Country::Country()" << std::endl;			// debug

	name= "empty";

	area= 0;
	color[0]= 0;
	color[1]= 0;
	color[2]= 0;
}

/* ************************************************************************** */

Country::~Country()
{
	//std::cout << "Country::~Country()" << std::endl;			// debug

	// do nothing
}

/* ************************************************************************** */
/* ************************************************************************** */

City::City()
{
	//std::cout << "City::City()" << std::endl;				// debug

	name= "empty";
	country= "empty";
	type= "";
	unparsed_coordinates= "empty";

	coordinates_x= 0;
	coordinates_y= 0;
}

/* ************************************************************************** */

City::~City()
{
	//std::cout << "City::~City()" << std::endl;				// debug

	// do nothing
}

/* ************************************************************************** */
/* ************************************************************************** */

void City::city_parse_coordinates()
{
	//std::cout << "(func) City::city_parse_coordinates" << std::endl;		// debug

	// COORDINATES FORMAT  :  xx°xx'N xx°xx'E

	// Cut latitude-longitude
		std::string::size_type cutter= unparsed_coordinates.find(" ");
		std::string latitude_degreesminutesdirection= trim(unparsed_coordinates.substr(0,cutter));
		std::string longitude_degreesminutesdirection= trim(unparsed_coordinates.substr(cutter+1));

	// Parse latitude
		std::string::size_type cutter_la1= latitude_degreesminutesdirection.find("'");
			latitude_direction= trim(latitude_degreesminutesdirection.substr(cutter_la1+1));
			std::string latitude_degreesminutes= trim(latitude_degreesminutesdirection.substr(0, cutter_la1));

		std::string::size_type cutter_la2= latitude_degreesminutes.find("*");
			std::istringstream la1( trim(latitude_degreesminutes.substr(0,cutter_la2)) );
			la1 >> latitude_degrees;

			std::istringstream la2( trim(latitude_degreesminutes.substr(cutter_la2+1)) );
			la2 >> latitude_minutes;

	// Parse longitude
		std::string::size_type cutter_lo1= longitude_degreesminutesdirection.find("'");
			longitude_direction= trim(longitude_degreesminutesdirection.substr(cutter_lo1+1));
			std::string longitude_degreesminutes= trim(longitude_degreesminutesdirection.substr(0, cutter_lo1));

		std::string::size_type cutter_lo2= longitude_degreesminutes.find("*");
			std::istringstream lo1( trim(longitude_degreesminutes.substr(0,cutter_lo2)) );
			lo1 >> longitude_degrees;

			std::istringstream lo2( trim(longitude_degreesminutes.substr(cutter_lo2+1)) );
			lo2 >> longitude_minutes;
}

/* ************************************************************************** */

void City::city_convert_coordinates(double ratio)
{
	//std::cout << "(func) City:city_convert_coordinates" << std::endl;		// debug
	// Convert coordinates in geographic format to pixel, using "ROBINSON projection"
	// http://en.wikipedia.org/wiki/Robinson_projection


	// Calcul effective latitude and longitude
	latitude= (latitude_degrees + ((latitude_minutes * (5.0/3.0)) / 100.0));
	longitude= (longitude_degrees + ((longitude_minutes * (5.0/3.0)) / 100.0));

	// latitude (paralleles)
	double coefflatt = (+4.45364619279 *pow(10,-15) * pow(latitude, 8)
					-1.35797293746 * pow(10,-12) * pow(latitude, 7)
					+1.61977236357 * pow(10,-10) * pow(latitude, 6)
					-9.48881769647 * pow(10,-9) * pow(latitude, 5)
					+2.83784488718 * pow(10,-7) * pow(latitude, 4)
					-4.55475882810 * pow(10,-6) * pow(latitude, 3)
					-2.49887445827 * pow(10,-6) * pow(latitude, 2)
					-1.89940640613 * pow(10,-4) * pow(latitude, 1)
					+1.00001225019 * pow(latitude, 0));

	if (latitude_direction == "N" || latitude_direction == "n")
		coordinates_y= static_cast<int>(ratio*(540.0*0.666f - latitude*5.4*0.666f*coefflatt));
	else if (latitude_direction == "S" || latitude_direction == "s")
		coordinates_y= static_cast<int>(ratio*(540.0*0.666f + latitude*5.4*0.666f*coefflatt));

	// longitude (meridiens)
	double coefflong = (-4.3490 *pow(10, -16) * pow(longitude, 8)
					+8.2050 *pow(10, -14) * pow(longitude, 7)
					-2.7431 *pow(10, -12) * pow(longitude, 6)
					-3.9468 *pow(10, -10) * pow(longitude, 5)
					+3.4696 *pow(10, -8) * pow(longitude, 4)
					-1.0363 *pow(10, -6) * pow(longitude, 3)
					+1.2813 *pow(10, -5) * pow(longitude, 2)
					+1.2347 *pow(10, -2) * pow(longitude, 1)
					+1.2189 *pow(10, -5) * pow(longitude, 0));

	if (longitude_direction == "E" || longitude_direction == "e")
		coordinates_x= static_cast<int>(ratio*(906.5*0.666f + (longitude*5.32*0.666f)*(coefflong)));
	else if (longitude_direction == "W" || longitude_direction == "w")
		coordinates_x= static_cast<int>(ratio*(906.5*0.666f - (longitude*5.32*0.666f)*(coefflong)));
}

/* ************************************************************************** */

void City::city_print_coordinates()
{
	//std::cout << "(func) City:city_print_coordinates" << std::endl;			// debug

	// City :
	std::cout << "================================" << std::endl;
	std::cout << "city : " << name << std::endl;

	// Check parsing
	std::cout << "unparsed  : " << unparsed_coordinates << std::endl;
	std::cout << "latitude  : " << latitude_degrees << " ° " << latitude_minutes << " ' " << latitude_direction << std::endl;
	std::cout << "longitude : " << longitude_degrees << " ° " << longitude_minutes << " ' " << longitude_direction << std::endl;

	// Check convertion
	std::cout << "latitude  : " << coordinates_y << "y pixels" << std::endl;
	std::cout << "longitude : " << coordinates_x << "x pixels"<< std::endl;
}

/* ************************************************************************** */
/* ************************************************************************** */
