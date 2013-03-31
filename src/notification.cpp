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
 * \file notification.cpp
 * \brief Notification
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2012
 *
 * Handle the game notifications. Ex: a friend want to play with you.
 */

#include "notification.h"
#include <iostream>

/* ************************************************************************** */

/*!
 * \brief Notification constructor.
 */
Notification::Notification(std::string message, notif_type_e type, uint32_t lifespan_ms)
{
    std::cout << "Notification::Notification" << std::endl;

    // Timer
    this->lifespan_ms = lifespan_ms;
    ntimer.start();
    fading_level = 0;

    // Icon texture
    notif_icon_texture = new sf::Texture();

    switch(type)
    {
    default:
    case NOTIF_INFO:
        if (!notif_icon_texture->loadFromFile("resources/gfx/icons/dialog-information.png"))
        {
            std::cerr << "[error] Loading 'dialog-information.png'" << std::endl;
            //return FAILURE;
        }
        break;

    case NOTIF_QUESTION:
        if (!notif_icon_texture->loadFromFile("resources/gfx/icons/dialog-question.png"))
        {
            std::cerr << "[error] Loading 'dialog-question.png'" << std::endl;
            //return FAILURE;
        }
        break;

    case NOTIF_WARNING:
        if (!notif_icon_texture->loadFromFile("resources/gfx/icons/dialog-warning.png"))
        {
            std::cerr << "[error] Loading 'dialog-warning.png'" << std::endl;
            //return FAILURE;
        }
        break;

    case NOTIF_ERROR:
        if (!notif_icon_texture->loadFromFile("resources/gfx/icons/dialog-error.png"))
        {
            std::cerr << "[error] Loading 'dialog-error.png'" << std::endl;
            //return FAILURE;
        }
        break;
    }

    // Notification background
    sf::Vector2f rectangle_size = sf::Vector2f(256, 64);
    sf::Vector2f rectangle_position = sf::Vector2f(32, 32);
    notif_background = new sf::RectangleShape(rectangle_size);
    notif_background->setPosition(rectangle_position);

    // Notification icon
    notif_icon = new sf::Sprite();
    notif_icon->setTexture(*notif_icon_texture);
    notif_icon->setPosition(notif_background->getPosition().x + 8.0, notif_background->getPosition().y + 8.0);
    notif_icon->setScale(0.75, 0.75);

    // Notification font
    notif_message_font = new sf::Font();
    if (!notif_message_font->loadFromFile("resources/fonts/DejaVuSans.ttf"))
    {
        std::cerr << "[error] Loading 'DejaVuSans.ttf'" << std::endl;
        //return FAILURE;
    }

    // Notification message
    notif_message = new sf::Text(message, *notif_message_font, 24);
    notif_message->setColor(sf::Color::Blue);
    notif_message->setPosition(notif_icon->getPosition().x + notif_icon->getGlobalBounds().width + 8.0,  notif_icon->getPosition().y + 8.0);

    // Update notification background size
    rectangle_size = sf::Vector2f(notif_message->getGlobalBounds().width + 92, 64);
    notif_background->setSize(rectangle_size);
}

/*!
 * \brief NotificationManager destructor.
 */
Notification::~Notification()
{
    std::cout << "Notification::~Notification" << std::endl;

    delete notif_background;

    delete notif_icon;
    delete notif_icon_texture;

    delete notif_message;
    delete notif_message_font;
}

/* ************************************************************************** */

bool Notification::isTimeElapsed(void)
{
    bool elapsed = false;

    if (ntimer.getElapsedTime() > lifespan_ms)
    {
        elapsed = true;
    }

    return elapsed;
}

/*!
 * \brief Notification draw.
 */
void Notification::draw(sf::RenderWindow &app)
{
    if( ntimer.getElapsedTime() < 500 )
    {
        // Fading in
        notif_background->setFillColor(sf::Color(255, 255, 255, fading_level*17));
        notif_icon->setColor(sf::Color(255, 255, 255, fading_level*17));
        notif_message->setColor(sf::Color(0, 0, 255, fading_level*17));
        fading_level++;
    }
    else if( ntimer.getElapsedTime() > (lifespan_ms - 500) )
    {
        // Fading out
        notif_background->setFillColor(sf::Color(255, 255, 255, fading_level*17));
        notif_icon->setColor(sf::Color(255, 255, 255, fading_level*17));
        notif_message->setColor(sf::Color(0, 0, 255, fading_level*17));
        fading_level--;
    }
/*
    else
    {
        // Make sure the transparency is off after fade-in ?
        notif_background->setFillColor(sf::Color(255, 255, 255, 255));
        notif_icon->setColor(sf::Color(255, 255, 255, 255));
        notif_message->setColor(sf::Color(0, 0, 255, 255));
    }
*/
    // Draw the notification
    app.draw(*notif_background);
    app.draw(*notif_icon);
    app.draw(*notif_message);
}

/* ************************************************************************** */
