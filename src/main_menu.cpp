#include "subtitles_setup_window.h"
#include "main_menu.h"
#include <QDebug>
#include <iostream>

MainMenu::MainMenu(QSize screenSize_, int windowW, int windowH) {
    screenSize = screenSize_;
    subtitlesOpen = 0;
    startPressed = 0;
    int buttonW = 2 * windowW / 3, buttonH = windowH / 4;
    subtitlesWindowButton = new QPushButton("Add subtitles", this);
    dictionaryButton = new QPushButton("Dictionary", this);
    this->setFixedSize(windowW, windowH);
    subtitlesWindowButton->setGeometry((windowW - buttonW) / 2, windowH / 6, buttonW, buttonH);
    dictionaryButton->setGeometry((windowW - buttonW) / 2, windowH / 3 + buttonH, buttonW, buttonH);
    subtitlesLayout = new QVBoxLayout;
    subtitlesLayoutWindow = new QWidget;
    //subtitlesLayoutWindow->setWindowFlags(Qt::WindowStaysOnTopHint);
    QPalette windowCol;
    windowCol.setColor(QPalette::Window, QColor::fromRgb(2, 109, 115));
    subtitlesLayoutWindow->setAutoFillBackground(true);
    subtitlesLayoutWindow->setPalette(windowCol);

    QObject::connect(subtitlesWindowButton, SIGNAL(clicked()), this, SLOT(open_new_subtitles()));

    //global hotkeys
    hotkeyManager = new UGlobalHotkeys(subtitlesLayoutWindow);
    QObject::connect(hotkeyManager, SIGNAL(activated(size_t)), this, SLOT(global_hotkey_pressed(size_t)));
}

void MainMenu::open_new_subtitles() {
    if (subtitlesOpen == 2) {
        return;
    }
    SubSetupWindow *newSub = new SubSetupWindow(screenSize, ++subtitlesOpen, this);
    subWindows.append(newSub);
    subtitlesLayout->addWidget(newSub);
    subtitlesLayoutWindow->setLayout(subtitlesLayout);
    subtitlesLayoutWindow->show();
}

void MainMenu::global_hotkey_pressed(size_t id) {
    if (id == 0) {
        for (auto widget : subWindows) {
            widget->stop_pressed();
        }
    }
    if (id == 1) {
        for (auto widget : subWindows) {
            widget->rewind_back_pressed();
        }
    }
    if (id == 2) {
        for (auto widget : subWindows) {
            widget->rewind_forward_pressed();
        }
    }
}

void MainMenu::starts(int add) {
    if (startPressed == 0 && add == 1) {
        hotkeyManager->registerHotkey("T", 0);
        hotkeyManager->registerHotkey("R", 1);
        hotkeyManager->registerHotkey("Y", 2);
    }
    startPressed += add;
    if (startPressed == 0) {
        hotkeyManager->unregisterAllHotkeys();
    }

}