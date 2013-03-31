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
 * \file gui.h
 * \brief gui system (HEADER).
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2010
 *
 * Contain different gui elements.
 */

#ifndef GUI_H
#define GUI_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// SFML library
#include <SFML/Graphics.hpp>

// Local file(s)
#include "managers/ConfigurationManager.hpp"

/* ************************************************************************** */

//! Position where to draw gui element
typedef enum {
    Center = 0,
    TopLeft,
    TopCenter,
    TopRight,
    BottomLeft,
    BottomCenter,
    BottomRight,
} guiPosition_e;

/* ************************************************************************** */
/*!
 * \class gui
 * \brief docme.
 */
class gui
{
public:
    gui();
    virtual ~gui();

    virtual bool guiLoad() = 0;
    virtual void guiDraw(sf::RenderWindow &App) = 0;

protected:
    float gui_x, gui_y;
    float gui_width, gui_height;

    float display_x, display_y;
    double display_aspectratio;
    double display_resratio;

    sf::Font *menuFont;

    sf::Color *cBlue;
    sf::Color *cBlack;
    sf::Color *cWhite;
    sf::Color *cWhiteBlue;
};

/* ************************************************************************** */

/*!
 * \class guiElement
 * \brief docme.
 */
class guiElement : public gui
{
public:
    guiElement(guiPosition_e p, float gui_width, float gui_height);

    bool guiLoad();
    bool guiSetSize();
    void guiDraw(sf::RenderWindow &App);

private:
    sf::Shape *Polygon;
    sf::Sprite *sprWa;
    sf::Texture *gui_whiteangle;
};

/* ************************************************************************** */

/*!
 * \class guiButton
 * \brief docme.
 */
class guiButton : public gui
{
public:
    guiButton(std::string text, float x, float y);
    bool guiLoad();
    void guiDraw(sf::RenderWindow &App);
    //Rect<float> guiGetRect();
    void guiSetSelection(bool);
    bool guiGetSelection();

private:
    unsigned int minX;
    sf::Text *mTextButton;
    sf::Sprite *sprBa;
    sf::Texture *gui_blueangle;
    sf::Shape *PolygonButton;
};

/* ************************************************************************** */

/*!
 * \class guiConfirmation
 * \brief docme.
 */
class guiConfirmation : public gui
{
public:
    guiConfirmation(std::string text);
    ~guiConfirmation();

    bool guiLoad();
    int guiExec(sf::Event&);
    void guiDraw(sf::RenderWindow &App);

private:
    sf::Text *txtMessage;
    sf::ConvexShape *polyBackground;
    sf::Sprite *sprWa;
    sf::Sprite *sprBa;
    sf::Texture *gui_whiteangle;
    sf::Texture *gui_blueangle;

    sf::RectangleShape *polyButton1;
    sf::RectangleShape *polyButton2;
    sf::Text *txtButtonYes;
    sf::Text *txtButtonNo;
};

/* ************************************************************************** */

/*!
 * \class guiMenu
 * \brief docme.
 */
class guiMenu : public gui
{
public:
    guiMenu(std::string title);
    virtual bool guiLoad();
    virtual void guiDraw(sf::RenderWindow &App);

private:
    sf::Text *menuTitle;
    sf::Sprite *sprBa;
    sf::Texture *gui_blueangle;
    sf::Sprite *sprWa;
    sf::Texture *gui_whiteangle;
    sf::Shape *PolygonUp;
    sf::Shape *PolygonDown;
};

/* ************************************************************************** */

/*
    // TODO
    gui_scorebox
    gui_timebox
    gui_infobox
    gui_levelbox
*/

/* ************************************************************************** */
#endif // GUI_H
