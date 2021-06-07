//
// Created by dym on 22.05.2021.
//
#include "AppEngine.hpp"
#include "src/ConfigLoader/ConfigCache.hpp"
#include "src/ConfigLoader/ConfigLoader.hpp"
#include "src/DBLink/DBLink.hpp"
#include "src/Logger/Logger.hpp"
#include "src/MarshalJson/MarshalJson.hpp"
#include "src/NetManager/NetManager.hpp"
#include "src/entities/Provider.hpp"
#include "src/models/ModelProviderCard.hpp"

AppEngine::~AppEngine() = default;

AppEngine::AppEngine()
    : QObject({})
    , _config(new ConfigCache(ConfigLoader::load()))
    , _providers(new ProviderVector)
    , _providersModel(new ModelProviderCard(*_providers, this))
    , _net(new NetManager)
{
    Logger::loadState(_config->logger);
    NetManager::loadState(_config->netManager);

    QObject::connect(_net.get(), &NetManager::postMinimal, this, &AppEngine::netMinimalHandler);
    QObject::connect(_net.get(), &NetManager::error, this, &AppEngine::error);

    QTimer::singleShot(0, this, &AppEngine::afterStartHandler);
}

void AppEngine::afterStartHandler() const
{
    _net->getMinimal();
}

void AppEngine::netMinimalHandler(QByteArray const sourceData)
{
    {
        QJsonParseError errorPtr {};
        *_providers = MarshalJson::deserialize(QJsonDocument::fromJson(sourceData, &errorPtr));
        if (errorPtr.error != QJsonParseError::NoError) {
            LOG_Error << "parsing json error:" << QString::number(errorPtr.error);
        }
    }

    DBLink dbLink;
    dbLink.storeToDB(*_providers);
    *_providers = dbLink.loadFromDB();

    _providersModel->changedAll();
}
