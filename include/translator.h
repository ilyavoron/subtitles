#ifndef SUBTITLES_TRANSLATOR_H
#define SUBTITLES_TRANSLATOR_H

#include <QNetworkAccessManager>


class Translator : public QObject {
    Q_OBJECT
public:
    Translator();
    void translate(QString text, QString fromL = "en", QString toL = "ru");
    void abort_all();
signals:
    void translated(QString text);
private:
    QNetworkAccessManager *manager;
    QString apiKeyFilename = "api.txt";
private slots:
    void onfinish(QNetworkReply * reply);
};


#endif //SUBTITLES_TRANSLATOR_H
