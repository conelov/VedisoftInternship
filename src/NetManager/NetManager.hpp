//
// Created by dym on 31.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_NETMANAGER_HPP
#define VEDISOFTINTERNSHIP_NETMANAGER_HPP
#include "NetManagerConfig.hpp"
#include "src/deffwd.hpp"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class NetManager final: public QObject {
  Q_OBJECT

public:
  enum Errc : quint8
  {
    NoError,
    SomeError,
    count
  };

private:
  inline static NetManagerConfig _config= netManagerDefault;

  //  QThread _threadManager;
  QScopedPointer<QNetworkAccessManager> _manager;

public:
  ~NetManager() override;
  NetManager();

  void getMinimal();
  Q_SIGNAL void postMinimal(QByteArray providers) const;

  void getImageCard(Card const &card, int providerIndex);
  Q_SIGNAL void postImageCard(Card const & card,QByteArray imageData, int providerIndex) const;

  Q_SIGNAL void error(Errc) const;
};

#endif // VEDISOFTINTERNSHIP_NETMANAGER_HPP
