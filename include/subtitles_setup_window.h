#ifndef SUBTITLES_SUBTITLES_CONFIG_WINDOW_H
#define SUBTITLES_SUBTITLES_CONFIG_WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QFileDialog>
#include <QTimeEdit>
#include "subtitles.h"
#include "stopwatch.h"
#include "subtitles_window.h"
#include <QLabel>
#include <QComboBox>
#include <QTimer>
#include <QDoubleSpinBox>
#include <QSettings>

#include <globalHotkey/uglobalhotkeys.h>
#include <globalHotkey/uglobal.h>
#include <globalHotkey/ukeysequence.h>
#include <globalHotkey/uexception.h>
#include <globalHotkey/hotkeymap.h>


class MiniTimer : public QLabel {
    Q_OBJECT
public slots:
    void change_time(QString timeText);
};

class SubSetupWindow : public QFrame {
    Q_OBJECT
private:
    void set_default_settings();

    QLineEdit *pathMainSubs, *pathTranslSubs;
    Subtitles mainSubtitles, transSubtitles;
    SubtitlesWindow mainSubWindow{false, settings}, transSubWindow{true, settings};
    QFileDialog *fileDialog1, *fileDialog2;
    Stopwatch *clock;
    QDialog *setTimeWindow;
    QTimeEdit *timeEdit;
    QPushButton *btnStart;
    QLabel *hint1;
    bool active;
    QComboBox *cboxCodec1, *cboxCodec2;
    QTimer *timer;
    QDoubleSpinBox *spBoxDelay1, *spBoxDelay2;
    bool translSubtitlesloaded;
    MiniTimer miniTimer;
    UGlobalHotkeys *hotkeyManager;
    QSettings *settings;
    QString settingsFile;
public:
    explicit SubSetupWindow(QSize screenSize_, int num = 1, int windowW = 781, int windowH = 422);
public slots:
    void browse_file1();
    void browse_file2();
    void slot_file_selected1(const QString &fileName);
    void slot_file_selected2(const QString &fileName);
    void button_set_time_clicked();
    void set_time();
    void start_clicked();
    void stop_pressed();
    void rewind_back_pressed();
    void rewind_forward_pressed();
    void reset_button_pressed();
    void reset_subs_pressed(); //reset to begin of current second
    void rewind_back_subs_pressed(); //rewind back 0.2sec
    void rewind_forward_subs_pressed(); // rewind forwards 0.2sec
    void update_subtitles();
    void open_settings1();
    void open_settings2();
    void update_trans_subtitles();
    void change_minitimer_visibility();
    void global_hotkey_pressed(size_t id);
};


#endif //SUBTITLES_SUBTITLES_CONFIG_WINDOW_H
