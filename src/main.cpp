#include <QApplication>
#include "main_menu.h"
#include "subtitles_window.h"
#include <iostream>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QFont mainFont("Arial Black", 9);
    QApplication::setFont(mainFont);

    QSize screenSize = app.screens()[0]->size();
    MainMenu menu(screenSize);
    menu.show();
    //SubtitlesWindow w(&mainFont);
    //w.show();
    return app.exec();
}