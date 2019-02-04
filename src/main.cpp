#include <QApplication>
#include "main_menu.h"
#include "subtitles_window.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QFont mainFont("Arial Black", 9);
    QApplication::setFont(mainFont);

    MainMenu menu;
    menu.show();
    //SubtitlesWindow w(&mainFont);
    //w.show();
    return app.exec();
}