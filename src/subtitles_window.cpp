#include "subtitles_window.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <iostream>

SubtitlesWindow::SubtitlesWindow(bool isTransl, QSettings *settings_) {
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(400, 50);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    settings = new SubtitlesSettings(this, settings_, isTransl);
    QPalette windowCol;
    windowCol.setColor(QPalette::WindowText, settings->get_value<QColor>("text_color"));
    this->setPalette(windowCol);

    lbl = new QLabel("Test", this);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setGeometry(this->rect());
    lbl->setTextInteractionFlags(Qt::TextSelectableByMouse);
    lbl->setFont(settings->get_value<QFont>("font"));
    lbl->setWindowFlags(Qt::WindowStaysOnTopHint);
    lbl->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    move_center();

    QVector <QString> tmpv;
    tmpv.append("Test Test Test Test Test\n");
    tmpv.append("Test Test Test Test Test\n");
    this->set_text(tmpv);
    this->hide();

    if (!isTransl) {
        timer.setInterval(100);
        timer.start();
        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(check_bounds()));
    }

    curWordIndex = -1;

    translWindow.setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    translWindow.resize(200, 40);
    translWindow.move(0, 0);

    if (isTransl) {
        translWindow.close();
    }

    connect(this, SIGNAL(word_in_focus(bool)), this, SLOT(change_translation_status(bool)));
    connect(&translator, SIGNAL(translated(QString)), this, SLOT(show_translation(QString)));
}

void SubtitlesWindow::paintEvent(QPaintEvent *event) {
    QPainter *painter = new QPainter(this);
    QBrush *brush = new QBrush(settings->get_value<QColor>("background_color"));
    painter->setOpacity(settings->get_value<double>("opacity"));
    painter->setPen(settings->get_value<QColor>("background_color"));
    painter->setBrush(*brush);
    painter->drawRect(this->rect());
    painter->setOpacity(1);
    if (curWordIndex != -1) {
        painter->drawRect(wordsBounds[curWordIndex]);
    }
    QPalette windowCol;
    windowCol.setColor(QPalette::WindowText, settings->get_value<QColor>("text_color"));
    this->setPalette(windowCol);
    delete painter;
}

void SubtitlesWindow::set_center_coords(int x, int y) {
    settings->set_value("posx", x);
    settings->spX->setValue(x);
    settings->set_value("posy", y);
    settings->spY->setValue(y);
}

void SubtitlesWindow::move_center() {
    int w = this->width();
    int h = this->height();
    int rx = settings->get_value<int>("posx") - w / 2;
    int ry = settings->get_value<int>("posy") - h / 2;
    this->move(rx, ry);
}

void SubtitlesWindow::set_text(QVector<QString> &str) {
    if (str.size() == 0) {
        set_text("", 0, 0);
        return;
    }
    words.clear();
    wordsBounds.clear();
    QString string = "";
    QLabel tmplbl;
    tmplbl.hide();
    int w = 0;
    tmplbl.setFont(settings->get_value<QFont>("font"));
    for (int i = 0; i < str.size(); i++) {
        string += str[i];
        tmplbl.setText(str[i]);
        w = std::max(w, tmplbl.fontMetrics().boundingRect(tmplbl.text()).width() + 10);
    }

    //finding words bounds
    int h = lbl->fontMetrics().boundingRect(string).height();
    QString curWord = "";
    int curPos = 0;
    int curRow = 0;
    int curx = w / 2 - string_width(str[curRow]) / 2 - 5; //curString begining x coord
    int cury = 0;
    QString curString = "";
    while (curPos < string.size()) {
        if (string.at(curPos).QChar::isLetter()) {
            curWord += string[curPos];
        }
        else {
            if (curWord != "") {
                words.push_back(curWord);
                wordsBounds.push_back(QRect(curx + string_width(curString) - string_width(curWord), cury,
                                            string_width(curWord) + 5, h + 5));
            }
            curWord = "";
            if (string[curPos] == '\n') {
                cury += h;
                curRow++;
                if (curRow < str.size()) {
                    curx = w / 2 - string_width(str[curRow]) / 2 - 5;
                }
                curString = "";
            }

        }
        curString += string[curPos];
        curPos++;
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

int SubtitlesWindow::string_width(QString &str) {
    return lbl->fontMetrics().boundingRect(str).width();
}

void SubtitlesWindow::check_bounds() {
    QPoint globalCursorPos = QCursor::pos();
    for (int i = 0; i < (int)wordsBounds.size(); i++) {
        QRect wordGlobalBounds = wordsBounds[i];
        wordGlobalBounds.translate(this->x(), this->y());
        if (wordGlobalBounds.contains(globalCursorPos)) {
            if (curWordIndex != i) {
                curWordIndex = i;
                emit word_in_focus(true);
                this->update();
            }
            return;
        }
    }
    if (curWordIndex != -1) {
        emit word_in_focus(false);
        curWordIndex = -1;
        this->update();
    }
}

void SubtitlesWindow::change_translation_status(bool is_highlighted) {
    if (is_highlighted) {
        translator.translate(words[curWordIndex]);
        translWindow.setText("translating...");
        translWindow.show();
    }
    else {
        translWindow.hide();
        translator.abort_all();
    }
}

void SubtitlesWindow::show_translation(QString translation) {
    translWindow.setText(translation);
}