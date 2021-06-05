//
// Created by dym on 31.05.2021.
//

#include "NetManager.hpp"
#include "NetManagerConfig.hpp"
#include "src/Logger/Logger.hpp"
#include "src/entities/Card.hpp"
#include <QNetworkReply>

namespace
{
NetManagerConfig _config= configDefault::netManager;
}

void NetManager::loadState(const NetManagerConfig &state)
{
  _config= state;
}

NetManager::~NetManager()= default;

NetManager::NetManager()
    : QObject({})
    , _manager(new QNetworkAccessManager)
{}

void NetManager::getMinimal()
{
  auto const reply= _manager->get(QNetworkRequest(_config.url));
  QObject::connect(
      reply,
      &QNetworkReply::finished,
      this,
      [this, reply]
      {
        if (reply->error() != QNetworkReply::NoError) {
          LOG_Warning << "Network request execution error"
                      << reply->errorString();
        }
        emit postMinimal(reply->readAll());
        reply->deleteLater();
      });
}