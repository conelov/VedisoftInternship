//
// Created by dym on 15.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_MARSHALJSON_HPP
#define VEDISOFTINTERNSHIP_MARSHALJSON_HPP
#include "src/deffwd.hpp"
#include <QStringList>
#include <QVector>

class QJsonDocument;
class QJsonObject;

class MarshalJson
{
    QStringList _errors;

    ProviderVector _providers;

public:
    //    static ProviderVector deserialize(QJsonDocument const &jsonIn);
    MarshalJson() = delete;
    MarshalJson(QJsonDocument const &jsonIn);

    ProviderVector &result();

    operator bool() const { return _errors.isEmpty(); }

    QStringList errorsList() const { return _errors; }

private:
    /// QJsonValue return type
    auto objExtractValue(QJsonObject const &obj, QString const &key);
};

#endif // VEDISOFTINTERNSHIP_MARSHALJSON_HPP
