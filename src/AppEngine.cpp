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
#include "src/utils.hpp"

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

    QTimer::singleShot(0, this, &AppEngine::afterInitAppHandler);
}

void AppEngine::afterInitAppHandler() const
{
    _net->getMinimal();
}

void AppEngine::netMinimalHandler(QByteArray const sourceData)
{
    QJsonParseError errorPtr {};
    auto const jsonDocument = QJsonDocument::fromJson(sourceData, &errorPtr);
    if (errorPtr.error != QJsonParseError::NoError) {
        LOG_Error << "parsing json system error:" << errorPtr.errorString();
        return;
    }
    MarshalJson marshalJson(jsonDocument);
    if (!marshalJson) {
        auto const err = marshalJson.errorsList().join(';');
        LOG_Error << "parsing json error:" << err;
        emit error("parsing json error: " + err);
        return;
    }

    DBLink dbLink;
    dbLink.storeToDB(*_providers);
    *_providers = dbLink.loadFromDB();

    *_providers = validationForGui(std::move(marshalJson.result()));

    _providersModel->changedAll();
}

ProviderVector AppEngine::validationForGui(ProviderVector &&source)
{
    QVector<decltype(Provider::id)> bindId;
    bindId.reserve(source.size());
    ProviderVector result;
    result.reserve(source.size());
    for (auto &&provider : source) {
        if (!isValidForGui(provider))
            continue;
        if (std::find(bindId.cbegin(), bindId.cend(), provider.id) != bindId.cend())
            continue;
        CardVector cardsValid = validationForGui(std::move(provider.cards));
        if (cardsValid.isEmpty())
            continue;
        bindId.push_back(provider.id);
        provider.cards = std::move(cardsValid);
        result.push_back(std::move(provider));
    }
    std::sort(result.begin(), result.end(), lessIdComparator);
    return result;
}

CardVector AppEngine::validationForGui(CardVector &&source)
{
    QVector<decltype(Provider::id)> bindId;
    bindId.reserve(source.size());
    CardVector result;
    result.reserve(source.size());
    for (auto &&card : source) {
        if (!isValidForGui(card))
            continue;
        if (std::find(bindId.cbegin(), bindId.cend(), card.id) != bindId.cend())
            continue;
        bindId.push_back(card.id);
        result.push_back(std::move(card));
    }
    std::sort(result.begin(), result.end(), lessIdComparator);
    return result;
}