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

    /// validation for GUI
    QVector<decltype(Provider::id)> bindId;
    bindId.reserve(marshalJson.result().size());
    /// Этот copy_if перемещает валидные и гарантирует strong порядок id у провайдеров
    /// Перемещаем из MarshalJson.result если
    std::copy_if(std::make_move_iterator(marshalJson.result().begin()),
                 std::make_move_iterator(marshalJson.result().end()),
                 std::back_inserter(*_providers), [&bindId](Provider const &p) {
                     if (!isValidForGui(p))
                         return false;
                     /// id не встречался ранее
                     if (std::find(bindId.cbegin(), bindId.cend(), p.id) != bindId.cend())
                         return false;
                     bindId.push_back(p.id);
                     return true;
                 });
    std::sort(_providers->begin(), _providers->end(),
              [](auto &&lhs, auto &&rhs) { return lhs.id < rhs.id; });
    /// Валидация карт у провайдеров
    for (auto &provider : *_providers) {
        QVector<decltype(Card::id)> bindId;
        bindId.reserve(provider.cards.size());
        provider.cards.erase(
                std::remove_if(provider.cards.begin(), provider.cards.end(),
                               /// Удаляем карты если
                               [&bindId](Card const &card) {
                                   if (!isValidForGui(card))
                                       return true;
                                   /// id не встречался ранее
                                   if (std::find(bindId.cbegin(), bindId.cend(), card.id)
                                       != bindId.cend())
                                       return true;
                                   bindId.push_back(card.id);
                                   return false;
                               }),
                provider.cards.end());
        std::sort(provider.cards.begin(), provider.cards.end(),
                  [](auto &&lhs, auto &&rhs) { return lhs.id < rhs.id; });
    }
    /// Удалить провайдеров без карт
    _providers->erase(
            std::remove_if(_providers->begin(), _providers->end(),
                           [](Provider const &provider) { return provider.cards.isEmpty(); }),
            _providers->end());

    _providersModel->changedAll();
}