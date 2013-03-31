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
 * \file ConfigurationManager.hpp
 * \brief Configuration MANAGER (HEADER)
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2012
 *
 * Handle the configuration file of the game.
 */

#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
/* ************************************************************************** */

// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Boost library
#include <boost/filesystem.hpp>

#ifdef WIN32
    // WINDOWS specifics libraries
    #include <windows.h>
#else
    // POSIX libraries
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

// Local file(s)
#include "Singleton.hpp"

/* ************************************************************************** */

/*!
 * \class ConfigurationManager
 * \brief Class for handeling configuration.
 * \note This is a singleton.
 *
 * This class load and save configuration values.
 */
class ConfigurationManager : public Singleton<ConfigurationManager>
{
friend class Singleton<ConfigurationManager>;

public:
    bool configLoad();
    bool configSave();
    void configShow();

    // Getters

        // Game
        const bool getSplashScreen();
        const unsigned int getWidth();
        const unsigned int getHeight();
        const unsigned int getColorDepth();
        const sf::VideoMode getVideoMode();
        const void getDefinition(unsigned int &width, unsigned int &height);
        const double getDefinitionRatio();
        const double getAspectRatio();
        const bool isFullScreen();
        const bool isVSync();
        const std::string getLanguage();
        const unsigned int getVolumeMaster();
        const unsigned int getVolumeEffects();
        const unsigned int getVolumeMusic();
        const std::string getUsername();
        const unsigned int getNetworkPort();

        // Display
        const void getDisplayDefinition(unsigned int &width, unsigned int &height);
        const unsigned int getDisplayColorDepth();
        const double getDisplayAspectRatio();
        const double getDisplayRefreshRate();

        // System
        const char *getSystemLocale();

        // Paths
        const char *getPathLocales();
        const char *getPathRessources();

    // Setters
    bool setWidth(unsigned int width);
    bool setHeight(unsigned int height);
    bool setColorsDepth(unsigned int colors);
    bool setDisplayResolution(unsigned int width, unsigned int height);
    bool setDisplayAspectRatio(double screenapectratio);
    bool setDisplayAspectRatio(std::string rawscreenapectratio);
    void setFullScreen(bool fullscreen);
    void setVSync(bool vsync);
    bool setLanguage(const char *lng);
    bool setVolumeMaster(unsigned int volume);
    bool setVolumeEffects(unsigned int volume);
    bool setVolumeMusic(unsigned int volume);
    bool setUsername(const char *user);
    bool setNetworkPort(unsigned int port);

private:
    ConfigurationManager();
    ~ConfigurationManager();

    // Configuration file permissions
    bool conf_canRead;  //!< Indicate if the config file exist and can be read
    bool conf_canWrite; //!< Indicate if we have write permissions into the config folder

    // Read and Write configuration
    bool xmlRead();
    bool xmlWrite();

    // Private setters
    void setPaths();
    void setDisplaySettings();
    void setSystemSettings();

    // Various paths
    boost::filesystem::path path_mapme;
    boost::filesystem::path path_resources;
    boost::filesystem::path path_locales;
    boost::filesystem::path path_config;
    boost::filesystem::path path_configfile;

    // System settings
    char system_Locale[255];   //!< System locale, extracted from environment variable
    char system_Language[255]; //!< System language, extracted from environment variable
    char system_Username[255]; //!< System current user name, extracted from environment variable

    // Display settings
    unsigned int display_Width;
    unsigned int display_Height;
    unsigned int display_ColorDepth;
    double       display_RefreshRate;
    double       display_AspectRatio;

    // Game settings
    double       conf_GameVersion;
    bool         conf_SplashScreen;          //!< True if Splash Screen is enabled
    unsigned int conf_Display_Width;         //!< Horizontal display definition (X)
    unsigned int conf_Display_Height;        //!< Vertical display definition (Y)
    unsigned int conf_Display_ColorDepth;    //!< Color mode used, currently not exposed in config file
    double       conf_Display_AspectRatio;   //!< Display aspect ratio
    bool         conf_FullScreen;            //!< True if fullscreen mode is enabled
    bool         conf_vSync;                 //!< True if vertical syncronisation is enabled
    unsigned int conf_VolumeMaster;          //!< Master audio volume
    unsigned int conf_VolumeMusic;           //!< Music volume
    unsigned int conf_VolumeEffects;         //!< Sound effects volume
    std::string  conf_Language;              //!< Language used by the game
    std::string  conf_Locale;                //!< Locale used by the game, derivated from conf_Language
    std::string  conf_Username;              //!< Username of the player, used for high score and network play
    unsigned int conf_NetworkPort;           //!< Network port used by the game
};

/* ************************************************************************** */
#endif // CONFIG_MANAGER_H
