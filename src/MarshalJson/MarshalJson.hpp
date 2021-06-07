//
// Created by dym on 15.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_MARSHALJSON_HPP
#define VEDISOFTINTERNSHIP_MARSHALJSON_HPP
#include <QtCore>

class Provider;
class QJsonDocument;

class MarshalJson
{
public:
    static QVector<Provider> deserialize(QJsonDocument const &jsonIn);
};

#endif // VEDISOFTINTERNSHIP_MARSHALJSON_HPP
