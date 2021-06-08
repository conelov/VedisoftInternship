//
// Created by dym on 15.05.2021.
//

#include "MarshalJson.hpp"
#include "MarshalJsonUtils.hpp"
#include "src/Logger/Logger.hpp"
#include "src/entities/Card.hpp"
#include "src/entities/Provider.hpp"

namespace {
auto const _errorPrefix_UndefinedKey = QStringLiteral("undefined key: ");
}

#if defined(MARSHALJSON_DESERIALIZE_CHECK) || defined(MARSHALJSON_DESERIALIZE_VALUE)
#    error "^^ redefinition"
#endif

#define MARSHALJSON_DESERIALIZE_CHECK

#ifdef MARSHALJSON_DESERIALIZE_CHECK
#    define MARSHALJSON_DESERIALIZE_VALUE(source, key)                                             \
        [this, &source, &key] {                                                                    \
            auto val = source.value(key);                                                          \
            if (val.isUndefined()) {                                                               \
                _errors.push_back(_errorPrefix_UndefinedKey + key);                                \
                Logger { "deserialize", "MarshalJson", 0, Logger::Error } << _errors.back();       \
            }                                                                                      \
            return val;                                                                            \
        }()
#else
#    define MARSHALJSON_DESERIALIZE_VALUE(source, key) source.value(key)
#endif

auto MarshalJson::objExtractValue(QJsonObject const &obj, QString const &key)
{
    return MARSHALJSON_DESERIALIZE_VALUE(obj, key);
}

MarshalJson::MarshalJson(const QJsonDocument &jsonIn)
{
    auto const providers_j =
            objExtractValue(jsonIn.object(), QStringLiteral("providers")).toArray();
    _providers.reserve(providers_j.size());

    for (auto it : providers_j) {
        auto const provider1_j = it.toObject();
        Provider provider1;

        provider1.id = objExtractValue(provider1_j, QStringLiteral("id")).toInt();
        provider1.title = objExtractValue(provider1_j, QStringLiteral("title")).toString();
        provider1.image_url = objExtractValue(provider1_j, QStringLiteral("image_url")).toString();
        {
            auto const cards_j =
                    objExtractValue(provider1_j, QStringLiteral("gift_cards")).toArray();
            provider1.cards.reserve(cards_j.size());

            for (auto it : cards_j) {
                auto const card1_j = it.toObject();
                Card card1;

                card1.id = objExtractValue(provider1_j, QStringLiteral("id")).toInt();
                card1.featured = objExtractValue(card1_j, QStringLiteral("featured")).toBool();
                {
                    auto [str, cost] = splitTitle(
                            objExtractValue(card1_j, QStringLiteral("title")).toString());
                    card1.title = std::move(str);
                    card1.credit = cost;
                }
                card1.point = objExtractValue(card1_j, QStringLiteral("credits")).toInt();
                card1.image_url = objExtractValue(card1_j, QStringLiteral("image_url")).toString();
                card1.codes_count = objExtractValue(card1_j, QStringLiteral("codes_count")).toInt();
                card1.currency = objExtractValue(card1_j, QStringLiteral("currency")).toInt();
                card1.description =
                        objExtractValue(card1_j, QStringLiteral("description")).toString();
                card1.redeem_url =
                        objExtractValue(card1_j, QStringLiteral("redeem_url")).toString();

                provider1.cards.push_back(std::move(card1));
            }
        }

        _providers.push_back(std::move(provider1));
    }
}
ProviderVector MarshalJson::result() const
{
    return _providers;
}
