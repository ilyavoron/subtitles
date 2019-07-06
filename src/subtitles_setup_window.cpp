
#include <QString>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QToolButton>
#include <QFileDialog>
#include <QDialog>
#include <QTimeEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QWindow>
#include <QStringList>

#include "subtitles_setup_window.h"
#include "main_menu.h"
#include <iostream>

SubSetupWindow::SubSetupWindow(int num, QWidget *menu, int windowW, int windowH) {
    mainMenu = menu;
    active = false;
    translSubtitlesloaded = false;
    //Timer
    timer = new QTimer(this);
    timer->setInterval(100);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_subtitles()));

    //Window
    this->setFixedSize(windowW, windowH);
    QPalette windowCol;
    windowCol.setColor(QPalette::Window, QColor::fromRgb(255, 255, 255));
    this->setAutoFillBackground(true);
    this->setPalette(windowCol);
    this->setAutoFillBackground(true);

    //Label "Subtitles #"
    QLabel *numlbl = new QLabel("Subtitles " + QString::number(num), this);
    QFont *numlblFont = new QFont("Arial Black", 17);
    numlbl->setFont(*numlblFont);
    numlbl->setGeometry(320, 0, 170, 51);

    //Groupbox "Main subtitles"
    QGroupBox *mainSubBox = new QGroupBox(this);
    mainSubBox->setGeometry(20, 50, 431, 161);
    mainSubBox->setTitle("Main subtitles");

    //Label "Choose subtitles:"
    QLabel *lblChoSub1 = new QLabel("Choose subtitles:", mainSubBox);
    lblChoSub1->setGeometry(30, 30, 201, 16);

    //Combobox1 choose codec
    cboxCodec1 = new QComboBox(mainSubBox);
    QStringList codecList;
    codecList << "UTF-8" << "Windows-1251" << "UTF-16" << "CP949" << "KOI8-R" << "KOI8-U" << "UTF-16BE" << "UTF-16LE";
    cboxCodec1->addItems(codecList);
    cboxCodec1->setEditable(true);
    cboxCodec1->setGeometry(232, 20, 171, 31);

    //LineEdit, path to main subtitles
    pathMainSubs = new QLineEdit(mainSubBox);
    pathMainSubs->setGeometry(30, 60, 350, 30);
    pathMainSubs->setReadOnly(true);

    //Button browse file
    QPushButton *btnBrowseFile1 = new QPushButton("...", mainSubBox);
    btnBrowseFile1->setGeometry(390, 60, 30, 30);
    connect(btnBrowseFile1, SIGNAL(clicked()), this, SLOT(browse_file1()));

    //Button "Configure"
    QPushButton *btnConfigure1 = new QPushButton("Configure", mainSubBox);
    btnConfigure1->setGeometry(30, 110, 93, 31);
    QObject::connect(btnConfigure1, SIGNAL(clicked()), this, SLOT(open_settings1()));

    //Label "Set delay:"
    QLabel *btnSetDel = new QLabel("Set delay:", mainSubBox);
    btnSetDel->setGeometry(230, 110, 81, 31);

    //Spin box, delay
    spBoxDelay1 = new QDoubleSpinBox(mainSubBox);
    spBoxDelay1->setGeometry(320, 110, 61, 31);
    spBoxDelay1->setDecimals(1);
    spBoxDelay1->setMinimum(-1000);
    spBoxDelay1->setMaximum(1000);
    spBoxDelay1->setSingleStep(0.1);

    //Label "sec"
    QLabel *btnSec1 = new QLabel("sec", mainSubBox);
    btnSec1->setGeometry(390, 110, 55, 31);

    //Groupbox "Translation subtitles"
    QGroupBox *translSubBox = new QGroupBox(this);
    translSubBox->setGeometry(20, 231, 431, 161);
    translSubBox->setTitle("Translation subtitles");
    translSubBox->setCheckable(true);
    translSubBox->setChecked(false);

    //Label "Choose subtitles:"
    QLabel *lblChoSub2 = new QLabel("Choose subtitles:", translSubBox);
    lblChoSub2->setGeometry(30, 30, 201, 16);

    //LineEdit, path to translation subtitles
    pathTranslSubs = new QLineEdit(translSubBox);
    pathTranslSubs->setGeometry(30, 60, 350, 30);
    pathTranslSubs->setReadOnly(true);

    //Button browse file
    QPushButton *btnBrowseFile2 = new QPushButton("...", translSubBox);
    btnBrowseFile2->setGeometry(390, 60, 30, 30);
    QObject::connect(btnBrowseFile2, SIGNAL(clicked()), this, SLOT(browse_file2()));

    //Combobox2 choose codec
    cboxCodec2 = new QComboBox(translSubBox);
    swap(codecList[0], codecList[1]);
    cboxCodec2->addItems(codecList);
    cboxCodec2->setEditable(true);
    cboxCodec2->setGeometry(232, 20, 171, 31);

    //Button "Configure"
    QPushButton *btnConfigure2 = new QPushButton("Configure", translSubBox);
    btnConfigure2->setGeometry(30, 110, 93, 31);
    QObject::connect(btnConfigure2, SIGNAL(clicked()), this, SLOT(open_settings2()));

    //Label "Set delay:"
    QLabel *btnSetDel2 = new QLabel("Set delay:", translSubBox);
    btnSetDel2->setGeometry(230, 110, 81, 31);

    //Spin box, delay
    spBoxDelay2 = new QDoubleSpinBox(translSubBox);
    spBoxDelay2->setGeometry(320, 110, 61, 31);
    spBoxDelay2->setDecimals(1);
    spBoxDelay2->setMinimum(-1000);
    spBoxDelay2->setMaximum(1000);
    spBoxDelay2->setSingleStep(0.1);

    //Label "sec"
    QLabel *btnSec2 = new QLabel("sec", translSubBox);
    btnSec2->setGeometry(390, 110, 55, 31);

    //Timer
    clock = new Stopwatch(this);
    clock->move(480, 90);

    //Button "Reset"
    QPushButton *btnReset = new QPushButton("Reset", this);
    btnReset->setGeometry(540, 40, 161, 41);
    QObject::connect(btnReset, SIGNAL(clicked()), this, SLOT(reset_button_pressed()));

    //Button "Set time"
    QPushButton *btnSetTime = new QPushButton("Set time", this);
    btnSetTime->setGeometry(540, 170, 161, 43);
    QObject::connect(btnSetTime, SIGNAL(clicked()), this, SLOT(button_set_time_clicked()));

    //Button "Start"
    btnStart = new QPushButton("Start", this);
    btnStart->setGeometry(540, 230, 161, 43);
    QObject::connect(btnStart, SIGNAL(clicked()), this, SLOT(start_clicked()));

    //hint
    hint1 = new QLabel("          Press 'Space'\n     to run/stop subtitles", this);
    hint1->setGeometry(520, 300, 201, 61);
    hint1->hide();

    fileDialog1 = new QFileDialog(this);
    fileDialog1->setDirectory("C:\\Users\\voron\\Desktop\\subs");
    fileDialog2 = new QFileDialog(this);
    fileDialog2->setDirectory("C:\\Users\\voron\\Desktop\\subs");
    QObject::connect(fileDialog1, SIGNAL(fileSelected(const QString &)), this, SLOT(slot_file_selected1(const QString &)));
    QObject::connect(fileDialog2, SIGNAL(fileSelected(const QString &)), this, SLOT(slot_file_selected2(const QString &)));

    //Dialog set time
    setTimeWindow = new QDialog;
    setTimeWindow->setFixedSize(305, 168);
    setTimeWindow->setModal(true);
    timeEdit = new QTimeEdit(setTimeWindow);
    timeEdit->setGeometry(100, 10, 111, 41);
    timeEdit->setDisplayFormat("hh:mm:ss");
    QPushButton *btnOK = new QPushButton("OK", setTimeWindow);
    btnOK->setGeometry(30, 107, 93, 41);
    QObject::connect(btnOK, SIGNAL(clicked()), this, SLOT(set_time()));
    QPushButton *btnCancel = new QPushButton("Cancel", setTimeWindow);
    btnCancel->setGeometry(180, 110, 93, 41);
    QObject::connect(btnCancel, SIGNAL(clicked()), setTimeWindow, SLOT(close()));

    transSubWindow.set_center_coords(960, 950);
    transSubWindow.change_text_color(QColor::fromRgb(217, 217, 58));
}

void SubSetupWindow::browse_file1() {
    fileDialog1->show();
}

void SubSetupWindow::browse_file2() {
    fileDialog2->show();
}

void SubSetupWindow::slot_file_selected1(const QString &fileName) {
    if (mainSubtitles.load_subtitles(fileName, cboxCodec1->currentText(), 0)) {
        pathMainSubs->setText(fileName);
    }
    else {
        pathMainSubs->setText("Failed to load subtitles");
    }
}

void SubSetupWindow::slot_file_selected2(const QString &fileName) {
    if (transSubtitles.load_subtitles(fileName, cboxCodec2->currentText(), 1)) {
        pathTranslSubs->setText(fileName);
        translSubtitlesloaded = true;
    }
    else {
        pathTranslSubs->setText("Failed to load subtitles");
    }
}

void SubSetupWindow::button_set_time_clicked() {
    int secTime = clock->get_time() / 1000;
    QTime curTime(secTime / 3600, (secTime % 3600) / 60, secTime % 60);
    timeEdit->setTime(curTime);
    secTime = mainSubtitles.get_max_time() / 1000 + (int)spBoxDelay1->value() + 1;
    curTime.setHMS(secTime / 3600, (secTime % 3600) / 60, secTime % 60);
    timeEdit->setMaximumTime(curTime);
    setTimeWindow->show();
}

void SubSetupWindow::set_time() {
    QTime newQTime = timeEdit->time();
    clock->set_time(newQTime.hour() * 3600 + newQTime.minute() * 60 + newQTime.second());
    setTimeWindow->close();
}

void SubSetupWindow::start_clicked() {
    if (active) {
        btnStart->setText("Start");
        active = false;
        clock->stop();
        hint1->hide();
        ((MainMenu*)mainMenu)->starts(-1);
    }
    else {
        btnStart->setText("Stop");
        active = true;
        hint1->show();
        ((MainMenu*)mainMenu)->starts(1);
    }
}

void SubSetupWindow::space_pressed() {
    if (active) {

        /*INPUT ip;
        // Set up a generic keyboard event.
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0; // hardware scan code for key
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        // Press the "Space" key
        ip.ki.wVk = 0x20; // virtual-key code for the "Space" key
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

        // Release the "A" key
        ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &ip, sizeof(INPUT));*/

        INPUT input;
        input.type=INPUT_MOUSE;
        input.mi.dx=0;
        input.mi.dy=0;
        input.mi.dwFlags=(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP);
        input.mi.mouseData=0;
        input.mi.dwExtraInfo=NULL;
        input.mi.time=0;
        SendInput(1,&input,sizeof(INPUT));

        if (clock->is_active()) {
            clock->stop();
            timer->stop();
            if (translSubtitlesloaded) {
                update_trans_subtitles();
                transSubWindow.show();
            }
        }
        else {
            clock->start();
            timer->start();
            if (translSubtitlesloaded) {
                transSubWindow.hide();
            }
        }
    }
}

void SubSetupWindow::reset_button_pressed() {
    clock->set_time(0);
}

void SubSetupWindow::update_subtitles() {
    QVector <QString> str;
    int changed = mainSubtitles.get_subtitles(clock->get_time() - (int)spBoxDelay1->value() * 1000, str);
    if (changed) {
        mainSubWindow.set_text(str);
    }
}

void SubSetupWindow::open_settings1() {
    mainSubWindow.show_settings();
    mainSubWindow.show();
}

void SubSetupWindow::open_settings2() {
    transSubWindow.show_settings();
    transSubWindow.show();
}

void SubSetupWindow::update_trans_subtitles() {
    QVector <QString> str;
    int changed = transSubtitles.get_subtitles(clock->get_time() - (int)spBoxDelay2->value() * 1000, str);
    if (changed) {
        transSubWindow.set_text(str);
    }
}