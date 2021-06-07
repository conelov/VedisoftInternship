//
// Created by dym on 31.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_NETMANAGER_HPP
#define VEDISOFTINTERNSHIP_NETMANAGER_HPP
#include "src/deffwd.hpp"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class NetManagerConfig;

class NetManager final : public QObject
{
    Q_OBJECT

public:
    static void loadState(NetManagerConfig const &state);

private:
    QScopedPointer<QNetworkAccessManager> _manager;

public:
    ~NetManager() override;
    NetManager();

    void getMinimal();

signals:
    void postMinimal(QByteArray providers) const;
    void error(QString msg) const;
};

#endif // VEDISOFTINTERNSHIP_NETMANAGER_HPP
