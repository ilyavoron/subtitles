#include "translator.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

Translator::Translator() {
    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
}

void Translator::translate(QString text, QString fromL, QString toL) {
    QJsonObject data;
    data.insert("q", QJsonValue(text));
    data.insert("source",  "en");
    data.insert("target", "ru");
    data.insert("format", "text");

    QFile file(apiKeyFilename);
    file.open(QIODevice::OpenModeFlag::ReadOnly);
    QString key = file.readAll();
    QNetworkRequest request(QUrl("https://translate.yandex.net/api/v1.5/tr.json/translate?key=" +
                                 key +
                                 "&text=" + text +
                                 "&lang=en-ru"));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,
                "application/json; charset=utf-8");
    manager->post(request, QByteArray());
}

void Translator::onfinish(QNetworkReply *reply) {
    QJsonDocument jsonText = QJsonDocument::fromJson(reply->readAll());
    auto translatedText = jsonText.object().value("text").toArray()[0].toString();
    qDebug() << translatedText << "\n";
    emit translated(translatedText);
}

