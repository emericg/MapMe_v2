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
 * \fn screenGame()
 * \brief screenGame constructor.
 */
screenGame::screenGame()
{
    //
}

/*!
 * \fn Run(sf::RenderWindow &App)
 * \brief screenGame pipeline.
 * \param App The render window.
 * \return true if rendering succeed, false otherwise.
 */
int screenGame::Run(sf::RenderWindow &App)
{
    std::cout << "screenGame::Run" << std::endl;
/*
    // Load map
    sf::Image *mapIMG;
    mapIMG = new sf::Image();
    if (!mapIMG->loadFromFile("resources/gfx/maps/worldmap_full_1080.png"))
    {
        std::cerr << "[error] Loading worldmap_full_1080" << std::endl;
        return false;
    }
    mapSprite = new sf::Sprite();
    mapSprite->SetImage(*mapIMG);
    mapSprite->SetScale(0.666f, 0.666f);

    // Events
    sf::Event Event;
    bool Running= true;

    // Notifications
    NotificationManager &NotificationManager = NotificationManager::getInstance();

    // Game Loop
    while (Running)
    {
        // Process events
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
            {
                return (-1);
            }

            if (Event.Type == sf::Event::KeyPressed)
            {
                switch (Event.Key.Code)
                {
                    case sf::Key::Escape:
                        // Goto (0) menu screen
                        delete mapSprite;
                        delete mapIMG;
                        return (0);
                        break;
                    case sf::Key::Q:
                        return (-1);
                        break;
                    default:
                        break;
                }
            }
        }

        // Drawing
        App.Clear();
        App.draw(*mapSprite);

        // Notifications
        NotificationManager.update();
        NotificationManager.draw();

        // Display
        App.Display();
    }
*/
    return (-1);
}
