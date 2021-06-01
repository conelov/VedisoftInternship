//
// Created by dym on 22.05.2021.
//
#include "AppEngine.hpp"
#include "src/ConfigLoader/ConfigCache.hpp"
#include "src/ConfigLoader/ConfigLoader.hpp"
#include "src/MarshalJson.hpp"
#include "src/NetManager/NetManager.hpp"
#include "src/models/ModelProviderCard.hpp"
#include "src/utils.hpp"

#include "testValues/values.hpp"

AppEngine::~AppEngine()= default;

AppEngine::AppEngine()
    : QObject({})
    , _config(new ConfigCache(ConfigLoader::load()))
    , _providers(new ProviderVector)
    , _providersModel(new ModelProviderCard(*_providers, this))
    , _net(new NetManager)
{
  QObject::connect(
      _net.get(), &NetManager::error, this, &AppEngine::netErrorHandler);
  QObject::connect(
      _net.get(),
      &NetManager::postMinimal,
      this,
      &AppEngine::netMinimalHandler);
  QObject::connect(
      _net.get(),
      &NetManager::postImageCard,
      this,
      &AppEngine::netCardImagePostHandler);

  QTimer::singleShot(0, this, &AppEngine::afterStartHandler);
}
void AppEngine::afterStartHandler() const
{
#ifndef NDEBUG
  static bool callOnce= true;
  assert(exchange(callOnce, false));
#endif
  _net->getMinimal();
}
void AppEngine::netErrorHandler(quint8 errc) const
{
  qDebug() << "net error, code:" << errc;
  assert(false);
}
void AppEngine::netMinimalHandler(QByteArray const sourceData)
{
  {
    QJsonParseError errorPtr{};
    *_providers= MarshalJson::deserialize(
        QJsonDocument::fromJson(sourceData, &errorPtr));
    assert(errorPtr.error == QJsonParseError::NoError);
  }
  _providersModel->changedAll();
 qDebug() << "netMinimalHandler, imUrl:" << _providers->front().cards.front().image_url;

//  for (ProviderVector::size_type i{}; i < _providers->size(); ++i)
//    for (auto const &card : _providers->at(i).cards) {
//      _net->getImageCard(card, i);
//    }
}
void AppEngine::netCardImagePostHandler(Card const & card, QByteArray const imageData,int providerIndex)
{
  qDebug() << "netImageHandler";

  _providersModel->changedOne(providerIndex);
}
