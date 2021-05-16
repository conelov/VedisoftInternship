//
// Created by dym on 14.05.2021.
//
#include "src/MarshalJson.hpp"
#include "src/utils.hpp"
#include <QCoreApplication>
#include <QDataStream>
#include <QFile>
#include <QJsonDocument>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  QJsonDocument jsonDocument;
  {
    QByteArray data;
    {
      QFile file("../testingProj/fileInput/jsonSrc_error.json");
      assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
      data= file.readAll();
    }
    QJsonParseError errorPtr{};
    jsonDocument= QJsonDocument::fromJson(data, &errorPtr);
    assert(errorPtr.error == QJsonParseError::NoError);
  }

  auto const vec= MarshalJson::deserialize(jsonDocument);


  return EXIT_SUCCESS;
}