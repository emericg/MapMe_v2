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
 * \file ConfigurationManager.cpp
 * \brief Configuration MANAGER
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2012
 *
 * Handle the configuration file of the game.
 */

#include "ConfigurationManager.hpp"

// TinyXML library
#include "../tinyxml2/tinyxml2.h"

// C++ standard libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

/* ************************************************************************** */

/*!
 * \brief ConfigurationManager constructor.
 * \note This constructor is private and can only be called by the singleton.
 *
 * Some operating system specific variables initialization.
 */
ConfigurationManager::ConfigurationManager()
{
    std::cout << "ConfigurationManager::ConfigurationManager" << std::endl;

    // Default
    conf_canRead  = false;
    conf_canWrite = false;

    // Default configuration values
    conf_GameVersion              = 1.0;
    conf_SplashScreen             = true;
    conf_Display_Width            = 1280;
    conf_Display_Height           = 720;
    conf_Display_ColorDepth       = 24;
    conf_Display_AspectRatio      = 16.0 / 9.0;
    conf_FullScreen               = false;
    conf_vSync                    = false;
    conf_Language                 = "auto";
    conf_Locale                   = "auto";
    conf_VolumeMaster             = 100;
    conf_VolumeEffects            = 100;
    conf_VolumeMusic              = 75;
    conf_Username                 = "auto";
    conf_NetworkPort              = 3615;

    // Default display settings
    display_Width                 = 0;
    display_Height                = 0;
    display_ColorDepth            = 24;
    display_AspectRatio           = 16.0 / 9.0;
    display_RefreshRate           = 30.0;

    // System settings
    setPaths();
    setDisplaySettings();
    setSystemSettings();
}

/*!
 * \brief ConfigurationManager destructor.
 * \note This destructor is private and can only be called by the singleton.
 */
ConfigurationManager::~ConfigurationManager()
{
    std::cout << "ConfigurationManager::~ConfigurationManager ";
}

/* ************************************************************************** */
/* ************************************************************************** */

/*!
 * \brief This function check, load and parse configuration file, then affect values.
 * \return true if everything is allright, otherwise false.
 */
bool ConfigurationManager::configLoad()
{
    //std::cout << "(func) ConfigurationManager::configLoad" << std::endl;
    bool retcode = true;

    if( conf_canRead == true )
    {
        // Read config file
        if( xmlRead() == false )
        {
            std::cerr << "[error] Your config file seems to be corrupted. Automatic correction on the way." << std::endl;

            if( (conf_canWrite == true) && (xmlWrite() == true) )
            {
                std::cerr << "[info] Corruption(s) successfully corrected." << std::endl;
            }
            else
            {
                std::cerr << "[error] Unable to correct config file." << std::endl;
                retcode = false;
            }
        }
    }
    else
    {
        std::cerr << "[error] Unable to open config file." << std::endl;
        retcode = false;

        if( conf_canWrite == true )
        {
            if( xmlWrite() == true )
            {
                std::cerr << "[info] New config file created with default values." << std::endl;
                conf_canRead = true;
                retcode = true;
            }
        }
    }

    return retcode;
}

/*!
 * \brief This function save every configuration variables into one config file.
 * \return true if everything is allright, otherwise false.
 */
bool ConfigurationManager::configSave()
{
    //std::cout << "(func) ConfigurationManager::configSave" << std::endl;
    bool retcode = false;

    if( conf_canWrite == true )
    {
        if( xmlWrite() == true )
        {
            conf_canRead = true;
            retcode = true;
        }
    }

    return retcode;
}

/* ************************************************************************** */

/*!
 * This function print the current configuration values into a terminal.
 */
void ConfigurationManager::configShow()
{
    //std::cout << "(func) ConfigurationManager::configPrint" << std::endl;

    std::cout << "- system user : '" << system_Username << "'"
              << "\n- system locale : '" << system_Locale << "'"
              << "\n- system language : '" << system_Language << "'"
              << "\n- path mapme : '" << path_mapme << "'"
              << "\n- path config : '" << path_config << "'"
              << "\n- path config file : '" << path_configfile << "'"
              << "\n- path resources : '" << path_resources << "'"
              << "\n- path locales : '" << path_locales << "'"
              << std::endl;

    std::cout << "\n- game version : '" << conf_GameVersion << "'"
              << "\n- display definition : '" << conf_Display_Width << "'x'" << conf_Display_Height << "'@'" << conf_Display_ColorDepth << "'"
              << "\n- display aspect ratio : '" << conf_Display_AspectRatio << "'"
              << "\n- fullscreen : '" << conf_FullScreen << "' vSync : '" << conf_vSync << "'"
              << "\n- language : '" << conf_Language << "' (locale : '" << conf_Locale << "')"
              << "\n- user name : '" << conf_Username << "', network port : '" << conf_NetworkPort << "'"
              << "\n- volume master : '" << conf_VolumeMaster << "', music : '" <<  conf_VolumeMusic << "'"
              << std::endl;
}

/*!
 * \fn bool xmlRead()
 * \return true if everything went allright, false otherwise.
 *
 * This function read configuration file and extract saved values.
 */
bool ConfigurationManager::xmlRead()
{
    std::cout << "(func) ConfigurationManager::xmlRead" << std::endl;
    bool file_corrupt = false;

    tinyxml2::XMLDocument configFile;

    // Open config file
    if( configFile.LoadFile(path_configfile.c_str()) != tinyxml2::XML_NO_ERROR )
    {
        std::cerr << "[error] Unable to open configuration file! ERROR #" << configFile.ErrorID() << std::endl;
        file_corrupt = true;
    }
    else
    {
        // Set XML paths
        tinyxml2::XMLHandle docHandle(&configFile);
        tinyxml2::XMLElement *nodeGame = docHandle.FirstChildElement("configuration").FirstChildElement("game").ToElement();
        tinyxml2::XMLElement *nodeLanguage = docHandle.FirstChildElement("configuration").FirstChildElement("language").ToElement();
        tinyxml2::XMLElement *nodeDisplay = docHandle.FirstChildElement("configuration").FirstChildElement("display").ToElement();
        tinyxml2::XMLElement *nodeSound = docHandle.FirstChildElement("configuration").FirstChildElement("sound").ToElement();
        tinyxml2::XMLElement *nodeNetwork = docHandle.FirstChildElement("configuration").FirstChildElement("network").ToElement();

        int    itemp = 0;
        double dtemp = 0.0;

        // Read 'game' node
        if( nodeGame == NULL )
        {
            file_corrupt = true;
            std::cerr << "[error] Unable to reach game node! Using default values." << std::endl;
        }
        else
        {
            if( nodeGame->QueryDoubleAttribute("version", &dtemp) == tinyxml2::XML_SUCCESS )
            {
                if( conf_GameVersion != dtemp )
                {
                    file_corrupt = true;
                    std::cerr << "[error] Your config file was created for a different version of MapMe." << std::endl;
                }
            }
            else
            {
                file_corrupt = true;
            }
        }

        // Read 'language' node
        if( nodeLanguage == NULL )
        {
            file_corrupt = true;
            std::cerr << "[error] Unable to reach language node! Using default values." << std::endl;
        }
        else
        {
            if( nodeLanguage->Attribute("language") == NULL )
            {
                file_corrupt = true;
            }
            else
            {
                conf_Language = nodeLanguage->Attribute("language");
            }
        }

        // Read 'display' node
        if( nodeDisplay == NULL )
        {
            file_corrupt = true;
            std::cerr << "[error] Unable to reach display node! Using default values." << std::endl;
        }
        else
        {
            if( nodeDisplay->QueryIntAttribute("width", &itemp) == tinyxml2::XML_SUCCESS )
            {
                if( setWidth(itemp) == false )
                {
                    file_corrupt = true;
                }
            }
            else
            {
                file_corrupt = true;
            }

            if( nodeDisplay->QueryIntAttribute("height", &itemp) == tinyxml2::XML_SUCCESS )
            {
                if( setHeight(itemp) == false )
                {
                    file_corrupt = true;
                }
            }
            else
            {
                file_corrupt = true;
            }

            if( nodeDisplay->QueryIntAttribute("colors", &itemp) == tinyxml2::XML_SUCCESS )
            {
                if( setColorsDepth(itemp) == false )
                {
                    file_corrupt = true;
                }
            }

            if( nodeDisplay->Attribute("aspectratio") != NULL)
            {
                if( setDisplayAspectRatio(nodeDisplay->Attribute("aspectratio")) == false )
                {
                    file_corrupt = true;
                }
            }
            else
            {
                file_corrupt = true;
            }

            if( nodeDisplay->QueryIntAttribute("fullscreen", &itemp) == tinyxml2::XML_SUCCESS )
            {
                setFullScreen(itemp);
            }
            else
            {
                file_corrupt = true;
            }

            if( nodeDisplay->QueryIntAttribute("vsync", &itemp) == tinyxml2::XML_SUCCESS )
            {
                setVSync(itemp);
            }
            else
            {
                file_corrupt = true;
            }
        }

        // Read 'sound' node
        if( nodeSound == NULL )
        {
            file_corrupt = true;
            std::cerr << "[error] Unable to reach sound node! Using default values." << std::endl;
        }
        else
        {
            if( nodeSound->QueryIntAttribute("master", &itemp) == tinyxml2::XML_SUCCESS )
            {
                if( setVolumeMaster(itemp) == false )
                {
                    file_corrupt = true;
                }
            }
            else
            {
                file_corrupt = true;
            }

            if( nodeSound->QueryIntAttribute("effects", &itemp) == tinyxml2::XML_SUCCESS )
            {
                if( setVolumeEffects(itemp) == false)
                {
                    file_corrupt = true;
                }
            }
            else
            {
                file_corrupt = true;
            }

            if( nodeSound->QueryIntAttribute("music", &itemp) == tinyxml2::XML_SUCCESS )
            {
                if( setVolumeMusic(itemp) == false )
                {
                    file_corrupt = true;
                }
            }
            else
            {
                file_corrupt = true;
            }
        }

        // Read 'network' node
        if( nodeNetwork == NULL )
        {
            std::cerr << "[error] Unable to reach network node! Using default values." << std::endl;
            file_corrupt = true;
        }
        else
        {
            if( nodeNetwork->Attribute("username") != NULL )
            {
                setUsername(nodeNetwork->Attribute("username"));
            }
            else
            {
                file_corrupt = true;
            }

            if( nodeNetwork->QueryIntAttribute("port", &itemp) == tinyxml2::XML_SUCCESS )
            {
                if( setNetworkPort(itemp) == false )
                {
                    file_corrupt = true;
                }
            }
            else
            {
                file_corrupt = true;
            }
        }
    }

    return !file_corrupt;
}

/*!
 * \fn bool xmlWrite()
 * \return true if everything went allright, false otherwise.
 *
 * This function write configuration file, using a combinaison values already
 * available and default values. The name of the function can be confusing, but
 * it use ostream and not tinyxml2 to write the configuration.
 */
bool ConfigurationManager::xmlWrite()
{
    std::cout << "(func) ConfigurationManager::xmlWrite" << std::endl;

    // Open config file
    std::ofstream configFile(path_configfile.c_str(), std::ios::out);

    // Write config file
    if( (configFile == NULL) || (configFile.fail() == true) )
    {
        std::cerr << "[error] The configuration file cannot be created or written!" << std::endl;
        conf_canWrite = false;

        return false;
    }
    else
    {
        // Convert screen aspect ratio
        std::string aspectratio = "16/9";
        if( conf_Display_AspectRatio == 4.0/3.0 )
        {
            aspectratio = "4/3";
        }
        else if( conf_Display_AspectRatio == 16.0/10.0 )
        {
            aspectratio = "16/10";
        }

        // Write into config file
        configFile
        << "<?xml version=\"1.0\" encoding=\"ASCII\" ?>"
        << "\n<!--      MapMe : Configuration     -->"
        << "\n"
        << "\n<configuration>"
        << "\n\t<game version=\"" << conf_GameVersion << "\" />"
        << "\n\t<language language=\"" << conf_Language << "\" />"
        << "\n\t<display width=\"" << conf_Display_Width << "\" height=\"" << conf_Display_Height << "\" aspectratio=\"" << aspectratio << "\" fullscreen=\"" << conf_FullScreen << "\" vsync=\"" << conf_vSync << "\" />"
        << "\n\t<sound master=\"" << conf_VolumeMaster << "\" effects=\"" << conf_VolumeEffects << "\" music=\"" << conf_VolumeMusic << "\" />"
        << "\n\t<network username=\"" << conf_Username << "\" port=\"" << conf_NetworkPort << "\" />"
        << "\n</configuration>"
        << std::endl;

        // Close file
        configFile.close();

        return true;
    }
}

/* ************************************************************************** */
/* ************************************************************************** */

/*!
 * \brief Set some paths requiered for the application to load.
 * \note This function contains plateform depedant code.
 *
 * Platform indepedant code, thanks to boost::filesystem.
 */
void ConfigurationManager::setPaths()
{
    char *ENV = NULL;

    // Use boost::filesystem to get the path of our executable
    path_mapme = boost::filesystem::current_path();

#ifdef WIN32
    path_resources = path_mapme;
    path_resources /= "resources";

    path_locales = path_resources;
    path_locales /= "i18n";

    path_config = path_mapme;
    path_config /= "config";
#else
    path_locales = "/usr/share/locale/";

    path_resources = path_mapme;
    path_resources /= "resources";

    path_config = path_mapme;
    path_config /= "config";

    ENV = getenv("XDG_CONFIG_HOME");
    if( ENV != NULL )
    {
        path_config = ENV;
        path_config /= "MapMe";
    }
    else
    {
        ENV = getenv("HOME");
        if( ENV != NULL )
        {
            path_config = ENV;
            path_config /= ".mapme";
        }
    }
#endif // WIN32

    path_configfile = path_config;
    path_configfile /= "config.xml";

    if( boost::filesystem::exists(path_config) == true )
    {
        if( boost::filesystem::is_directory(path_config) == true )
        {
            conf_canWrite = true;
        }
    }
    else
    {
        if( boost::filesystem::create_directory(path_config) == true )
        {
            conf_canWrite = true;
        }
    }

    if( boost::filesystem::exists(path_configfile) == true )
    {
        conf_canRead = true;
    }

    std::cout << "path_mapme : " << path_mapme << std::endl;
    std::cout << "path_locales : " << path_locales << std::endl;
    std::cout << "path_resources : " << path_resources << std::endl;
    std::cout << "path_config : " << path_config << std::endl;
    std::cout << "path_configfile : " << path_configfile << std::endl;
}

/*!
 * \brief Extract some settings from the current display mode.
 */
void ConfigurationManager::setDisplaySettings()
{
    sf::VideoMode currentVideoMode = sf::VideoMode::getDesktopMode();

    display_Width = currentVideoMode.width;
    display_Height = currentVideoMode.height;
    display_ColorDepth = currentVideoMode.bitsPerPixel;
    display_RefreshRate = 30;
    display_AspectRatio = static_cast<double>(currentVideoMode.width) / static_cast<double>(currentVideoMode.height);
}

/*!
 * \brief Extract some settings from the operating system.
 * \note This function contains plateform depedant code.
 */
void ConfigurationManager::setSystemSettings()
{
    char *ENV = NULL;

#ifdef WIN32
    //FIXME Get env variables
        //%HOMEPATH%
        //%USERNAME%
#else
    // Get user name
    ENV = getenv("USER");
    if( ENV != NULL )
    {
        strncpy(system_Username, ENV, 255);
    }

    // Get user locale
    ENV = getenv("LANG");
    if( ENV != NULL )
    {
        strncpy(system_Locale, ENV, 255);

        // Set User language from locale
        strncpy(system_Language, ENV, 255);
    }
#endif // WIN32
}

/* ************************************************************************** */
/* ************************************************************************** */

/*!
 * \fn const bool getSplashScreen()
 * \return True if Splash Screen must be displayed.
 */
const bool ConfigurationManager::getSplashScreen()
{
    return conf_SplashScreen;
}

/*!
 * \brief conf_DisplayResolution_Width getter.
 * \return unsigned int conf_DisplayResolution_Width The horizontal display resolution.
 */
const unsigned int ConfigurationManager::getWidth()
{
    return conf_Display_Width;
}

/*!
 * \brief conf_DisplayResolution_Height getter.
 * \return unsigned int conf_DisplayResolution_Height The vertical display resolution.
 */
const unsigned int ConfigurationManager::getHeight()
{
    return conf_Display_Height;
}

/*!
 * \brief conf_DisplayColors getter.
 * \return unsigned int conf_DisplayColors The colors resolution.
 */
const unsigned int ConfigurationManager::getColorDepth()
{
    return conf_Display_ColorDepth;
}

/*!
 * \brief conf_Display_Width and conf_Display_Height getter.
 * \param[out] &width A reference to a value containing horizontal definition in px.
 * \param[out] &height A reference to a value containing vertical definition in px.
 *
 * Put the screen definition in value passed by reference.
 */
const void ConfigurationManager::getDefinition(unsigned int &width, unsigned int &height)
{
    width = conf_Display_Width;
    height = conf_Display_Height;
}

/*!
 * \brief getDefinitionRatio getter.
 *
 * Return ratio between current definition and optimal definition for the game.
 */
const double ConfigurationManager::getDefinitionRatio()
{
    double conf_DisplayDefinitionRatio;

    if( conf_Display_Height != 0 )
    {
        conf_DisplayDefinitionRatio = static_cast<double>(conf_Display_Height)/720.0;
        return true;
    }
    else
    {
        std::cerr << "[error] Cannot compute ratio between current and optimal definition for the game. Using 1.0." << std::endl;
        conf_DisplayDefinitionRatio = 1;
    }

    return conf_DisplayDefinitionRatio;
}

/*!
 * \brief conf_Display_AspectRatio getter.
 * \return double The display aspect ratio.
 */
const double ConfigurationManager::getAspectRatio()
{
    return conf_Display_AspectRatio;
}

/*!
 * \brief conf_FullScreen getter.
 * \return bool true if fullscreen is set.
 */
const bool ConfigurationManager::isFullScreen()
{
    return conf_FullScreen;
}

/*!
 * \brief conf_vsync getter.
 * \return bool true if vsync is set.
 */
const bool ConfigurationManager::isVSync()
{
    return conf_vSync;
}

/*!
 * \brief Return a sf::VideoMode build with current game configuration values.
 * \return A valid sf::VideoMode.
 */
const sf::VideoMode ConfigurationManager::getVideoMode()
{
    sf::VideoMode gameVideoMode(getWidth(), getHeight(), getColorDepth());
    return gameVideoMode;
}

/*!
 * \brief conf_Language getter.
 * \return std::string game language.
 */
const std::string ConfigurationManager::getLanguage()
{
    return conf_Language;
}

/*!
 * \brief conf_VolumeMaster getter.
 * \return the master volume percentage.
 */
const unsigned int ConfigurationManager::getVolumeMaster()
{
    return conf_VolumeMaster;
}

/*!
 * \brief conf_VolumeEffects getter.
 * \return the effects volume percentage.
 */
const unsigned int ConfigurationManager::getVolumeEffects()
{
    return conf_VolumeEffects;
}

/*!
 * \brief conf_VolumeMusic getter.
 * \return the music volume percentage.
 */
const unsigned int ConfigurationManager::getVolumeMusic()
{
    return conf_VolumeMusic;
}

/*!
 * \brief conf_Username getter.
 * \return std::string username.
 */
const std::string ConfigurationManager::getUsername()
{
    return conf_Username;
}

/*!
 * \brief conf_Port getter.
 * \return The network port used by the multiplayer game.
 */
const unsigned int ConfigurationManager::getNetworkPort()
{
    return conf_NetworkPort;
}

/* ************************************************************************** */

/*!
 * \brief Display definition getter.
 * \param[out] The display width definition.
 * \param[out] The display height definition.
 */
const void ConfigurationManager::getDisplayDefinition(unsigned int &width, unsigned int &height)
{
    width  = display_Width;
    height = display_Height;
}

/*!
 * \brief display_ColorDepth getter.
 * \return double The display native aspect ratio.
 */
const unsigned int ConfigurationManager::getDisplayColorDepth()
{
    return display_ColorDepth;
}

/*!
 * \brief display_AspectRatio getter.
 * \return double The display native aspect ratio.
 */
const double ConfigurationManager::getDisplayAspectRatio()
{
    return display_AspectRatio;
}

/*!
 * \brief display_RefreshRate getter.
 * \return unsigned int The display native refresh rate.
 */
const double ConfigurationManager::getDisplayRefreshRate()
{
    return display_RefreshRate;
}

/* ************************************************************************** */

/*!
 * \brief system_Locale getter.
 * \return The system locale.
 */
const char *ConfigurationManager::getSystemLocale()
{
    if( conf_Locale == "auto" )
    {
        return system_Locale;
    }
    else
    {
        return conf_Locale.c_str();
    }
}

/*!
 * \brief path_locales getter.
 */
const char *ConfigurationManager::getPathLocales()
{
    return path_locales.c_str();
}

/*!
 * \brief path_resources getter.
 */
const char *ConfigurationManager::getPathRessources()
{
    return path_resources.c_str();
}

/*!
 * \brief conf_DisplayResolution_Width setter.
 * \param unsigned int width Horizontal display resolution.
 * \return bool true if value is successfully applied.
 *
 * The minimum width is set to 640, the maximum to 4096.
 * The window width cannot be bigger than the display width.
 */
bool ConfigurationManager::setWidth(unsigned int width)
{
    if( (width >= 0) && (width <= 4096) &&
        (width <= sf::VideoMode::getDesktopMode().width) )
    {
        conf_Display_Width = width;
        return true;
    }
    else
    {
        std::cerr << "(set) bad conf_DisplayResolution_Width value" << std::endl;
        return false;
    }
}

/*!
 * \brief conf_DisplayResolution_Height setter.
 * \param unsigned int height Vertical display resolution.
 * \return bool true if value is successfully applied.
 *
 * The minimum height is set to 360, the maximum to 4096.
 * The window height cannot be bigger than the display height.
 */
bool ConfigurationManager::setHeight(unsigned int height)
{
    if( (height >= 360) && (height <= 4096) &&
        (height <= sf::VideoMode::getDesktopMode().height) &&
        (height == static_cast<unsigned int>(static_cast<double>(conf_Display_Width)/conf_Display_AspectRatio)) )
    {
        conf_Display_Height = height;
        return true;
    }
    else
    {
        conf_Display_Height = static_cast<unsigned int>(static_cast<double>(conf_Display_Width)/conf_Display_AspectRatio);
        std::cerr << "(set) bad conf_DisplayResolution_Height value. Y is " << height << " and should be "<< conf_Display_Height << std::endl;
        return false;
    }
}

/*!
 * \brief conf_DisplayColors setter.
 * \param unsigned int colors Colors resolution.
 * \return bool true if value is successfully applied.
 */
bool ConfigurationManager::setColorsDepth(unsigned int colors)
{
    if( (colors == 16) || (colors == 24) )
    {
        conf_Display_ColorDepth = colors;
        return true;
    }
    else
    {
        std::cerr << "(set) bad conf_DisplayColors value. colors is " << colors << " but supported values are 16, 24" << std::endl;
        return false;
    }
}

/*!
 * \brief conf_DisplayResolution_Height and conf_DisplayResolution_Height setter.
 * \param unsigned int width Horizontal definition.
 * \param unsigned int height Vertical definition.
 * \return bool true if both values are successfully applied.
 */
bool ConfigurationManager::setDisplayResolution(unsigned int width, unsigned int height)
{
    bool retcode = true;
    unsigned int height_save = conf_Display_Height;

    if( setWidth(width) == true )
    {
        if( setHeight(height) == false )
        {
            // Restore horizontal definition
            conf_Display_Height = height_save;
            retcode = false;
        }
    }

    return retcode;
}

/*!
 * \brief conf_Display_AspectRatio setter.
 * \param aspectratio The screen aspect ratio.
 * \return bool true if succeed.
 */
bool ConfigurationManager::setDisplayAspectRatio(double aspectratio)
{
    bool retcode = true;

    if( aspectratio == 0 )
    {
        sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
        conf_Display_AspectRatio = static_cast<double>(desktopVideoMode.width)/static_cast<double>(desktopVideoMode.height);
    }
    else if( (aspectratio == (4.0/3.0)) ||
             (aspectratio == (16.0/9.0)) ||
             (aspectratio == (16.0/10.0)) )
    {
        conf_Display_AspectRatio = aspectratio;
    }
    else
    {
        std::cerr << "[error] Unsupported screen aspect ratio! Using 16/9." << std::endl;
        retcode = false;
    }

    return retcode;
}

/*!
 * \fn bool setDisplayAspectRatio(std::string rawaspectratio)
 * \brief conf_Display_AspectRatio setter.
 * \param rawaspectratio The format of the screen.
 * \return bool true if succeed.
 *
 * The optimal definition for the game is 1280x720px (16/9 aspect ratio).
 * Because we do not use vector graphics, we have to build each sprite with a fixed definition,
 * and scale it to match user definition.
 * conf_Display_AspectRatio MUST be updated each time game definition is changed.
 */
bool ConfigurationManager::setDisplayAspectRatio(std::string rawaspectratio)
{
    bool retcode = true;

    if( rawaspectratio == "0" )
    {
        sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
        conf_Display_AspectRatio = static_cast<double>(desktopVideoMode.width)/static_cast<double>(desktopVideoMode.height);
    }
    else if( (rawaspectratio == "4/3") ||
             (rawaspectratio == "4:3") )
    {
        conf_Display_AspectRatio = 4.0/3.0;
    }
    else if( (rawaspectratio == "16/9") ||
             (rawaspectratio == "16:9") )
    {
        conf_Display_AspectRatio = 16.0/9.0;
    }
    else if( (rawaspectratio == "16/10") ||
             (rawaspectratio == "16:10") )
    {
        conf_Display_AspectRatio= 16.0/10.0;
    }
    else
    {
        std::cerr << "[error] Unsupported screen aspect ratio!" << std::endl;
        retcode = false;
    }

    return retcode;
}

/*!
 * \brief conf_FullScreen setter.
 * \param fullscreen The fullscreen state to set.
 *
 * Do not return true or false, because if fullscreen mode fails it's likely not
 * because of the configuration value but because of the system's settings.
 */
void ConfigurationManager::setFullScreen(const bool fullscreen)
{
    conf_FullScreen = fullscreen;
}

/*!
 * \brief conf_vSync setter.
 * \param vsync The vsync state to set.
 *
 * Do not return true or false, because if vsync mode fails it's likely not
 * because of the configuration value but because of the system's settings.
 */
void ConfigurationManager::setVSync(const bool vSync)
{
    conf_vSync = vSync;
}

/*!
 * \brief conf_Language setter.
 * \param lng The language to set.
 * \return bool true if value is successfully applied.
 */
bool ConfigurationManager::setLanguage(const char *lng)
{
    //strncpy(conf_Language, lng, 255);
    return false;
}

/*!
 * \brief conf_VolumeMaster setter.
 * \param volume The volume level to set.
 * \return bool true if value is successfully applied.
 */
bool ConfigurationManager::setVolumeMaster(const unsigned int volume)
{
    if( (volume >= 0) && (volume <= 100) )
    {
        conf_VolumeMaster = volume;
        return true;
    }
    else
    {
        std::cerr << "(set) conf_VolumeMaster value is out of range!" << std::endl;
        return false;
    }
}

/*!
 * \brief conf_VolumeEffects setter.
 * \param volume The volume to set.
 * \return bool true if value is successfully applied.
 */
bool ConfigurationManager::setVolumeEffects(const unsigned int volume)
{
    if( (volume >= 0) && (volume <= 100) )
    {
        conf_VolumeEffects = volume;
        return true;
    }
    else
    {
        std::cerr << "(set) conf_VolumeEffects value is out of range!" << std::endl;
        return false;
    }
}

/*!
 * \brief conf_VolumeMusic setter.
 * \param volume The volume to set.
 * \return bool true if value is successfully applied.
 */
bool ConfigurationManager::setVolumeMusic(const unsigned int volume)
{
    if( (volume >= 0) && (volume <= 100) )
    {
        conf_VolumeMusic = volume;
        return true;
    }
    else
    {
        std::cerr << "(set) conf_VolumeMusic value is out of range!" << std::endl;
        return false;
    }
}

/*!
 * \brief conf_Username setter.
 * \param user The username to set.
 * \return bool true if value is successfully applied.
 */
bool ConfigurationManager::setUsername(const char *user)
{
    //strncpy(conf_Username, user, 255);
    return false;
}

/*!
 * \brief conf_Port setter.
 * \param port The port number to set.
 * \return bool true if value is successfully applied.
 */
bool ConfigurationManager::setNetworkPort(const unsigned int port)
{
    if( (port > 0) && (port < 65536) )
    {
        conf_NetworkPort = port;
        return true;
    }
    else
    {
        std::cerr << "(set) conf_Port value out of range" << std::endl;
        return false;
    }
}

/* ************************************************************************** */
