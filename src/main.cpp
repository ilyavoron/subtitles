#include <QApplication>
#include "main_menu.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QFont mainFont("Arial Black", 9);
    QApplication::setFont(mainFont);

    MainMenu menu;
    menu.show();
    return app.exec();
}