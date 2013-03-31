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
 * \brief Game screen (HEADER)
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Handle the game.
 */

#ifndef SCREENGAME_H
#define SCREENGAME_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// Local file(s)
#include "managers/ScreenManager.hpp"

/* ************************************************************************** */

/*!
 * \class screenGame
 * \brief Handle the game.
 */
class screenGame : public Screens
{
private:
    sf::Sprite *mapSprite;

public:
    screenGame();
    virtual int Run(sf::RenderWindow &App);
};

/* ************************************************************************** */
#endif // SCREENGAME_H
