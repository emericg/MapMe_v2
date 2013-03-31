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
 * \file NotificationManager.hpp
 * \brief Notification MANAGER (HEADER)
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Handle the game notifications. Ex: a friend want to play with you.
 */

#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H
/* ************************************************************************** */

// SFML library
#include <SFML/Graphics.hpp>

// Local file(s)
#include "Singleton.hpp"
#include "../typedef.h"
#include "../notification.h"

#include <vector>

/* ************************************************************************** */

/*!
 * \class NotificationManager
 * \brief NotificationManager handles in-game notifications.
 * \note This is a singleton.
 *
 * Handle in-game notifications. Ex: a friend want to play with you.
 */
class NotificationManager : public Singleton<NotificationManager>
{
friend class Singleton<NotificationManager>;

private:
    NotificationManager();
    ~NotificationManager();

    std::vector<Notification *> notifications;

public:
    bool init();
    bool add(std::string message, notif_type_e type = NOTIF_INFO, uint32_t lifespan_ms = 4000);
    void update();
    void draw(sf::RenderWindow &App);
};

/* ************************************************************************** */
#endif // NOTIFICATION_MANAGER_H
