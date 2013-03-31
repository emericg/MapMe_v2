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
 * \file NotificationManager.cpp
 * \brief Notification MANAGER
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Handle the game notifications. Ex: a friend want to play with you.
 */

#include "NotificationManager.hpp"

/* ************************************************************************** */

/*!
 * \brief NotificationManager constructor.
 * \note This constructor is private and can only be called by the singleton.
 */
NotificationManager::NotificationManager()
{
    std::cout << "NotificationManager::NotificationManager" << std::endl;
}

/*!
 * \brief NotificationManager destructor.
 * \note This destructor is private and can only be called by the singleton.
 */
NotificationManager::~NotificationManager()
{
    std::cout << "NotificationManager::~NotificationManager" << std::endl;

    for(int i = 0; i < notifications.size(); i++)
    {
        if( notifications.at(i) )
        {
            delete notifications.at(i);
        }
    }

    notifications.clear();
}

/* ************************************************************************** */

/*!
 * \brief NotificationManager initialisation.
 *
 * Empty function.
 */
bool NotificationManager::init()
{
    std::cout << "NotificationManager::init" << std::endl;
    return true;
}

/*!
 * \brief NotificationManager initialisation.
 *
 * Empty function.
 */
bool NotificationManager::add(std::string message, notif_type_e type, uint32_t lifespan_ms)
{
    std::cout << "NotificationManager::add" << std::endl;

    Notification *notif = new Notification(message, type, lifespan_ms);
    notifications.push_back(notif);

    return true;
}

/*!
 * \brief NotificationManager update.
 */
void NotificationManager::update()
{
    for( int i = 0; i < notifications.size(); i++ )
    {
        if( notifications.at(i) )
        {
            if( notifications.at(i)->isTimeElapsed() == true )
            {
                delete notifications.at(i);
                notifications.pop_back();
            }
        }
    }
}

/*!
 * \brief NotificationManager draw.
 */
void NotificationManager::draw(sf::RenderWindow &app)
{
    // Draw notifications
    for( int i = 0; i < notifications.size(); i++ )
    {
        if( notifications.at(i) )
        {
            notifications.at(i)->draw(app);
        }
    }
}

/* ************************************************************************** */
