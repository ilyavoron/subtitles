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
public slots:
    void incr_time(int a = 1);
    void stop();
    void start();
    void set_time(int sec);
    void reset_timer();
    void rewind_timer(int a);
signals:
    void time_changed(QString timeString);
};


#endif //SUBTITLES_STOPWATCH_H
