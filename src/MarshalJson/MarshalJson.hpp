//
// Created by dym on 15.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_MARSHALJSON_HPP
#define VEDISOFTINTERNSHIP_MARSHALJSON_HPP
#include "src/deffwd.hpp"
#include <QtCore>

class QJsonDocument;

class MarshalJson
{
public:
    static ProviderVector deserialize(QJsonDocument const &jsonIn);
};

#endif // VEDISOFTINTERNSHIP_MARSHALJSON_HPP
