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
 * \file gui.cpp
 * \brief gui system.
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Different gui elements.
 */

#include "gui.h"

/* ************************************************************************** */

gui::gui(/*unsigned int X = 0, unsigned int Y = 0*/)
{
    // Load usefull colors
    cBlue = new sf::Color(84, 126, 137, 255);
    cWhite = new sf::Color(255, 255, 255, 255);
    cWhiteBlue = new sf::Color(67, 114, 126, 190);
    cBlack = new sf::Color(0, 0, 0, 255);

    // Get screen definition and ratio
    ConfigurationManager &confManager = ConfigurationManager::getInstance();
    display_x = static_cast<float>(confManager.getWidth());
    display_y = static_cast<float>(confManager.getHeight());
    display_aspectratio = confManager.getAspectRatio();
    display_resratio = confManager.getDefinitionRatio();

    // Variables initialization
    gui_x = 1;
    gui_y = 0;
    gui_width = 0;
    gui_height = 0;
/*
    * viewportWidth -> contentWidth
    * viewportHeight -> contentHeight
    * viewportX -> contentX
    * viewportY -> contentY
*/
}

gui::~gui()
{
    delete menuFont;

    delete cBlue;
    delete cBlack;
    delete cWhite;
    delete cWhiteBlue;
}

/* ************************************************************************** */

/*!
 * \fn guiElement(GuiPosition p, float width, float height)
 * \brief Constructor for guiElement.
 *
 * Set size and position for this gui element.
 *//*
guiElement::guiElement(GuiPosition p, float width, float height)
{
    // Set size
    gui_width = display_x * width;
    gui_height = display_y * height;

    float borderx = 48 * display_resratio;
    float bordery = 48 * display_resratio;

    // Set position
    if (p == TopLeft)
    {
        gui_x = borderx;
        gui_y = bordery;
    }
    else if (p == TopCenter)
    {
        gui_x = display_x/2.0 - gui_width/2.0;
        gui_y = bordery;
    }
    else if (p == TopRight)
    {
        gui_x = display_x - gui_width - borderx;
        gui_y = bordery;
    }
    else if (p == BottomLeft)
    {
        gui_x = borderx;
        gui_y = display_y - bordery - gui_height;
    }
    else if (p == BottomCenter)
    {
        gui_x = display_x/2.0 - gui_width/2.0;
        gui_y = display_y - bordery - gui_height;
    }
    else if (p == BottomRight)
    {
        gui_x = display_x - gui_width - borderx;
        gui_y = display_y - bordery - gui_height;
    }
    else //if (p == Center)
    {
        gui_x = display_x/2.0 - gui_width/2.0;
        gui_y = display_y/2.0 - gui_height/2.0;
    }
}

bool guiElement::guiLoad()
{
    // Image
    gui_whiteangle = new sf::Texture();
    if (!gui_whiteangle->loadFromFile("resources/gfx/gui/gui_whiteangle_720.png"))
    {
        std::cerr << "[error] Loading 'gui_whiteangle_720.png'" << std::endl;
        return false;
    }
    sprWa = new sf::Sprite();
    sprWa->setTexture(*gui_whiteangle);

    float bs = sprWa->getGlobalBounds().width;

    // Polygon
    Polygon = new sf::Shape();
    Polygon->setPoint(gui_x + bs, gui_y, *cWhite);
    Polygon->setPoint(gui_x + gui_width - bs, gui_y, *cWhite);
    Polygon->setPoint(gui_x + gui_width - bs, gui_y + bs, *cWhite);
    Polygon->setPoint(gui_x + gui_width, gui_y + bs, *cWhite);
    Polygon->setPoint(gui_x + gui_width, gui_y + gui_height - bs, *cWhite);
    Polygon->setPoint(gui_x + gui_width - bs, gui_y + gui_height - bs, *cWhite);
    Polygon->setPoint(gui_x + gui_width - bs, gui_y + gui_height, *cWhite);
    Polygon->setPoint(gui_x + bs, gui_y + gui_height, *cWhite);
    Polygon->setPoint(gui_x + bs, gui_y + gui_height - bs, *cWhite);
    Polygon->setPoint(gui_x, gui_y + gui_height - bs, *cWhite);
    Polygon->setPoint(gui_x, gui_y + bs, *cWhite);
    Polygon->setPoint(gui_x + bs, gui_y + bs, *cWhite);
}

bool guiElement::guiSetSize()
{
    //
}

void guiElement::guiDraw(sf::RenderWindow &App)
{
    // Draw angle
    sprWa->FlipY(false);
    sprWa->setPosition(gui_x, gui_y);
    sprWa->FlipX(false);
    App.draw(*sprWa);
    sprWa->SetX(gui_x + gui_width - sprWa->GetSize().x);
    sprWa->FlipX(true);
    App.draw(*sprWa);

    sprWa->FlipY(true);
    sprWa->setPosition(gui_x, gui_y + gui_height  - sprWa->GetSize().y);
    sprWa->FlipX(false);
    App.draw(*sprWa);
    sprWa->SetX(gui_x + gui_width - sprWa->GetSize().x);
    sprWa->FlipX(true);
    App.draw(*sprWa);

    // Draw polygon
    App.draw(*Polygon);
}
*/
/* ************************************************************************** */
/*
guiMenu::guiMenu(std::string title)
{
    menuTitle = new sf::Text();
    menuTitle->SetString(title.c_str());

    gui_width = display_x*0.25;
    gui_height = display_y*0.50;

    gui_x = (display_x-gui_width)/2.0;
    gui_y = (display_y-gui_height)/2.0 + gui_height*0.10;
}

bool guiMenu::guiLoad()
{
    // Font
    menuFont = new sf::Font();
    if (!menuFont->loadFromFile("resources/fonts/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "[error] Loading 'DejaVuSans-Bold.ttf'" << std::endl;
        return false;
    }

    // Polygons
    PolygonUp = new sf::Shape();
    PolygonUp->setPoint(gui_x, gui_y, *cWhiteBlue);
    PolygonUp->setPoint(gui_x, gui_y - gui_height*0.16 + 16.0, *cWhiteBlue);
    PolygonUp->setPoint(gui_x + 16.0, gui_y - gui_height*0.16 + 16.0, *cWhiteBlue);
    PolygonUp->setPoint(gui_x + 16.0, gui_y - gui_height*0.16, *cWhiteBlue);
    PolygonUp->setPoint(gui_x + gui_width - 16.0, gui_y - gui_height*0.16, *cWhiteBlue);
    PolygonUp->setPoint(gui_x + gui_width - 16.0, gui_y - gui_height*0.16 + 16.0, *cWhiteBlue);
    PolygonUp->setPoint(gui_x + gui_width, gui_y - gui_height*0.16 + 16.0, *cWhiteBlue);
    PolygonUp->setPoint(gui_x + gui_width, gui_y, *cWhiteBlue);

    PolygonDown = new sf::Shape();
    PolygonDown->setPoint(gui_x, gui_y, *cWhite);
    PolygonDown->setPoint(gui_x, gui_y + gui_height*0.8, *cWhite);
    PolygonDown->setPoint(gui_x + 16.0, gui_y + gui_height*0.8, *cWhite);
    PolygonDown->setPoint(gui_x + 16.0, gui_y + gui_height*0.8 + 16.0, *cWhite);
    PolygonDown->setPoint(gui_x + gui_width - 16.0, gui_y + gui_height*0.8 + 16.0, *cWhite);
    PolygonDown->setPoint(gui_x + gui_width - 16.0, gui_y + gui_height*0.8, *cWhite);
    PolygonDown->setPoint(gui_x + gui_width, gui_y + gui_height*0.8, *cWhite);
    PolygonDown->setPoint(gui_x + gui_width, gui_y, *cWhite);

    // Text
    menuTitle->SetFont(*menuFont);
    menuTitle->SetCharacterSize(48.0*display_resratio);
    menuTitle->SetColor(*cWhite);
    menuTitle->SetX(display_x*0.50 - menuTitle->GetRect().Width/2.0);
    menuTitle->SetY(gui_y - gui_height*0.16);

    // Images
    gui_blueangle = new sf::Texture();
    if (!gui_blueangle->loadFromFile("resources/gfx/gui/gui_blueangle_720.png"))
    {
        std::cerr << "[error] Loading 'gui_blueangle_720.png'" << std::endl;
        return false;
    }
    sprBa = new sf::Sprite();
    sprBa->SetImage(*gui_blueangle);
    sprBa->SetY(gui_y - gui_height*0.16);

    gui_whiteangle = new sf::Texture();
    if (!gui_whiteangle->loadFromFile("resources/gfx/gui/gui_whiteangle_720.png"))
    {
        std::cerr << "[error] Loading 'gui_whiteangle_720.png'" << std::endl;
        return false;
    }
    sprWa = new sf::Sprite();
    sprWa->SetImage(*gui_whiteangle);
    sprWa->SetY(gui_y + gui_height*0.80);
    sprWa->FlipY(true);

    return true;
}

void guiMenu::guiDraw(sf::RenderWindow &App)
{
    // Draw
    sprBa->SetX(gui_x);
    sprBa->FlipX(false);
    App.draw(*sprBa);
    sprBa->SetX(gui_x + gui_width - 16.0);
    sprBa->FlipX(true);
    App.draw(*sprBa);

    sprWa->SetX(gui_x);
    sprWa->FlipX(false);
    App.draw(*sprWa);
    sprWa->SetX(gui_x + gui_width - 16.0);
    sprWa->FlipX(true);
    App.draw(*sprWa);

    App.draw(*PolygonUp);
    App.draw(*PolygonDown);

    App.draw(*menuTitle);
}
*/
/* ************************************************************************** */

guiConfirmation::guiConfirmation(std::string text)
{
    // Set text
    txtMessage = new sf::Text();
    txtMessage->setString(text.c_str());

    // Set size and position for this gui element
    gui_width = txtMessage->getGlobalBounds().width*1.1;
    gui_height = display_y*0.16;

    gui_x = (display_x - gui_width)/2.0;
    gui_y = (display_y - gui_height)/2.0 + gui_height*0.10;
}

guiConfirmation::~guiConfirmation()
{
    if( txtMessage )
    {
        delete txtMessage;
        txtMessage = NULL;
    }

    if( polyBackground )
    {
        delete polyBackground;
        polyBackground = NULL;
    }

    if( sprWa )
    {
        delete sprWa;
        sprWa = NULL;
    }

    if( sprBa )
    {
        delete sprBa;
        sprWa = NULL;
    }

    if( gui_whiteangle )
    {
        delete gui_whiteangle;
        gui_whiteangle = NULL;
    }

    if( gui_blueangle )
    {
        delete gui_blueangle;
        gui_blueangle = NULL;
    }
/*
    if( PolygonButton1 )
    {
        delete PolygonButton1;
        PolygonButton1 = NULL;
    }

    if( PolygonButton2 )
    {
        delete PolygonButton2;
        PolygonButton2 = NULL;
    }
*/
    if( txtButtonYes )
    {
        delete txtButtonYes;
        txtButtonYes = NULL;
    }

    if( txtButtonNo )
    {
        delete txtButtonNo;
        txtButtonNo = NULL;
    }
}

bool guiConfirmation::guiLoad()
{
    // Font
    menuFont = new sf::Font();
    if (!menuFont->loadFromFile("resources/fonts/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "[error] Loading 'DejaVuSans-Bold.ttf'" << std::endl;
        return false;
    }

    // Text
    txtMessage->setFont(*menuFont);
    txtMessage->setCharacterSize(30.0*display_resratio);
    txtMessage->setColor(*cWhiteBlue);
    txtMessage->setPosition((display_x*0.50 - txtMessage->getGlobalBounds().width/2.0), (gui_y - gui_height*0.30));

    // Update gui size and position (to follow the text size)
    gui_width = txtMessage->getGlobalBounds().width * 1.1;
    gui_x = (display_x - gui_width)/2.0;

    // Polygon
    polyBackground = new sf::ConvexShape(14);
    polyBackground->setPoint(0, sf::Vector2f(gui_x, gui_y));
    polyBackground->setPoint(1, sf::Vector2f(gui_x, gui_y - gui_height*0.50 + 16.0));
    polyBackground->setPoint(2, sf::Vector2f(gui_x + 16.0, gui_y-gui_height*0.50 + 16.0));
    polyBackground->setPoint(3, sf::Vector2f(gui_x + 16.0, gui_y-gui_height*0.50));
    polyBackground->setPoint(4, sf::Vector2f(gui_x + gui_width - 16.0, gui_y - gui_height*0.50));
    polyBackground->setPoint(5, sf::Vector2f(gui_x + gui_width - 16.0, gui_y - gui_height*0.50 + 16.0));
    polyBackground->setPoint(6, sf::Vector2f(gui_x + gui_width, gui_y - gui_height*0.50 + 16.0));
    polyBackground->setPoint(7, sf::Vector2f(gui_x + gui_width, gui_y));
    polyBackground->setPoint(8, sf::Vector2f(gui_x + gui_width, gui_y + gui_height*0.50));
    polyBackground->setPoint(9, sf::Vector2f(gui_x + gui_width - 16.0, gui_y + gui_height*0.50));
    polyBackground->setPoint(10, sf::Vector2f(gui_x + gui_width - 16.0, gui_y + gui_height*0.50 + 16.0));
    polyBackground->setPoint(11, sf::Vector2f(gui_x + 16.0, gui_y + gui_height*0.50 + 16.0));
    polyBackground->setPoint(12, sf::Vector2f(gui_x + 16.0, gui_y + gui_height*0.50));
    polyBackground->setPoint(13, sf::Vector2f(gui_x, gui_y + gui_height*0.50));

    polyBackground->setFillColor(*cWhite);

    // GUI Button
    //guiButton *ButtonYes = new guiButton(gettext("YES"), 0, 0);
    //guiButton *ButtonNo = new guiButton(gettext("NO"), 0, 0);


    // Text Button
    txtButtonYes = new sf::Text();
    txtButtonYes->setString(gettext("YES"));
    txtButtonYes->setFont(*menuFont);
    txtButtonYes->setCharacterSize(24.0*display_resratio);
    txtButtonYes->setColor(*cWhiteBlue);
    txtButtonYes->setPosition(gui_x + gui_width/2.0 - gui_width*0.10, gui_y + gui_height*0.23);

    txtButtonNo = new sf::Text();
    txtButtonNo->setString(gettext("NO"));
    txtButtonNo->setFont(*menuFont);
    txtButtonNo->setCharacterSize(24.0*display_resratio);
    txtButtonNo->setColor(*cWhiteBlue);
    txtButtonNo->setPosition(gui_x + gui_width/2.0 + gui_width*0.10, gui_y + gui_height*0.23);

    // Images
    gui_whiteangle = new sf::Texture();
    if (!gui_whiteangle->loadFromFile("resources/gfx/gui/gui_whiteangle_720.png"))
    {
        std::cerr << "[error] Loading 'gui_whiteangle_720.png'" << std::endl;
        return false;
    }
    sprWa = new sf::Sprite();
    sprWa->setTexture(*gui_whiteangle);

    gui_blueangle = new sf::Texture();
    if (!gui_blueangle->loadFromFile("resources/gfx/gui/gui_blueangle_720.png"))
    {
        std::cerr << "[error] Loading 'gui_blueangle_720.png'" << std::endl;
        return false;
    }
    sprBa = new sf::Sprite();
    sprBa->setTexture(*gui_blueangle);
    sprBa->setScale(display_resratio, display_resratio);

    return true;
}

int guiConfirmation::guiExec(sf::Event& Event)
{
    if (Event.type == sf::Event::MouseMoved)
    {
        if (txtButtonYes->getGlobalBounds().contains(Event.mouseMove.x, Event.mouseMove.y))
        {
            txtButtonNo->setColor(*cBlue);
            txtButtonYes->setColor(*cBlack);
        }
        else if (txtButtonNo->getGlobalBounds().contains(Event.mouseMove.x, Event.mouseMove.y))
        {
            txtButtonNo->setColor(*cBlack);
            txtButtonYes->setColor(*cBlue);
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (txtButtonYes->getGlobalBounds().contains(Event.mouseMove.x, Event.mouseMove.y))
        {
            return 2;
        }
        else if (txtButtonNo->getGlobalBounds().contains(Event.mouseMove.x, Event.mouseMove.y))
        {
            return 1;
        }
    }

    if (Event.type == sf::Event::KeyPressed)
    {
        switch (Event.key.code)
        {
            case sf::Keyboard::Return:
                if (txtButtonYes->getColor() == *cBlack)
                    return 2;
                else
                    return 1;
            break;

            case sf::Keyboard::Q:
                return 2;
            break;

            case sf::Keyboard::Left:
                txtButtonNo->setColor(*cBlue);
                txtButtonYes->setColor(*cBlack);
            break;

            case sf::Keyboard::Right:
                txtButtonNo->setColor(*cBlack);
                txtButtonYes->setColor(*cBlue);
            break;

            default:
            break;
        }
    }

    return 0;
}

void guiConfirmation::guiDraw(sf::RenderWindow &App)
{
    // Draw angle
    sprWa->setRotation(0);
    sprWa->setPosition(gui_x, gui_y - gui_height*0.50);
    App.draw(*sprWa);

    sprWa->setRotation(90);
    sprWa->setPosition(gui_x + gui_width, gui_y - gui_height*0.50);
    App.draw(*sprWa);

    sprWa->setRotation(270);
    sprWa->setPosition(gui_x, gui_y + gui_height*0.50 + 16.0);
    App.draw(*sprWa);

    sprWa->setRotation(180);
    sprWa->setPosition(gui_x + gui_width, gui_y + gui_height*0.50 + 16.0);
    App.draw(*sprWa);

    // Draw polygon background
    App.draw(*polyBackground);
/*
    // Draw buttons backgrounds
    App.draw(*PolygonButton1);
    App.draw(*PolygonButton2);

    // Draw buttons angles
    sprBa->setRotation(0);
    sprBa->setPosition(mTextButtonYes->getPosition().x, gui_y - gui_height*0.23);
    App.draw(*sprBa);

    sprBa->setRotation(90);
    sprBa->setPosition(mTextButtonYes->getPosition().x + mTextButtonYes->getGlobalBounds().width, gui_y + gui_height*0.23);
    App.draw(*sprBa);

    sprBa->setRotation(270);
    sprBa->setPosition(mTextButtonYes->getPosition().x, gui_y - gui_height*0.23 + 16.0);
    App.draw(*sprBa);

    sprBa->setRotation(180);
    sprBa->setPosition(mTextButtonYes->getPosition().x + mTextButtonYes->getGlobalBounds().width, gui_y + gui_height*0.23 + 16.0);
    App.draw(*sprBa);

    //sprBa->FlipY(false);
    sprBa->setPosition(mTextButtonNo->getPosition().x, gui_y + gui_height*0.23 + 16);
    //sprBa->FlipX(false);
    App.draw(*sprBa);
    sprBa->setPosition(mTextButtonNo->getPosition().x + mTextButtonNo->getGlobalBounds().width, gui_y + gui_height*0.23);
    //sprBa->FlipX(true);
    App.draw(*sprBa);

    //sprBa->FlipY(true);
    sprBa->setPosition(mTextButtonNo->getPosition().x - 16.0, gui_y + gui_height*0.23 + 16.0);
    //sprBa->FlipX(false);
    App.draw(*sprBa);
    sprBa->setPosition(mTextButtonNo->getPosition().x + mTextButtonNo->getGlobalBounds().width, gui_y + gui_height*0.23 + 16.0);
    //sprBa->FlipX(true);
    App.draw(*sprBa);
*/
    App.draw(*txtButtonYes);
    App.draw(*txtButtonNo);

    // Draw title
    App.draw(*txtMessage);
}

/* ************************************************************************** */
/*
guiButton::guiButton(std::string text, float x, float y)
{
    mTextButton = new sf::Text();
    mTextButton->SetString(text.c_str());
    //posX=
    //posY=
}

bool guiButton::guiLoad()
{
    // Text button
    mTextButton->SetFont(*menuFont);
    mTextButton->SetCharacterSize(24.0*display_resratio);
    mTextButton->SetColor(*cWhiteBlue);
    //mTextButton->SetX(x - mTextButton->GetRect().Width/2.0);
    //mTextButton->SetY(y - mTextButton->GetRect().Height/2.0);

    // ??
    gui_height = 32.0*display_resratio;
    gui_width = 64.0*display_resratio;

//   if (mTextButton->GetRect().GetHeight() < height)
//       std::cerr << "[fixme] This text is larger than is button." << std::endl;
//   if( = mTextButton->GetRect().Width * 1.2;


    // Blue angle
    gui_blueangle = new sf::Texture();
    if (!gui_blueangle->loadFromFile("resources/gfx/gui/gui_blueangle_720.png"))
    {
        std::cerr << "[error] Loading 'gui_blueangle_720.png'" << std::endl;
        return false;
    }
    sprBa = new sf::Sprite();
    sprBa->SetImage(*gui_blueangle);
    sprBa->SetScale(display_resratio, display_resratio);

    // First angle
    sprBa->SetY(gui_y + gui_height*0.23);
    sprBa->SetX(mTextButton->GetPosition().x - 16.0);

    // Shape
    PolygonButton = new sf::Shape();
    PolygonButton->setPoint(gui_x, gui_y, *cWhite);
}

void guiButton::guiDraw(sf::RenderWindow &App)
{
    App.draw(*PolygonButton);
    App.draw(*mTextButton);

    // Draw buttons
    sprBa->FlipY(false);
    sprBa->SetY(gui_y + gui_height*0.23);
    sprBa->SetX(mTextButton->GetPosition().x - 16.0);
    sprBa->FlipX(false);
    App.draw(*sprBa);
    sprBa->SetX(mTextButton->GetPosition().x + mTextButton->GetRect().Width);
    sprBa->FlipX(true);
    App.draw(*sprBa);

    sprBa->FlipY(true);
    sprBa->SetY(gui_y + gui_height*0.23 + 16.0);
    sprBa->SetX(mTextButton->GetPosition().x - 16.0);
    sprBa->FlipX(false);
    App.draw(*sprBa);
    sprBa->SetX(mTextButton->GetPosition().x + mTextButton->GetRect().Width);
    sprBa->FlipX(true);
    App.draw(*sprBa);
}
*/
/*
sf::Shape guiButton::getRect()
{
    //
}
*/
/* ************************************************************************** */

/*
bool gui::gui_upmenu(sf::RenderWindow &App)
{
    //
}

bool gui::gui_scorebox()
{
    //
}

bool gui::gui_timebox()
{
    //
}

bool gui::gui_infobox()
{
    //
}

bool gui::gui_levelbox()
{
    //
}
*/
/*
    gui_whiteblueangle = new sf::Texture();
    if (!gui_whiteblueangle->loadFromFile("resources/gfx/gui/gui_whiteblueangle_720.png"))
    {
        std::cerr << "[error] loading 'gui_whiteblueangle_720.png'" << std::endl;
        return false;
    }
*/
/*
    icon_clic = new sf::Texture();
    if (!icon_clic->loadFromFile("resources/gfx/icons/clic.png"))
    {
        std::cerr << "[error] loading 'clic.png'" << std::endl;
        return false;
    }

    icon_time = new sf::Texture();
    if (!icon_time->loadFromFile("resources/gfx/icons/time.png"))
    {
        std::cerr << "[error] loading 'time.png'" << std::endl;
        return false;
    }
*/
/* ************************************************************************** */
