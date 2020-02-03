#ifndef SUBTITLES_SUBTITLES_SETTINGS_H
#define SUBTITLES_SUBTITLES_SETTINGS_H

#include <QWidget>
#include <QColorDialog>
#include <QSpinBox>
#include <QSlider>
#include <QFontComboBox>
#include <QSettings>

class SubtitlesSettings : public QDialog {
    Q_OBJECT
private:

    QWidget *subtitlesWindow;
public:
    SubtitlesSettings(QWidget *_subtitlesWindow, QSettings *settings_, bool isTransl);
    void set_value(QString key, QVariant val);
    template <typename T>
    T get_value(QString key);

    QSettings *settings;
    QString keyPrefix;
    QColorDialog backColorDialog, textColorDialog;
    QSpinBox *spX, *spY;
    QSlider *transpSlider;
    QFontComboBox *comboBox;
    QSpinBox *spinBox;
public slots:
    void open_background_color_window();
    void open_text_color_window();
    void set_transp(int new_transp);
    void set_font(const QFont &new_font);
    void set_font_size(int fontSize);
    void change_background_color(const QColor& new_color);
    void change_text_color(const QColor &new_color);
    void change_position();
    void reset_settings();
    void ok_pressed();
};

#endif //SUBTITLES_SUBTITLES_SETTINGS_H
