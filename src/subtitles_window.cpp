#include "subtitles_window.h"

#include <QPainter>
#include <QPaintEvent>
#include <QBrush>

SubtitlesWindow::SubtitlesWindow(QFont _font, QColor _backgroundColor, QColor _textColor, double _transp, int _cx, int _cy) {
    this->setFocusPolicy(Qt::NoFocus);
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);
    textColor = _textColor;
    backgroundColor = _backgroundColor;
    transp = _transp;
    font = _font;
    this->setFixedSize(400, 50);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    QPalette windowCol;
    windowCol.setColor(QPalette::WindowText, textColor);
    this->setPalette(windowCol);

    lbl = new QLabel("TEST", this);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setGeometry(this->rect());
    lbl->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lbl->setFont(font);
    lbl->setWindowFlags(Qt::WindowStaysOnTopHint);
    cx = _cx;
    cy = _cy;
    move_center();
}

void SubtitlesWindow::paintEvent(QPaintEvent *event) {
    QPainter *painter = new QPainter(this);
    QBrush *brush = new QBrush(backgroundColor);
    painter->setOpacity(transp);
    painter->setPen(backgroundColor);
    painter->setBrush(*brush);
    painter->drawRect(this->rect());
    delete painter;
}

void SubtitlesWindow::set_center_coords(int x, int y) {
    cx = x;
    cy = y;
}

void SubtitlesWindow::move_center() {
    int w = this->width();
    int h = this->height();
    int rx = cx - w / 2;
    int ry = cy - h / 2;
    this->move(rx, ry);
}

void SubtitlesWindow::set_text(QVector<QString> &str) {
    if (str.size() == 0) {
        this->hide();
    }
    QString string = "";
    QLabel tmplbl;
    int w = 0;
    tmplbl.setFont(font);
    for (int i = 0; i < str.size(); i++) {
        string += str[i];
        tmplbl.setText(str[i]);
        w = std::max(w, tmplbl.fontMetrics().boundingRect(tmplbl.text()).width() + 10);
    }
    set_text(string, str.size(), w);
    if (!this->isVisible()) {
        this->show();
    }
}

void SubtitlesWindow::set_text(QString str, int he, int we) {
    lbl->setText(str);
    int w = we;
    if (we == 0) {
        w = lbl->fontMetrics().boundingRect(lbl->text()).width() + 10;
    }
    int h = lbl->fontMetrics().boundingRect(lbl->text()).height() * he + 10;
    this->setFixedSize(w, h);
    lbl->setFixedSize(w, h);
    move_center();
}
