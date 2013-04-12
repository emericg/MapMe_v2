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
 * \file screenGame.h
 * \brief Game screen
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Handle the game.
 */

#include "screenGame.h"

/* ************************************************************************** */

/*!
 * \brief screenGame constructor.
 */
screenGame::screenGame()
{
    std::cout << "screenGame::screenGame" << std::endl;
}

/*!
 * screenGame destructor.
 */
screenGame::~screenGame()
{
    std::cout << "screenGame::~screenGame" << std::endl;

    delete cBlack;
    delete cWhite;
    delete cGrey;

    delete gameMapSprite;
    delete gameMapTexture;

    delete guiConf;
}

/*!
 * \brief Load static resources needed for the main menu.
 */
bool screenGame::load(sf::RenderWindow &App)
{
    std::cout << "screenGame::load" << std::endl;
    float resRatio = (App.getSize().y / 1080.0);

    // Colors
    cBlack = new sf::Color(0, 0, 0, 127);
    cWhite = new sf::Color(255, 255, 255, 255);
    cGrey = new sf::Color(255, 255, 255, 127);

    // Menu background map
    gameMapTexture = new sf::Texture();
    if( !gameMapTexture->loadFromFile("resources/gfx/maps/worldmap_full_1080.png") )
    {
        std::cerr << "[error] Loading 'worldmap_full_1080.png' failed!" << std::endl;
        return FAILURE;
    }

    gameMapSprite = new sf::Sprite();
    gameMapSprite->setTexture(*gameMapTexture);
    gameMapSprite->setPosition(0, 0);

    // Resize background to match window size
    if( resRatio != 1 || ((App.getSize().x/App.getSize().y) != 16.0/9.0) )
    {
        gameMapSprite->setScale(resRatio, resRatio);
/*
        // Handle differents screen aspect ratio ?
        if( (App.getSize().x/App.getSize().y) != 16.0/9.0 )
        {
            int x1 = (App.getSize().x - gameMapSprite->getTextureRect().width)/2;
            gameMapSprite->setPosition(x1, 0);
        }
*/
    }

    // Confirmation window
    guiConf = new guiConfirmation(gettext("Do you really want to close the game ?"));
    guiConf->guiLoad();

    return SUCCESS;
}

/*!
 * \brief screenGame pipeline.
 * \param App The render window.
 * \return true if rendering succeed, false otherwise.
 */
int screenGame::run(sf::RenderWindow &App)
{
    std::cout << "screenGame::run" << std::endl;
    bool exitconfirmation = false;
    bool running = true;
    sf::Event Event;

    // Notifications
    NotificationManager &NotificationManager = NotificationManager::getInstance();
    NotificationManager.add("Let's go !", NOTIF_ERROR);

    // Game Loop
    while( running )
    {
        // Clear screen
        App.clear();

        // Drawing (1/2)
        App.draw(*gameMapSprite);

        // Process confirmation events
        if( exitconfirmation )
        {
            while( App.pollEvent(Event) )
            {
                int confirmcode = guiConf->guiExec(Event);

                if( confirmcode == 1 )
                    exitconfirmation = false;
                else if( confirmcode == 2 )
                    return -1;
            }
        }
        else
        {
            // Process menu events
            while( App.pollEvent(Event) )
            {
                if( Event.type == sf::Event::Closed )
                {
                    exitconfirmation = !exitconfirmation;
                    break;
                }
                /*
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
                {
                    for( int i = 0; i < menuTable.size(); i++ )
                    {
                        if( menuTable[i]->getGlobalBounds().contains(Event.mouseMove.x, Event.mouseMove.y) )
                        {
                            if( i == 0 )
                            {
                                // Goto (1) game screen
                                return (1);
                            }
                            else if( i == (menuTable.size() - 1) )
                            {
                                exitconfirmation != exitconfirmation;
                                break;
                            }
                        }
                    }
                }
*/
                if( Event.type == sf::Event::MouseMoved )
                {
                    // Event.mouseMove.x
                    // contains the current X position of the mouse cursor, in local coordinates

                    // Event.mouseMove.y
                    // contains the current Y position of the mouse cursor, in local coordinates
                }

                if( Event.type == sf::Event::KeyPressed )
                {
                    switch( Event.key.code )
                    {
                        case sf::Keyboard::Q:
                            return -1;
                        break;

                        case sf::Keyboard::Escape:
                            if( exitconfirmation)
                                exitconfirmation = false;
                            else
                                exitconfirmation = true;
                        break;

                        default:
                        break;
                    }
                }
            }
        }

        // Drawing (2/2)
        if( exitconfirmation )
        {
            //App.draw(*effectBlur);
            guiConf->guiDraw(App);
        }

        //guiE->guiDraw(App);
        //mguiMenu->guiDraw(App);

        // Notifications
        NotificationManager.update();
        NotificationManager.draw(App);

        // Display
        App.display();
    }

    return 1;
}
