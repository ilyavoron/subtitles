#include "subtitles_settings.h"
#include "subtitles_window.h"

#include <QPushButton>
#include <QLabel>

SubtitlesSettings::SubtitlesSettings(QWidget *_subtitlesWindow, QSettings *settings_, bool isTransl){
    this->setFixedSize(259, 397);
    this->setWindowFlags(Qt::WindowTitleHint);
    subtitlesWindow = _subtitlesWindow;
    settings = settings_;
    if (isTransl) {
        keyPrefix = "main/";
    }
    else {
        keyPrefix = "transl/";
    }

    /*font.setFamily("Arial Black");
    font.setPixelSize(31);
    backgroundColor = QColor::fromRgb(0, 0, 0);
    textColor = QColor::fromRgb(255, 255, 255);
    transp = 0.2;
    cx = 960;
    cy = 1020;*/

    QPushButton *btnBackgroundColor = new QPushButton("Background color", this);
    btnBackgroundColor->setGeometry(30, 20, 201, 31);
    QObject::connect(btnBackgroundColor, SIGNAL(clicked()), this, SLOT(open_background_color_window()));
    QObject::connect(&backColorDialog, SIGNAL(colorSelected(const QColor&)), this, SLOT(change_background_color(const QColor&)));

    QPushButton *btnTextColor = new QPushButton("Text color", this);
    btnTextColor->setGeometry(30, 70, 201, 31);
    QObject::connect(btnTextColor, SIGNAL(clicked()), this, SLOT(open_text_color_window()));
    QObject::connect(&textColorDialog, SIGNAL(colorSelected(const QColor&)), this, SLOT(change_text_color(const QColor&)));

    QLabel *lbl1 = new QLabel("Transparency:", this);
    lbl1->setGeometry(20, 110, 131, 31);

    transpSlider = new QSlider(this);
    transpSlider->setOrientation(Qt::Horizontal);
    transpSlider->setGeometry(40, 150, 181, 22);
    transpSlider->setMinimum(0);
    transpSlider->setMaximum(100);
    transpSlider->setValue((int)(this->get_value<double>("subs/opacity") * 100));
    transpSlider->setSingleStep(1);
    connect(transpSlider, SIGNAL(valueChanged(int)), this, SLOT(set_transp(int)));

    QLabel *lbl2 = new QLabel("Font:", this);
    lbl2->setGeometry(20, 190, 91, 21);

    comboBox = new QFontComboBox(this);
    comboBox->setCurrentFont(this->get_value<QFont>("subs/font"));
    comboBox->setGeometry(30, 220, 141, 31);
    QObject::connect(comboBox, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(set_font(const QFont &)));

    spinBox = new QSpinBox(this);
    spinBox->setMaximum(40);
    spinBox->setMinimum(5);
    spinBox->setValue(this->get_value<QFont>("subs/font").pixelSize());
    spinBox->setGeometry(180, 220, 42, 31);
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(set_font_size(int)));

    QLabel *lbl3 = new QLabel("Position:", this);
    lbl3->setGeometry(20, 270, 81, 21);

    QLabel *lbl4 = new QLabel("x:", this);
    QLabel *lbl5 = new QLabel("y:", this);
    lbl4->setGeometry(40, 300, 21, 21);
    lbl5->setGeometry(140, 300, 21, 21);

    spX = new QSpinBox(this);
    spX->setGeometry(60, 300, 61, 22);
    spX->setMaximum(1920);
    spX->setMinimum(0);
    spX->setValue(this->get_value<int>("subs/posx"));
    QObject::connect(spX, SIGNAL(valueChanged(int)), this, SLOT(change_position()));

    spY = new QSpinBox(this);
    spY->setGeometry(161, 300, 61, 22);
    spY->setMaximum(1080);
    spY->setMinimum(0);
    spY->setValue(this->get_value<int>("subs/posy"));
    QObject::connect(spY, SIGNAL(valueChanged(int)), this, SLOT(change_position()));

    QPushButton *btnOk = new QPushButton("OK", this);
    btnOk->setGeometry(20, 350, 93, 28);
    QObject::connect(btnOk, SIGNAL(clicked()), this, SLOT(ok_pressed()));

    QPushButton *btnReset = new QPushButton("Reset", this);
    btnReset->setGeometry(140, 350, 93, 28);
    QObject::connect(btnReset, SIGNAL(clicked()), this, SLOT(reset_settings()));
}

void SubtitlesSettings::open_background_color_window() {
    backColorDialog.show();
}

void SubtitlesSettings::open_text_color_window() {
    textColorDialog.show();
}

void SubtitlesSettings::set_transp(int new_transp) {
    this->set_value("subs/opacity", (double)new_transp / 100);
    ((SubtitlesWindow*)subtitlesWindow)->update();
}

void SubtitlesSettings::set_font(const QFont &new_font) {
    this->set_value("subs/font", new_font);
    ((SubtitlesWindow*)subtitlesWindow)->change_font(new_font);
}

void SubtitlesSettings::set_font_size(int fontSize) {
    QFont font = this->get_value<QFont>("subs/font");
    font.setPixelSize(fontSize);
    set_font(font);
}

void SubtitlesSettings::change_background_color(const QColor &new_color) {
    this->set_value("subs/background_color", new_color);
    subtitlesWindow->update();
}

void SubtitlesSettings::change_text_color(const QColor &new_color) {
    this->set_value("subs/text_color", new_color);
    subtitlesWindow->update();
}

void SubtitlesSettings::change_position() {
    this->set_value("subs/posx", spX->value());
    this->set_value("subs/posy", spY->value());
    ((SubtitlesWindow*)subtitlesWindow)->move_center();
}

/*void SubtitlesSettings::reset_settings(){
    font.setFamily("Arial Black");
    font.setPixelSize(31);
    backgroundColor = QColor::fromRgb(0, 0, 0);
    textColor = QColor::fromRgb(255, 255, 255);
    transp = 0.2;
    cx = 960;
    spX->setValue(cx);
    cy = 1020;
    spY->setValue(cy);
    transpSlider->setValue((int)(transp * 100));
    comboBox->setCurrentFont(font);
    spinBox->setValue(font.pixelSize());
    subtitlesWindow->update();
    ((SubtitlesWindow*)subtitlesWindow)->change_font(font);
}*/

void SubtitlesSettings::ok_pressed() {
    subtitlesWindow->hide();
    this->close();
}

void SubtitlesSettings::set_value(QString key, QVariant val) {
    settings->setValue(keyPrefix + key, val);
}

template <typename T>
T SubtitlesSettings::get_value(QString key) {
    return settings->value(key).value<T>();
}