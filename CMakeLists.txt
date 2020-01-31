cmake_minimum_required(VERSION 3.12)
project(subtitles)

set(CMAKE_PREFIX_PATH C:/Qt/5.14.1/mingw73_64/lib/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_AUTOMOC ON)

set(SOURCE_FILES src/main.cpp src/main_menu.cpp include/main_menu.h src/subtitles_window.cpp include/subtitles_window.h src/subtitles_setup_window.cpp include/subtitles_setup_window.h src/stopwatch.cpp include/stopwatch.h src/subtitles.cpp include/subtitles.h include/globalHotkey/uglobalhotkeys.cpp include/globalHotkey/uglobalhotkeys.h include/globalHotkey/uglobalhotkeys.cpp include/globalHotkey/uglobalhotkeys.h include/globalHotkey/ukeysequence.cpp include/globalHotkey/ukeysequence.h include/globalHotkey/uexception.cpp include/globalHotkey/uexception.h include/globalHotkey/uglobal.h include/globalHotkey/hotkeymap.h src/subtitles_settings.cpp include/subtitles_settings.h src/translator.cpp include/translator.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(./include/)

find_package(Qt5Core REQUIRED)

find_package(Qt5Widgets REQUIRED)

find_package(Qt5Gui REQUIRED)

find_package(Qt5Network REQUIRED)

include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

add_executable(subtitles ${SOURCE_FILES})

target_link_libraries(subtitles Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network user32)

