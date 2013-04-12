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
 * \file Singleton.hpp
 * \brief Singleton structure.
 * \author ?
 * \date 2008
 *
 * This file provide a singleton implementation.
 */

#ifndef SINGLETON_H
#define SINGLETON_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <cstdlib>

/* ************************************************************************** */

template <class T>

/*!
 * \class Singleton
 * \brief class for manage other classes
 *
 * This class handle unique classes instance on demand.
 */
class Singleton
{
public:
    /*!
     * \brief Create and/or return an unique class instance.
     * \return Return a reference to a class instance.
     */
    static T & getInstance()
    {
        if( !Inst )
        {
            Inst = new T;
        }

        return *Inst;
    }

    /*!
     * Destroy a class instance by calling it's destructor.
     */
    static void destroyInstance()
    {
        delete Inst;
        Inst = NULL;
    }

protected:
    /*!
     * Singleton constructor. This constructor is protected because you must not
     * be able to call it directly,
     */
    Singleton()
    {
        // empty
    }

    /*!
     * Singleton destructor. This destructor is protected because you must not
     * be able to call it directly.
     */
    ~Singleton()
    {
        std::cout << "(this singleton is being destroyed)" << std::endl;
    }

private:
    static T *Inst;               //!< A class instance
    Singleton(Singleton&);        //!< Forbid copies
    void operator = (Singleton&);
};

/*!
 * Declaration of our unique class instance
 */
template <class T> T* Singleton<T>::Inst = NULL;

/* ************************************************************************** */
#endif // SINGLETON_H
