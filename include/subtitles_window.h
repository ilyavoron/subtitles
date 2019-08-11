#ifndef SUBTITLES_SUBTITLES_WINDOW_H
#define SUBTITLES_SUBTITLES_WINDOW_H

#include <QWidget>
#include <QFont>
#include <QLabel>
#include <QApplication>
#include <QTimer>

#include "subtitles_settings.h"

class SubtitlesWindow : public QWidget {
    Q_OBJECT
private:
    class TranslationWindow : public QWidget {
    private:
        QLabel wordToTranslate{this};
    public:
        TranslationWindow();
        void translate(QString word);
    };

    SubtitlesSettings *settings;
    QLabel *lbl;
    QVector <QRect> wordsBounds;
    QVector <QString> words;
    QTimer timer;
    int curWordIndex;
    TranslationWindow translWindow;

    int string_width(QString &str);
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;

private slots:
    void check_bounds();
public:
    SubtitlesWindow(bool isTransl = false);
    void set_center_coords(int x, int y);
    void move_center();
    void set_text(QVector <QString> &str);
    void set_text(QString str, int he = 1, int we = 0);
    void change_font(QFont font);
    void show_settings();
    void change_text_color(QColor col);
};


#endif //SUBTITLES_SUBTITLES_WINDOW_H
