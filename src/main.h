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
 * \file main.h
 * \brief Main file (HEADER).
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2012
 *
 * Start the program, initialize various stuffs and launch the main menu.
 */

#ifndef MAIN_H
#define MAIN_H
/* ************************************************************************** */

#ifdef WIN32
    // Windows specifics library
    #include "windows.h"
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
    int main(int argc, char **argv);
#endif

/* ************************************************************************** */
#endif // MAIN_H
