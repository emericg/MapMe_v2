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
 * \brief Menu screen
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * Handle the game menu.
 */

#include "screenMenu.h"
#include "typedef.h"

/* ************************************************************************** */

/*!
 * screenMenu constructor.
 */
screenMenu::screenMenu()
{
    std::cout << "screenMenu::screenMenu" << std::endl;

}

/*!
 * screenMenu destructor.
 */
screenMenu::~screenMenu()
{
    std::cout << "screenMenu::~screenMenu" << std::endl;

    delete cBlack;
    delete cWhite;
    delete cGrey;

    delete menuBar;
    delete menuFont;
    delete menuBackground;

    delete Menu1;
    delete Menu2;
    delete Menu3;
    delete Menu4;

    delete guiConf;
}

/*!
 * \brief Load static resources needed for the main menu.
 */
bool screenMenu::Load(sf::RenderWindow &App)
{
    std::cout << "screenMenu::Load" << std::endl;

    float resRatio = (App.getSize().y / 720.0);

    // Colors
    cBlack = new sf::Color(0, 0, 0, 127);
    cWhite = new sf::Color(255, 255, 255, 255);
    cGrey = new sf::Color(255, 255, 255, 127);

    // Menu background
    menuBackgroundTexture = new sf::Texture();
    if (!menuBackgroundTexture->loadFromFile("resources/gfx/menu/background_720.png"))
    {
        std::cerr << "[error] Loading 'background_720.png'" << std::endl;
        return FAILURE;
    }

    menuBackground = new sf::Sprite();
    menuBackground->setTexture(*menuBackgroundTexture);
    menuBackground->setPosition(0, 0);

    // Resize background to match window size
    if (resRatio != 1 || ((App.getSize().x/App.getSize().y) != 16.0/9.0))
    {
        menuBackground->setScale(resRatio, resRatio);
/*
        // Handle differents screen aspect ratio ?
        if ((App.getSize().x/App.getSize().y) != 16.0/9.0)
        {
            int x1 = (App.getSize().x - menuBackground->getTextureRect().width)/2;
            menuBackground->setPosition(x, 0);
        }
*/
    }

    // Menu bar
    sf::Vector2f pos = sf::Vector2f(0.f, App.getSize().y*0.90);
    sf::Vector2f siz = sf::Vector2f(App.getSize().x, App.getSize().y*0.955);
    menuBar = new sf::RectangleShape();
    menuBar->setPosition(pos);
    menuBar->setSize(siz);
    menuBar->setFillColor(*cBlack);

    // Font
    menuFont = new sf::Font();
    if (!menuFont->loadFromFile("resources/fonts/DejaVuSans.ttf"))
    {
        std::cerr << "[error] Loading 'DejaVuSans.ttf'" << std::endl;
        return FAILURE;
    }

    // Texts
    Menu1 = new sf::Text(gettext("SINGLE PLAYER"));
    Menu2 = new sf::Text(gettext("MULTI PLAYERS"));
    Menu3 = new sf::Text(gettext("OPTIONS"));
    Menu4 = new sf::Text(gettext("EXIT"));

    // Menu init
    menuTable.push_back(Menu1);
    menuTable.push_back(Menu2);
    menuTable.push_back(Menu3);
    menuTable.push_back(Menu4);
    for (int i = 0; i<menuTable.size(); i++)
    {
        menuTable[i]->setColor(*cGrey);
        menuTable[i]->setFont(*menuFont);
        menuTable[i]->setCharacterSize(31*resRatio);
    }
    menuTable[0]->setColor(*cWhite);

    float y = App.getSize().y*0.90;
    float gap = App.getSize().x*0.04;

    Menu1->setPosition(gap, y);
    Menu2->setPosition(Menu1->getPosition().x + Menu1->getGlobalBounds().width + gap, y);
    Menu4->setPosition(App.getSize().x - Menu4->getGlobalBounds().width - gap, y);
    Menu3->setPosition(Menu4->getPosition().x - Menu3->getGlobalBounds().width - gap, y);

    // Confirmation window
    guiConf = new guiConfirmation(gettext("Do you really want to close the game ?"));
    guiConf->guiLoad();
/*
    // Blur shader
    effectBlur = new sf::Shader();
    if (!effectBlur->loadFromFile("resources/shaders/blur.sfx", sf::Shader::Fragment))
    {
        std::cerr << "[error] Loading 'blur.sfx'" << std::endl;
        return FAILURE;
    }
*/
    return true;
}

/*!
 * \fn Run(sf::RenderWindow &App)
 * \brief screenMenu pipeline.
 * \param App The render window.
 * \return docme.
 */
int screenMenu::Run(sf::RenderWindow &App)
{
    std::cout << "screenMenu::Run" << std::endl;
    bool exitconfirmation = false;

    // Notifications
    NotificationManager &NotificationManager = NotificationManager::getInstance();
    NotificationManager.add("Bienvenue dans MapMe !");

    // Events
    sf::Event Event;
    bool Running = true;

    // Menu Loop
    int menu = 0;
    while (Running)
    {
        // Clear screen
        App.clear();

        // Drawing (1/2)
        App.draw(*menuBackground);
        App.draw(*menuBar);

        App.draw(*Menu1);
        App.draw(*Menu2);
        App.draw(*Menu3);
        App.draw(*Menu4);

        // Process confirmation events
        if (exitconfirmation)
        {
            while (App.pollEvent(Event))
            {
                int confirmcode = guiConf->guiExec(Event);

                if (confirmcode == 1)
                    exitconfirmation = false;
                else if (confirmcode == 2)
                    return (-1);
            }
        }
        else
        {
        // Process menu events
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                exitconfirmation != exitconfirmation;
                break;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for (int i = 0; i < menuTable.size(); i++)
                {
                    if (menuTable[i]->getGlobalBounds().contains(Event.mouseMove.x, Event.mouseMove.y))
                    {
                        if (i == 0)
                        {
                            // Goto (1) game screen
                            return (1);
                        }
                        else if (i == menuTable.size() - 1)
                        {
                            exitconfirmation != exitconfirmation;
                            break;
                        }
                    }
                }
            }

            if (Event.type == sf::Event::MouseMoved)
            {
                // Event.mouseMove.x
                // contains the current X position of the mouse cursor, in local coordinates

                // Event.mouseMove.y
                // contains the current Y position of the mouse cursor, in local coordinates

                for (int i = 0; i < menuTable.size(); i++)
                {
                    if (menuTable[i]->getGlobalBounds().contains(Event.mouseMove.x, Event.mouseMove.y))
                    {
                        menuTable[menu]->setColor(*cGrey);
                        menu = i;
                        menuTable[menu]->setColor(*cWhite);
                    }
                }
            }

            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Right:
                        menuTable[menu]->setColor(*cGrey);
                        menu++;
                        if (menu == menuTable.size())
                            menu = 0;
                        if (menu == -1)
                            menu = menuTable.size()-1;
                        menuTable[menu]->setColor(*cWhite);
                        break;
                    case sf::Keyboard::Left:
                        menuTable[menu]->setColor(*cGrey);
                        menu--;
                        if (menu == menuTable.size())
                            menu = 0;
                        if (menu == -1)
                            menu = menuTable.size()-1;
                        menuTable[menu]->setColor(*cWhite);
                        break;
                    case sf::Keyboard::Q:
                        return (-1);
                        break;
                    case sf::Keyboard::Escape:
                        if (exitconfirmation)
                            exitconfirmation = false;
                        else
                            exitconfirmation = true;
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0)
                        {
                            // Goto (1) game screen
                            return (1);
                        }
                        else if (menu == menuTable.size()-1)
                        {
                            if (exitconfirmation)
                                exitconfirmation = false;
                            else
                                exitconfirmation = true;
                            break;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        }

        // Drawing (2/2)
        if (exitconfirmation)
        {
            //App.draw(*effectBlur);
            guiConf->guiDraw(App);
        }

        //guiE->guiDraw(App);
        //mguiMenu->guiDraw(App);

        // Notifications
        NotificationManager.draw(App);

        // Display
        App.display();
    }

    return (-1);
}
