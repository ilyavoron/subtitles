
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

#include "subtitles_setup_window.h"
#include "main_menu.h"

SubSetupWindow::SubSetupWindow(int num, QWidget *menu, int windowW, int windowH) {
    mainMenu = menu;
    active = false;
    //QWidget::grabKeyboard();
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

    //Label "Set delay:"
    QLabel *btnSetDel = new QLabel("Set delay:", mainSubBox);
    btnSetDel->setGeometry(230, 110, 81, 31);

    //Spin box, delay
    QDoubleSpinBox *spBoxDelay1 = new QDoubleSpinBox(mainSubBox);
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
    connect(btnBrowseFile2, SIGNAL(clicked()), this, SLOT(browse_file2()));

    //Button "Configure"
    QPushButton *btnConfigure2 = new QPushButton("Configure", translSubBox);
    btnConfigure2->setGeometry(30, 110, 93, 31);

    //Label "Set delay:"
    QLabel *btnSetDel2 = new QLabel("Set delay:", translSubBox);
    btnSetDel2->setGeometry(230, 110, 81, 31);

    //Spin box, delay
    QDoubleSpinBox *spBoxDelay2 = new QDoubleSpinBox(translSubBox);
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
    fileDialog2 = new QFileDialog(this);
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
}

void SubSetupWindow::browse_file1() {
    fileDialog1->show();
}

void SubSetupWindow::browse_file2() {
    fileDialog2->show();
}

void SubSetupWindow::slot_file_selected1(const QString &fileName) {
    if (mainSubtitles.load_subtitles(fileName)) {
        pathMainSubs->setText(fileName);
    }
    else {
        pathMainSubs->setText("Failed to load subtitles");
    }
}

void SubSetupWindow::slot_file_selected2(const QString &fileName) {
    if (transSubtitles.load_subtitles(fileName)) {
        pathTranslSubs->setText(fileName);
    }
    else {
        pathTranslSubs->setText("Failed to load subtitles");
    }
}

void SubSetupWindow::button_set_time_clicked() {
    int secTime = clock->get_time() / 1000;
    QTime curTime(secTime / 3600, (secTime % 3600) / 60, secTime % 60);
    timeEdit->setTime(curTime);
    secTime = mainSubtitles.get_max_time() / 1000;
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
        if (clock->is_active()) {
            clock->stop();
        }
        else {
            clock->start();
        }
    }
}

void SubSetupWindow::reset_button_pressed() {
    clock->set_time(0);
}