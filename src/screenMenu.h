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
 * \file screenMenu.h
 * \brief Menu screen (HEADER)
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Handle the game menu.
 */

#ifndef SCREENMENU_H
#define SCREENMENU_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// Local file(s)
#include "gui.h"
#include "managers/ScreenManager.hpp"

/* ************************************************************************** */

/*!
 * \class screenMenu
 * \brief Handle the game menu.
 */
class screenMenu : public Screens
{
private:
    sf::Color *cBlack;
    sf::Color *cWhite;
    sf::Color *cGrey;

    sf::RectangleShape *menuBar;
    sf::Sprite *menuBackground;
    sf::Texture *menuBackgroundTexture;
    sf::Shader *effectBlur;

    guiConfirmation *guiConf;

    sf::Font *menuFont;
    sf::Text *Menu1;
    sf::Text *Menu2;
    sf::Text *Menu3;
    sf::Text *Menu4;
    std::vector<sf::Text*> menuTable;

public:
    screenMenu();
    ~screenMenu();

    virtual bool load(sf::RenderWindow &App);
    virtual int run(sf::RenderWindow &App);
};

/* ************************************************************************** */
#endif // SCREENMENU_H
