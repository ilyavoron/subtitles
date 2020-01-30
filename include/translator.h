#ifndef SUBTITLES_TRANSLATOR_H
#define SUBTITLES_TRANSLATOR_H

#include <QNetworkAccessManager>


class Translator : public QObject {
    Q_OBJECT
public:
    Translator();
public slots:
    void translate(QString text, QString fromL = "en", QString toL = "ru");
signals:
    void translated(QString text);
private:
    QNetworkAccessManager *manager;
    QString apiKeyFilename = "api.txt";
private slots:
    void onfinish(QNetworkReply * reply);
};


#endif //SUBTITLES_TRANSLATOR_H
