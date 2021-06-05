//
// Created by dym on 06.06.2021.
//

#ifndef VEDISOFTINTERNSHIP_JSON_HPP
#define VEDISOFTINTERNSHIP_JSON_HPP
#include <QJsonDocument>
#include <QFile>

namespace tstv
{
QJsonDocument const jsonDocumentSource= []
{
  QJsonDocument jsonDocument;
  QByteArray data;
  {
    QFile file("../fileInput/jsonSrc_error.json");
    assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
    data= file.readAll();
  }
  QJsonParseError errorPtr{};
  jsonDocument= QJsonDocument::fromJson(data, &errorPtr);
  assert(errorPtr.error == QJsonParseError::NoError);
  return jsonDocument;
}();
}

#endif // VEDISOFTINTERNSHIP_JSON_HPP
