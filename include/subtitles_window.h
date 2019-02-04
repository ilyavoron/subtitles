#ifndef SUBTITLES_SUBTITLES_WINDOW_H
#define SUBTITLES_SUBTITLES_WINDOW_H

#include <QWidget>
#include <QFont>
#include <QLabel>

class SubtitlesWindow : public QWidget {
    Q_OBJECT
private:
    QFont font;
    QLabel *lbl1, *lbl2;
    int cx, cy;
public:
    SubtitlesWindow(QFont *_font);
};


#endif //SUBTITLES_SUBTITLES_WINDOW_H
