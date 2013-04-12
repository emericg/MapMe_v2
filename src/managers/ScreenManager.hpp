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
 * \file ScreenManager.hpp
 * \brief Screen MANAGER (HEADER)
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Handle the differents 'screens' of the game.
 */

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
/* ************************************************************************** */

// SFML library
#include <SFML/Graphics.hpp>

// Local file(s)
#include "NotificationManager.hpp"

/* ************************************************************************** */

/*!
 * \class Screens
 * \brief class for handeling game screens.
 *
 * This is a skeleton for the screens system of the game.
 */
class Screens
{
public:
    virtual bool load(sf::RenderWindow &App) = 0;
    virtual int run(sf::RenderWindow &App) = 0;
};

/* ************************************************************************** */
#endif // SCREENMANAGER_H
