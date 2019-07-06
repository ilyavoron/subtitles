#ifndef SUBTITLES_MAIN_MENU_H
#define SUBTITLES_MAIN_MENU_H

#include <QWidget>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QVector>
#include <subtitles_setup_window.h>

#include <globalHotkey/uglobalhotkeys.h>
#include <globalHotkey/uglobal.h>
#include <globalHotkey/ukeysequence.h>
#include <globalHotkey/uexception.h>
#include <globalHotkey/hotkeymap.h>


class MainMenu : public QMainWindow {
    Q_OBJECT
private:
    QPushButton *subtitlesWindowButton, *dictionaryButton;
    QVBoxLayout *subtitlesLayout;
    QWidget *subtitlesLayoutWindow;
    QVector <SubSetupWindow*> subWindows;
    int subtitlesOpen;
    int startPressed;
    UGlobalHotkeys *hotkeyManager;
public:
    explicit MainMenu(int windowW = 300, int windowH = 200);
    void starts(int add);
public slots:
    void open_new_subtitles();
    void global_hotkey_pressed(size_t id);
};


#endif //SUBTITLES_MAIN_MENU_H
