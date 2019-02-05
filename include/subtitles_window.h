#ifndef SUBTITLES_SUBTITLES_WINDOW_H
#define SUBTITLES_SUBTITLES_WINDOW_H

#include <QWidget>
#include <QFont>
#include <QLabel>
#include <QApplication>

class SubtitlesWindow : public QWidget {
    Q_OBJECT
private:
    QFont font;
    QColor backgroundColor, textColor;
    double transp;
    QLabel *lbl;
    int cx, cy;
public:
    SubtitlesWindow(QFont _font = QApplication::font(), QColor _backgroundColor = QColor::fromRgb(0, 0, 0), QColor _textColor = QColor::fromRgb(255, 255, 255), double _transp = 0.3, int _cx = 960, int _cy = 990);
    void paintEvent(QPaintEvent *event);
    void set_center_coords(int x, int y);
    void move_center();
    void set_text(QVector <QString> &str);
    void set_text(QString str, int he = 1, int we = 0);
};


#endif //SUBTITLES_SUBTITLES_WINDOW_H
