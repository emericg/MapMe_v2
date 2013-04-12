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
 * \file main.cpp
 * \brief Main file of MapMe.
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2012
 *
 * Start the game, initialize libraries and launch main menu.
 */

// Local file(s)
#include "managers/ConfigurationManager.hpp"
#include "managers/NotificationManager.hpp"
#include "cmake_options.h"
#include "screenMenu.h"
#include "screenGame.h"
#include "main.h"

// Gettext librairies
#include <libintl.h>
#include <locale.h>

// SFML library
#include <SFML/Graphics.hpp>

// C++ standard library
#include <iostream>
#include <unistd.h>

/* ************************************************************************** */

#ifdef WIN32
/*!
 * \fn WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 * \param hInstance ??.
 * \param hPrevInstance ??.
 * \param lpCmdLine ??.
 * \param nCmdShow ??.
 * \return Return the program state at exit: 0 if everything is fine, 1 if an error has occured.
 * \note Required by mwing when using SDL, but is it for SFML ??
 *
 * Main function of MapMe project.
 * Start the programme, initialize libraries, then start game pipe, wich contain menu and game.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
/*!
 * \fn int main (int argc, char **argv)
 * \param argc Number of arguments.
 * \param argv Arguments.
 * \return Return the program state at exit: 0 if everything is fine, 1 if an error occur.
 *
 * Main function of MapMe.
 * Start the programme, initialize libraries, then start game pipe, wich contain menu and game.
 */
int main(int argc, char **argv)
#endif
{
    // Configuration loading
    ////////////////////////////////////////////////////////////////////////////

    ConfigurationManager &ConfigurationManager = ConfigurationManager::getInstance();
    if( ConfigurationManager.configLoad() == false )
    {
        std::cerr << "[error] Loading game configuration failed. Using default values." << std::endl;
        std::cerr << "[error] No configuration file will be used during this session." << std::endl;
    }

    // Window initialization
    ////////////////////////////////////////////////////////////////////////////

    uint32_t windowstyle = sf::Style::Close;
    if( ConfigurationManager.isFullScreen() )
    {
        windowstyle |= sf::Style::Fullscreen;
    }

    sf::RenderWindow appWindow;
    appWindow.create(ConfigurationManager.getVideoMode(), "MapMe [DEV]", windowstyle);
    if( ConfigurationManager.isVSync() )
    {
        appWindow.setFramerateLimit(30);
        appWindow.setVerticalSyncEnabled(true);
    }
    else
    {
        appWindow.setFramerateLimit(30);
    }

    sf::Texture iconTexture;
    if( iconTexture.loadFromFile("resources/gfx/icons/mapme.png") )
    {
        appWindow.setIcon(64u, 64u, iconTexture.copyToImage().getPixelsPtr());
    }

    // Shading capabilities check
    ////////////////////////////////////////////////////////////////////////////

    if( sf::Shader::isAvailable() == false )
    {
        std::cerr << "[error] Fragment shaders are not supported by your graphic card." << std::endl;
        std::cerr << "[info]  Fragment shaders are disabled." << std::endl;
    }

#if ENABLE_DEBUG == 0
    // Splash Screen handling (fad-in)
    ////////////////////////////////////////////////////////////////////////////

    sf::Clock   *splashClock = NULL;
    sf::Texture *splashTexture = NULL;
    sf::Sprite  *splashSprite = NULL;

    if( ConfigurationManager.getSplashScreen() )
    {
        splashTexture = new sf::Texture();
        if( splashTexture->loadFromFile("resources/gfx/menu/splash.png") )
        {
            splashSprite = new sf::Sprite();
            splashSprite->setTexture(*splashTexture);
            splashSprite->setPosition((appWindow.getSize().x - splashTexture->getSize().x)/2.0,
                                      (appWindow.getSize().y - splashTexture->getSize().y)/2.0);

            int fadein = 0;
            while( fadein < 30 )
            {
                splashSprite->setColor(sf::Color(255, 255, 255, fadein*8.5));
                appWindow.clear(sf::Color::Black);
                appWindow.draw(*splashSprite);
                appWindow.display();
                fadein++;
            }

            splashClock = new sf::Clock;
        }
    }
#endif // ENABLE_DEBUG

    // Internationalization
    ////////////////////////////////////////////////////////////////////////////

    setlocale(LC_ALL, ConfigurationManager.getSystemLocale());
    textdomain("mapme");
    bindtextdomain("mapme", ConfigurationManager.getPathLocales());

    // Notification system initialisation
    ////////////////////////////////////////////////////////////////////////////

    NotificationManager &NotificationManager = NotificationManager::getInstance();
    if( NotificationManager.init() == false )
    {
        std::cerr << "[error] Loading NotificationManager." << std::endl;
        std::cerr << "[info]  Notifications are disabled." << std::endl;
    }

    // Screens initialisation
    ////////////////////////////////////////////////////////////////////////////

    screenMenu s0;
    screenGame s1;

    if( s0.load(appWindow) != 1 )
    {
        std::cerr << "[error] Main Menu loading." << std::endl;
        return EXIT_FAILURE;
    }

    if( s1.load(appWindow) != 1 )
    {
        std::cerr << "[error] Game screen loading." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<Screens*> vScreens;
    vScreens.push_back(&s0);
    vScreens.push_back(&s1);

#if ENABLE_DEBUG == 0
    // Splash Screen handling (fad-out)
    ////////////////////////////////////////////////////////////////////////////

    if( ConfigurationManager.getSplashScreen() == true )
    {
        if( splashClock->getElapsedTime().asMilliseconds() < 1000 )
        {
            unsigned int tts = (1000 - splashClock->getElapsedTime().asMilliseconds());
            usleep(tts);
        }

        int fadeout = 30;
        while( fadeout > 0 )
        {
            splashSprite->setColor(sf::Color(255, 255, 255, fadeout*8.5));
            appWindow.clear(sf::Color::Black);
            appWindow.draw(*splashSprite);
            appWindow.display();
            fadeout--;
        }

        if( splashTexture )
        {
            delete splashTexture;
            splashTexture = NULL;
        }

        if( splashSprite )
        {
            delete splashSprite;
            splashSprite = NULL;
        }

        if( splashClock )
        {
            delete splashClock;
            splashClock = NULL;
        }
    }
#endif // ENABLE_DEBUG

    // Main loop
    ////////////////////////////////////////////////////////////////////////////

    std::cout << "[info] MapMe launched!" << std::endl;
    int screen = 0;
    while( screen >= 0 )
    {
        screen = vScreens[screen]->run(appWindow);
    }

    // Exit sequence
    ////////////////////////////////////////////////////////////////////////////

    std::cout << "[info] Shutting down." << std::endl;
    ConfigurationManager.destroyInstance();
    appWindow.close();

    return EXIT_SUCCESS;
}

/* ************************************************************************** */
