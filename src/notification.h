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
 * \file notification.h
 * \brief Notification (HEADER)
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2012
 *
 * Handle the game notifications. Ex: a friend want to play with you.
 */

#ifndef NOTIFICATION_H
#define NOTIFICATION_H
/* ************************************************************************** */

#include "typedef.h"
#include "timer.h"

// SFML library
#include <SFML/Graphics.hpp>

/* ************************************************************************** */

typedef enum {
    NOTIF_INFO = 0,
    NOTIF_QUESTION,
    NOTIF_WARNING,
    NOTIF_ERROR
} notif_type_e;

class Notification
{
private:
    sf::RectangleShape *notif_background;

    sf::Sprite *notif_icon;
    sf::Texture *notif_icon_texture;

    sf::Text *notif_message;
    sf::Font *notif_message_font;

    uint32_t fading_level;
    uint32_t lifespan_ms; //!< Lifespan of the notification, in milliseconds
    Timer ntimer;

public:
    Notification(const std::string message, const notif_type_e type, const uint32_t lifespan_ms);
    ~Notification();

    bool isTimeElapsed();
    void draw(sf::RenderWindow &App);
};

/* ************************************************************************** */
#endif // NOTIFICATION_H
