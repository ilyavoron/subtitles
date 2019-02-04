#ifndef SUBTITLES_SUBTITLES_H
#define SUBTITLES_SUBTITLES_H

#include <QString>
#include <QVector>

class Subtitles {
private:
    int maxTime;
    int size = 0;
    class Title {
    public:
        QVector <QString> strings;
        int time;
        int size;
        Title(int _time = 0) {
            time = _time;
            size = 0;
        }
    };
    QVector <Title> lines;
    int last_ind;
public:
    Subtitles();
    bool load_subtitles(QString fileName, QString codecName);
    int get_subtitles(int time, QVector <QString> &str); //in msec
    int get_max_time();
};


#endif //SUBTITLES_SUBTITLES_H
