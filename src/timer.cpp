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
 * \file timer.cpp
 * \brief Simple timer class.
 * \author Emeric GRANGE <emeric.grange@gmail.com>
 * \date 2009
 *
 * This file contain a timer class.
 */

#include "timer.h"

/* ************************************************************************** */

/*!
 * \brief Timer constructor.
 */
Timer::Timer()
{
    // States and variables initialization
    started = false;
    paused  = false;

    startTicks  = 0;
    pausedTicks = 0;
}

/*!
 * \brief Timer destructor.
 */
Timer::~Timer()
{
    // stub
}

/*!
 * \brief Start the timer, or restart it if already running.
 */
void Timer::start()
{
    if (!started)
    {
        // Start the timer
        started = true;
        paused = false;

        // Get actual time.
        Clock.restart();
        startTicks = Clock.getElapsedTime().asMilliseconds();
    }
}

/*!
 * \brief Stop the Timer.
 */
void Timer::stop()
{
    started = false;
    paused = false;
}

/*!
 * \brief Restart the Timer if already running.
 */
void Timer::restart()
{
    if (started)
    {
        Clock.restart();
    }
}

/*!
 * \fn void pause();
 *
 * Pause the timer. It must be running and unpaused, otherwise this function do nothing.
 */
void Timer::pause()
{
    if (started && !paused)
    {
        paused = true;

        // Get the time when paused signal is encountered
        pausedTicks = Clock.getElapsedTime().asMilliseconds() - startTicks;
    }
}

/*!
 * \brief Unpause the timer if paused.
 */
void Timer::unpause()
{
    if (paused)
    {
        paused = false;

        // Remove the paused time from the total time
        startTicks = Clock.getElapsedTime().asMilliseconds() - pausedTicks;
        pausedTicks = 0;
    }
}

/*!
 * \brief Return elapsed time from timer start.
 * \return unsigned time elapsed in milliseconds.
 */
const unsigned Timer::getElapsedTime()
{
    if (started)
    {
        if (paused)
        {
            return pausedTicks;
        }
        else
        {
            return Clock.getElapsedTime().asMilliseconds() - startTicks;
        }
    }
    else
    {
        return 0;
    }
}

/*!
 * \brief Return Timer global state.
 * \return true if Timer is started, false otherwise.
 */
const bool Timer::isStarted()
{
    return started;
}

/*!
 * \brief Return Timer pause state.
 * \return true if Timer is paused, false otherwise.
 */
const bool Timer::isPaused()
{
    return paused;
}

/* ************************************************************************** */
