#include <QApplication>
#include "subtitles_setup_window.h"
#include "subtitles_window.h"
#include <QScreen>
#include <iostream>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QFont mainFont("Arial Black", 9);
    QApplication::setFont(mainFont);

    QSize screenSize = app.screens()[0]->size();
    SubSetupWindow newSub(screenSize);
    newSub.show();
    return app.exec();
}