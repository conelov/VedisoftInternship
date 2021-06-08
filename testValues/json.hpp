//
// Created by dym on 06.06.2021.
//

#ifndef VEDISOFTINTERNSHIP_JSON_HPP
#define VEDISOFTINTERNSHIP_JSON_HPP
#include "deffwd_testValues.hpp"
#include <QFile>
#include <QJsonDocument>

namespace tstv {
auto const jsonDocumentSource = [](QString const name) {
    QJsonDocument jsonDocument;
    QByteArray data;
    {
        QFile file(PROJECT_SOURCE_DIR "/" + name);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "file no open:" << PROJECT_SOURCE_DIR "/" + name;
            assert(false);
        }
        data = file.readAll();
    }
    QJsonParseError errorPtr {};
    jsonDocument = QJsonDocument::fromJson(data, &errorPtr);
    assert(errorPtr.error == QJsonParseError::NoError);
    return jsonDocument;
};

QJsonDocument const jsonDocumentSourceError = jsonDocumentSource("jsonSrcError.json");
QJsonDocument const jsonDocumentSourceStd = jsonDocumentSource("jsonSrc.json");
QJsonDocument const jsonDocumentSourceAdvanced = jsonDocumentSource("jsonSrcAdvanced.json");

}

#endif // VEDISOFTINTERNSHIP_JSON_HPP
