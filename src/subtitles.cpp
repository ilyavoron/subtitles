#include "subtitles.h"

Subtitles::Subtitles() {
    maxTime = (3600 + 546 + 34) * 1000 + 567;
}

bool Subtitles::load_subtitles(const QString &fileName) {
    return true;
}

QString Subtitles::get_subtitles(int time) {

}

int Subtitles::get_max_time() {
    return maxTime;
}