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
#include "src/DBLink/DBLink.hpp"

#include "testValues/values.hpp"
#include "src/PropertyGenerator.hpp"

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

  {
    DBLink dbLink;
    dbLink.storeToDB(*_providers);
    *_providers = dbLink.loadFromDB();
  }
  _providersModel->changedAll();

}
void AppEngine::netCardImagePostHandler(Card const & card, QByteArray const imageData,int providerIndex)
{
  qDebug() << "netImageHandler";
  assert(false);
}
