#ifndef SUBTITLES_SUBTITLES_H
#define SUBTITLES_SUBTITLES_H

#include <QString>


class Subtitles {
private:
    int maxTime;
public:
    Subtitles();
    bool load_subtitles(const QString &fileName);
    QString get_subtitles(int time); //in msec
    int get_max_time();
};


#endif //SUBTITLES_SUBTITLES_H
