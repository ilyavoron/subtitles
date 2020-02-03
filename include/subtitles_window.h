#ifndef SUBTITLES_SUBTITLES_WINDOW_H
#define SUBTITLES_SUBTITLES_WINDOW_H

#include <QWidget>
#include <QFont>
#include <QLabel>
#include <QApplication>
#include <QTimer>
#include <QSettings>

#include "subtitles_settings.h"
#include "translator.h"

class SubtitlesWindow : public QWidget {
    Q_OBJECT
private:
    SubtitlesSettings *settings;
    QLabel *lbl;
    QVector <QRect> wordsBounds;
    QVector <QString> words;
    QTimer timer;
    int curWordIndex;
    QLabel translWindow;
    Translator translator;

    int string_width(QString &str);
    void paintEvent(QPaintEvent *event) override;

private slots:
    void check_bounds();
    void change_translation_status(bool is_highlighted);
    void show_translation(QString translation);
signals:
    void word_in_focus(bool is_highlighted);
public:
    SubtitlesWindow(bool isTransl, QSettings *settings);
    void set_center_coords(int x, int y);
    void move_center();
    void set_text(QVector <QString> &str);
    void set_text(QString str, int he = 1, int we = 0);
    void change_font(QFont font);
    void show_settings();
    void change_text_color(QColor col);
};


#endif //SUBTITLES_SUBTITLES_WINDOW_H
