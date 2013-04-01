cmake_minimum_required(VERSION 2.8)


## MapMe v2
###############################

PROJECT(MapMe)
SET(MapMe_VERSION_MAJOR 0)
SET(MapMe_VERSION_MINOR 2)
SET(MapMe_VERSION_PATCH 0)


## MapMe files & directories
###############################

SET(SOURCE_FILES
    src/managers/Singleton.hpp src/managers/ScreenManager.hpp
    src/managers/ConfigurationManager.cpp src/managers/NotificationManager.cpp

    src/main.cpp
    src/cmake_options.h src/typedef.h src/debug.cpp
    src/screenMenu.cpp src/screenGame.cpp
    src/gui.cpp src/notification.cpp
    src/utils.cpp src/timer.cpp src/parser.cpp src/elements.cpp
    src/tinyxml2/tinyxml2.cpp)


## MapMe options
###############################

OPTION(ENABLE_DEBUG "Toggle debug and trace output" ON)
OPTION(ENABLE_COLORS "Toggle colors in console output" ON)

CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/src/cmake_options.h.in"
               "${CMAKE_SOURCE_DIR}/src/cmake_options.h")


## Libraries options
###############################

SET(SFML_STATIC_LIBRARIES OFF)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)


## Software libraries
###############################

FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio REQUIRED)
FIND_PACKAGE(Boost COMPONENTS system filesystem thread REQUIRED)
FIND_PACKAGE(Doxygen)

IF(NOT SFML_FOUND)
    message (FATAL_ERROR "SFML libraries not found!")
ENDIF(NOT SFML_FOUND)

IF(NOT Boost_FOUND)
    message (FATAL_ERROR "Boost libraries not found!")
ENDIF(NOT Boost_FOUND)

IF(NOT DOXYGEN_FOUND)
    message ("Doxygen not found!")
ENDIF(NOT DOXYGEN_FOUND)


## Build options
###############################

# Use "release" and "-O2" for maximum speed.
# Use "debug" and "-O0" if you want better support for GDB and Valgrind.
IF(ENABLE_DEBUG)
    MESSAGE(STATUS "This is a DEBUG build.")
    SET(CMAKE_BUILD_TYPE debug)
    SET(CMAKE_C_FLAGS "-O0 -g")
    SET(CMAKE_CXX_FLAGS "-O0 -g")
ELSE(ENABLE_DEBUG)
    MESSAGE(STATUS "This is a RELEASE build.")
    SET(CMAKE_BUILD_TYPE release)
    SET(CMAKE_C_FLAGS "-O2")
    SET(CMAKE_CXX_FLAGS "-O2")
ENDIF(ENABLE_DEBUG)


## Build
###############################

ADD_EXECUTABLE(MapMe ${SOURCE_FILES})

INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(MapMe ${SFML_LIBRARIES} ${Boost_LIBRARIES})


# Install (optional step)
###############################

INSTALL(TARGETS MapMe DESTINATION /usr/bin)
INSTALL(FILES resources/* DESTINATION /usr/share/mapme/resources)
