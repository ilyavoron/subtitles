#include "stopwatch.h"
#include <QTime>
#include <QDebug>
#include <iostream>

Stopwatch::Stopwatch(QWidget *parent) {
    curTime = 0;
    timerStart = 1000;
    this->setParent(parent);
    this->setSegmentStyle(Filled);
    this->setDigitCount(8);
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(incr_time()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
    show_time();
    this->resize(280, 60);
}

void Stopwatch::incr_time(int a) {
    curTime += a;
    int ch = curTime / 3600;
    int cm = (curTime % 3600) / 60;
    int cs = curTime % 60;
    QTime time(ch, cm, cs);
    QString text = time.toString("hh:mm:ss");
    this->display(text);
    emit time_changed(text);
}

void Stopwatch::show_time() {
    timer->setInterval(1000);
    incr_time(0);
}

void Stopwatch::start() {
    timer->start(timerStart);
    timerStart = 1000;
}

void Stopwatch::stop() {
    if(!timer->isActive()){
        return;
    }
    timerStart = timer->remainingTime();
    timer->stop();
}

int Stopwatch::get_time() {
    int rTime = timer->remainingTime();
    if (rTime < 0) {
        rTime = timerStart;
    }
    return curTime * 1000 + (1000 - rTime);
}

void Stopwatch::set_time(int sec) {
    curTime = sec;
    timer->setInterval(1000);
    timerStart = 1000;
    show_time();
}

bool Stopwatch::is_active() {
    return timer->isActive();
}

void Stopwatch::reset_timer() {
    if (timer->isActive()) {
        timer->setInterval(1000);
    }
    else {
        timerStart = 1000;
    }
}

void Stopwatch::rewind_timer(int a) {
    a = -a;
    int remTime = timer->remainingTime();
    if (timer->isActive()) {
        if (remTime + a > 1000) {
            timer->setInterval((remTime + a) % 1000);
            incr_time(-((remTime + a - 1) / 1000));
            return;
        }
        if (remTime + a <= 0) {
            timer->setInterval(1000 - (-(remTime + a)) % 1000);
            incr_time((-(remTime + a) - 1) / 1000 + 1);
            return;
        }
        timer->setInterval(remTime + a);
    }
    else {
        remTime = timerStart;
        if (remTime + a > 1000) {
            timerStart = ((remTime + a) % 1000);
            incr_time(-((remTime + a - 1) / 1000));
            return;
        }
        if (remTime + a <= 0) {
            timerStart = (1000 - (-(remTime + a)) % 1000);
            incr_time((-(remTime + a) - 1) / 1000 + 1);
            return;
        }
        timerStart = (remTime + a);
    }
}