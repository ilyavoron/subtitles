#include "subtitles.h"
#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QTextCodec>
#include <iostream>

Subtitles::Subtitles() {
    maxTime = 0;
    last_ind = 0;
}

bool Subtitles::load_subtitles(QString fileName, QString codecName) {
    QTextCodec *codec = QTextCodec::codecForName(codecName.toUtf8());
    for (int i = 0; i < fileName.size(); i++) {
        if (fileName[i] == '/') {
            fileName = fileName.left(i) + "\\" + fileName.right(fileName.size() - i - 1);
        }
    }
    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    lines.append(Title(0));
    size++;
    QString str;
    while (!file->atEnd()) {
        str = file->readLine();
        if (str == "") {
            break;
        }
        str = (file->readLine());
        int hour = str.mid(0, 2).toInt();
        int min = str.mid(3, 2).toInt();
        int sec = str.mid(6, 2).toInt();
        int msec = str.mid(9, 3).toInt() + (hour * 3600 + min * 60 + sec) * 1000;
        lines.append(Title(msec));
        hour = str.mid(17, 2).toInt();
        min = str.mid(20, 2).toInt();
        sec = str.mid(23, 2).toInt();
        msec = str.mid(26, 3).toInt() + (hour * 3600 + min * 60 + sec) * 1000;
        while (!file->atEnd()) {
            str = codec->toUnicode(file->readLine());
            if (str == "\r\n") {
                break;
            }
            str.replace("\r\n", "\n");
            str.replace("<i>", "");
            str.replace("</i>", "");
            lines[size].strings.append(str);
            lines[size].size++;
        }
        lines.append(Title(msec));
        size += 2;
    }
    maxTime = lines.back().time;
    return true;
}

int Subtitles::get_subtitles(int time, QVector <QString> &str) {
    if (time >= maxTime) {
        if (last_ind == size - 1) {
            return 0;
        }
        last_ind = size - 1;
        return 1;
    }
    if (lines[last_ind].time <= time) {
        if (lines[last_ind + 1].time > time) {
            return 0;
        }
        last_ind++;
        if (last_ind == size - 1 || lines[last_ind + 1].time > time) {
            str = lines[last_ind].strings;
            return 1;
        }
    }
    int left_b = 0, right_b = size;
    while (right_b - left_b != 1) {
        int mid_b = (right_b + left_b) / 2;
        if (lines[mid_b].time > time) {
            right_b = mid_b;
        }
        else {
            left_b = mid_b;
        }
    }
    last_ind = left_b;
    str = lines[last_ind].strings;
    return 1;
}

int Subtitles::get_max_time() {
    return maxTime;
}