#include "subtitles_window.h"

SubtitlesWindow::SubtitlesWindow(QFont *_font) {
    font = *_font;
    lbl1 = new QLabel();
    lbl2 = new QLabel();
    lbl1->setFont(font);
    lbl2->setFont(font);
    lbl1->setText("test1");
    lbl2->setText("test2");
    lbl1->setGeometry(0, 0, 100, 50);
    lbl2->setGeometry(0, 50, 100, 50);
    lbl1->setAutoFillBackground(true);
    lbl2->setAutoFillBackground(true);

    //this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setFixedSize(1000, 1000);
    //setAttribute( Qt::WA_OpaquePaintEvent, true );
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    //this->setWindowOpacity(0.5);
    /*QBrush brush;
    brush.setColor(QColor::fromRgb(2, 109, 115));
    QPalette windowCol(brush, brush, brush, brush, brush, brush, brush, brush, brush);
    //windowCol.setColor(QPalette::Window, QColor::fromRgb(2, 109, 115, 0));
    this->setAutoFillBackground(true);
    this->setPalette(windowCol);*/
}