#ifndef SUBTITLES_STOPWATCH_H
#define SUBTITLES_STOPWATCH_H

#include <QTimer>
#include <QWidget>
#include <QLCDNumber>


class Stopwatch : public QLCDNumber  {
    Q_OBJECT
private:
    QTimer *timer;
    int curTime; //sec
    int timerStart; //msec
public:
    Stopwatch(QWidget *parent);
    int get_time(); //in msec
    bool is_active();
private slots:
    void show_time();
    void incr_time();
public slots:
    void stop();
    void start();
    void set_time(int sec);
};


#endif //SUBTITLES_STOPWATCH_H
