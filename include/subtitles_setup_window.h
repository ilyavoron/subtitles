#ifndef SUBTITLES_SUBTITLES_CONFIG_WINDOW_H
#define SUBTITLES_SUBTITLES_CONFIG_WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QFileDialog>
#include <QTimeEdit>
#include "subtitles.h"
#include "stopwatch.h"
#include <QLabel>

class SubSetupWindow : public QWidget {
    Q_OBJECT
private:
    QLineEdit *pathMainSubs, *pathTranslSubs;
    Subtitles mainSubtitles, transSubtitles;
    QFileDialog *fileDialog1, *fileDialog2;
    Stopwatch *clock;
    QDialog *setTimeWindow;
    QTimeEdit *timeEdit;
    QPushButton *btnStart;
    QLabel *hint1;
    bool active;
    QWidget *mainMenu;
public:
    explicit SubSetupWindow(int num = 1, QWidget *menu = nullptr, int windowW = 781, int windowH = 422);
public slots:
    void browse_file1();
    void browse_file2();
    void slot_file_selected1(const QString &fileName);
    void slot_file_selected2(const QString &fileName);
    void button_set_time_clicked();
    void set_time();
    void start_clicked();
    void space_pressed();
    void reset_button_pressed();
};


#endif //SUBTITLES_SUBTITLES_CONFIG_WINDOW_H
