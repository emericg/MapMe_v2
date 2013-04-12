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
 * \file parser.cpp
 * \brief Database parser.
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Used to parse differents elements databases used by the game.
 */

#include "parser.h"

/* ************************************************************************** */

/*!
 * \fn Parser()
 * \brief Parser constructor.
 */
Parser::Parser()
{
    std::cout << "Parser::Parser" << std::endl;

    // Get definition ratio
    //ConfigurationManager &ConfigurationManager = ConfigurationManager::getInstance();

    // Get language
    //strncpy(dbLng, ConfigurationManager.conf_lLng.c_str(), 4);
    strncpy(dbLng, "fr", 4);

    dbStat = false;
}

/*!
 * \fn Parser()
 * \brief Parser destructor.
 */
Parser::~Parser()
{
    std::cout << "Parser::~Parser" << std::endl;
}

/*!
 * \fn Parser::dbCheck()
 * \brief Check the database file.
 * \return true if database is ok, false otherwise.
 */
bool Parser::dbCheck()
{
    std::cout << "(func) Parser::CheckDb" << std::endl;

    // dbPath
    strncpy(dbPath, "databases/", 512);
    strncat(dbPath, dbLng , 4);
    strncat(dbPath, "/xxx.xml", 512);
    //std::cout << "   path : " << dbPath << std::endl;

    tinyxml2::XMLDocument dbFile;
    if (dbFile.LoadFile(dbPath) != tinyxml2::XML_NO_ERROR)
    {
        std::cerr << "[error] Unable to open database! ERROR #" << dbFile.ErrorID() << std::endl;
        return false;
    }
    else
    {
        tinyxml2::XMLHandle docHandle(&dbFile);
        infos = docHandle.FirstChildElement("database").FirstChildElement("infos").ToElement();

        if (!infos)
        {
            dbStat = false;
            return false;
        }
        else
        {
            double dbVersion = 0.0;
            infos->QueryDoubleAttribute("version", &dbVersion);

            if (dbVersion != 1.0)
            {
                dbStat = false;
                return false;
            }
            else
            {
                dbStat = true;
                std::cout << "   database successfully opened !" << std::endl;
                return true;
            }
        }
    }

    return false;
}

/*!
 * \fn Parser::dbParse(element *elements[])
 * \brief Print the content of the elements table.
 * \param *elements[] A table of elements.
 * \param nb docme.
 * \param nb docme.
 * \return docme.
 */
bool Parser::dbParse(element *elements[], short nb, short lv)
{
    std::cout << "Parser::dbParse" << std::endl;

    return false;
}

/*!
 * \fn Parser::elementsPrint(element *elements[])
 * \param element *elements[] a table of elements.
 *
 * Print the content of the elements table.
 */
void Parser::elementsPrint(element *elements[])
{
    std::cout << "Parser::elementsPrint" << std::endl;
}

/* ************************************************************************** */

/*
bool CityParser::dbParse(element *elements[], short nb, short lv)
{
    std::cout << "(func) Parser::ParseCountriesFile" << std::endl; // debug

    // Open 'database'
    TiXmlDocument countriesdb(countriesdb_path);
    if (!countriesdb.LoadFile())
    {
        std::cerr << "   Unable to open countriesdb database! ERROR #" << countriesdb.ErrorId() << std::endl;
        return false;
    }
    else if (countriesdb_statut == false)
    {
        std::cerr << "   Unable to load countriesdb database! internal format ERROR" << std::endl;
        return false;
    }
    else
    {
        std::cout << "   countriesdb database successfully opened!" << std::endl;
    }

    // XML paths
    TiXmlHandle docHandle(&countriesdb);

    std::ostringstream oss;
    oss << lv;
    std::string llv= oss.str();
    std::string level= ("level" + llv);

    // Loading loop
    for(short i= 0; i<nb; i++)
    {
        countrynode= docHandle.FirstChildElement("database").FirstChild(level.c_str()).Child("country", i).ToElement();

        // load values
        country[i]->name= countrynode->Attribute("name");
        countrynode->QueryIntAttribute("area", &country[i]->area);

        //color?


        // loop
        if (countrynode->NextSiblingElement("country") == 0)
            break;
    }

    return true;
}
*/

/*
bool Parser::ParseCitiesFile(City *city[], short nb, short lv)
{
    std::cout << "(func) Parser::ParseCitiesFile" << std::endl; // debug

    // Open 'database'
    TiXmlDocument database(citiesdb_path);
    if (!database.LoadFile()) // redondant ?
    {
        std::cerr << "   Unable to open citiesdb database! ERROR #" << database.ErrorId() << std::endl;
        return false;
    }
    else if (citiesdb_statut == false) // redondant ?
    {
        std::cerr << "   Unable to load citiesdb database! internal format ERROR" << std::endl;
        return false;
    }

    // XML paths
    TiXmlHandle docHandle(&database);

    std::ostringstream oss;
    oss << lv;
    std::string llv= oss.str();
    std::string level= ("level" + llv);

    // XML node
    citynode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("city", 0).ToElement();

    // Count nodes
    totalcities= 0;
    while(citynode)
    {
        totalcities++;
        citynode= citynode->NextSiblingElement();
    }

    //citynode->FirstChildElement();
    std::cout << "  " << totalcities << " cities in this node." << std::endl;

    // City list
    short totalcities_tab[totalcities];
    for(short i=0; i<totalcities; i++)
        totalcities_tab[i]= 0;

    // Initialize random seed
    srand(time(NULL));

    // Random loading loop
    for(short i=0; i<nb; i++)
    {
        short a= rand() % totalcities;
        if (totalcities_tab[a] != 1)
        {
            citynode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("city", a).ToElement();

            // load values
            city[i]->name= citynode->Attribute("name");
            city[i]->country= citynode->Attribute("country");
            city[i]->unparsed_coordinates= citynode->Attribute("coordinates");

            // convert coordinates
            //city[i]->city_parse_coordinates();
            //city[i]->city_convert_coordinates(ratio);
            //city[i]->city_print_coordinates(); // debug

            // update usetable
            totalcities_tab[a]= 1;
        }
        else
        {
            i--;
        }
    }

    return true;
}
*/

/*
bool CapitalParser::ParseDb(City *city[], short nb, short lv)
{
    std::cout << "(func) Parser::ParseCapitalsFile" << std::endl; // debug

    // Open 'database'
    TiXmlDocument database(capitalsdb_path);
    if (!database.LoadFile()) // redondant ?
    {
        std::cerr << "   Unable to open capitalsdb database! ERROR #" << database.ErrorId() << " , " << database.ErrorDesc() << std::endl;
        return false;
    }
    else if (capitalsdb_statut == false) // redondant ?
    {
        std::cerr << "   Unable to load capitalsdb database! shorternal format ERROR" << std::endl;
        return false;
    }

    // XML paths
    TiXmlHandle docHandle(&database);

    std::ostringstream oss;
    oss << lv;
    std::string llv= oss.str();
    std::string level= ("level" + llv);

    // XML node
    capitalnode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("capital", 0).ToElement();

    // Count nodes
    totalcapitals= 0;
    while(capitalnode)
    {
        totalcapitals++;
        capitalnode= capitalnode->NextSiblingElement();
    }

    //capitalnode->FirstChildElement();
    std::cout << "  " << totalcapitals << " capitals in this node." << std::endl;

    // Capitals list
    short totalcapitals_tab[totalcapitals];
    for(short i= 0; i<totalcapitals; i++)
        totalcapitals_tab[i]= 0;

    // Initialize random seed
    srand(time(NULL));

    // Random loading loop
    for(short i=0; i<nb; i++)
    {
        short a= rand() % totalcapitals;
        if (totalcapitals_tab[a] != 1)
        {
            capitalnode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("capital", a).ToElement();

            // load values
            city[i]->name= capitalnode->Attribute("name");
            city[i]->country= capitalnode->Attribute("capitalof");
            if (capitalnode->Attribute("type") != NULL)
                city[i]->type= capitalnode->Attribute("type");
            else
                city[i]->type= "";
            city[i]->unparsed_coordinates= capitalnode->Attribute("coordinates");

            // convert coordinates
            //city[i]->city_parse_coordinates();
            //city[i]->city_convert_coordinates(ratio);
            //city[i]->city_print_coordinates(); // debug

            // update usetable
            totalcapitals_tab[a]= 1;
        }
        else
        {
            i--;
        }
    }

    return true;
}
*/

/* ************************************************************************** */
