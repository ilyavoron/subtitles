#include "translator.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>
#include <QFile>

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
    abort_all();
    manager->post(request, QByteArray());
}

void Translator::onfinish(QNetworkReply *reply) {
    if (!reply->isReadable()) {
        return;
    }
    QJsonArray jsonText = QJsonDocument::fromJson(reply->readAll()).object().value("text").toArray();
    if (jsonText.size() == 0) {
        return;
    }
    auto translatedText = jsonText[0].toString();
    emit translated(translatedText);
    reply->deleteLater();
}

void Translator::abort_all() {
    foreach (auto &reply, manager->findChildren<QNetworkReply *>()) {
        if (reply->isReadable()) {
            reply->abort();
        }
    }
}
