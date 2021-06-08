//
// Created by dym on 20.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_APPENGINE_HPP
#define VEDISOFTINTERNSHIP_APPENGINE_HPP
#include "deffwd.hpp"
#include <QObject>

class AppEngine final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ModelProviderCard *pcModel READ pcModel CONSTANT)

    const QScopedPointer<ConfigCache> _config;
    const QScopedPointer<ProviderVector> _providers;
    const QScopedPointer<ModelProviderCard> _providersModel;
    const QScopedPointer<NetManager> _net;

public:
    ~AppEngine() override;
    AppEngine();

    Q_INVOKABLE ModelProviderCard *pcModel() { return _providersModel.get(); }

public slots:
    void afterInitAppHandler() const;

private slots:
    void netMinimalHandler(QByteArray sourceData);

signals:
    void error(QString msg) const;
};

#endif // VEDISOFTINTERNSHIP_APPENGINE_HPP
