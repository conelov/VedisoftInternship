//
// Created by dym on 31.05.2021.
//

#include "NetManager.hpp"
#include "src/entities/Card.hpp"
#include "src/utils.hpp"
#include <QNetworkReply>

#include <QDebug>

NetManager::~NetManager()= default;
NetManager::NetManager()
    : QObject({})
    , _manager(new QNetworkAccessManager)
{
  _manager->setObjectName(
      QStringLiteral(TO_LITERAL(NetManager)) +
      QStringLiteral(TO_LITERAL(_threadManager)));
}
void NetManager::getMinimal()
{
  auto const reply= _manager->get(QNetworkRequest(_config.url));
  QObject::connect(
      reply,
      &QNetworkReply::finished,
      this,
      [this, reply]
      {
        assert(reply->error() == QNetworkReply::NoError);
        emit postMinimal(reply->readAll());
      });
}
void NetManager::getImageCard(const Card &card, int providerIndex)
{
  assert(card.image_url != DEUBG_NULLSTR);
  auto reply= _manager->get(QNetworkRequest(QUrl(card.image_url)));
  QObject::connect(
      reply,
      &QNetworkReply::finished,
      this,
      [card, reply, providerIndex, this]
      {
        assert(reply->error() == QNetworkReply::NoError);
        emit postImageCard(card, reply->readAll(), providerIndex);
      });
}
