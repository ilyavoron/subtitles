#include "subtitles_window.h"

#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QDebug>

SubtitlesWindow::SubtitlesWindow() {
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(400, 50);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    settings = new SubtitlesSettings(this);
    QPalette windowCol;
    windowCol.setColor(QPalette::WindowText, settings->textColor);
    this->setPalette(windowCol);

    lbl = new QLabel("Test", this);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setGeometry(this->rect());
    lbl->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lbl->setFont(settings->font);
    lbl->setWindowFlags(Qt::WindowStaysOnTopHint);
    move_center();

    QVector <QString> tmpv;
    tmpv.append("Test Test Test Test Test\n");
    tmpv.append("Test Test Test Test Test\n");
    this->set_text(tmpv);
    this->hide();
}

void SubtitlesWindow::paintEvent(QPaintEvent *event) {
    QPainter *painter = new QPainter(this);
    QBrush *brush = new QBrush(settings->backgroundColor);
    painter->setOpacity(settings->transp);
    painter->setPen(settings->backgroundColor);
    painter->setBrush(*brush);
    painter->drawRect(this->rect());
    QPalette windowCol;
    windowCol.setColor(QPalette::WindowText, settings->textColor);
    this->setPalette(windowCol);
    delete painter;
}

void SubtitlesWindow::set_center_coords(int x, int y) {
    settings->cx = x;
    settings->spX->setValue(x);
    settings->cy = y;
    settings->spY->setValue(y);
}

void SubtitlesWindow::move_center() {
    int w = this->width();
    int h = this->height();
    int rx = settings->cx - w / 2;
    int ry = settings->cy - h / 2;
    this->move(rx, ry);
}

void SubtitlesWindow::set_text(QVector<QString> &str) {
    QString string = "";
    QLabel tmplbl;
    tmplbl.hide();
    int w = 0;
    tmplbl.setFont(settings->font);
    for (int i = 0; i < str.size(); i++) {
        string += str[i];
        tmplbl.setText(str[i]);
        w = std::max(w, tmplbl.fontMetrics().boundingRect(tmplbl.text()).width() + 10);
    }
    set_text(string, str.size(), w);
}

void SubtitlesWindow::set_text(QString str, int he, int we) {
    int w = we;
    int h;
    if (we == 0) {
        w = 1;
    }
    lbl->setText(str);
    h = lbl->fontMetrics().boundingRect(lbl->text()).height() * he + 10;
    lbl->setFixedSize(w, h);
    this->setFixedSize(w, h);
    move_center();
    this->show();
}

void SubtitlesWindow::change_font(QFont font) {
    lbl->setFont(font);
    QVector <QString> tmpv;
    tmpv.append("Test Test Test Test Test\n");
    tmpv.append("Test Test Test Test Test\n");
    this->set_text(tmpv);
}

void SubtitlesWindow::show_settings() {
    settings->show();
}

void SubtitlesWindow::change_text_color(QColor col) {
    this->settings->change_text_color(col);
}