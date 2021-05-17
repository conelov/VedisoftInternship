//
// Created by dym on 15.05.2021.
//

#include "MarshalJson.hpp"
#include "src/entities/aggregates.hpp"

#if defined(MARSHALJSON_DESERIALIZE_CHECK) ||                                  \
    defined(MARSHALJSON_DESERIALIZE_VALUE)
  #error "^^ redefinition"
#endif

#define MARSHALJSON_DESERIALIZE_CHECK

/// TODO: remove throw exception
#ifdef MARSHALJSON_DESERIALIZE_CHECK
  #define MARSHALJSON_DESERIALIZE_VALUE(source, key)                           \
    [&source, &key]                                                            \
    {                                                                          \
      auto val= source.value(key);                                             \
      if (val.isUndefined())                                                   \
        throw std::invalid_argument(                                           \
            std::string("MarshalJson::deserialize: no value for the "          \
                        "requested key (") +                                   \
            key.toStdString() + ')');                                          \
      return val;                                                              \
    }()
#else
  #define MARSHALJSON_DESERIALIZE_VALUE(source, key)                           \
    source.value(key)
#endif

QJsonValue objExtractValue(QJsonObject const &obj, QString const &key)
{
  return MARSHALJSON_DESERIALIZE_VALUE(obj, key);
}

QVector<Provider> MarshalJson::deserialize(const QJsonDocument &jsonIn)
{
  QVector<Provider> providers;
  auto const providers_j=
      objExtractValue(jsonIn.object(), QStringLiteral("providers")).toArray();
  providers.reserve(providers_j.size());

  for (auto it : providers_j) {
    auto const provider1_j= it.toObject();
    Provider provider1;

    provider1.id= objExtractValue(provider1_j, QStringLiteral("id")).toInt();
    provider1.title=
        objExtractValue(provider1_j, QStringLiteral("title")).toString();
    provider1.imageUrl=
        objExtractValue(provider1_j, QStringLiteral("image_url")).toString();
    {
      auto const cards_j=
          objExtractValue(provider1_j, QStringLiteral("gift_cards")).toArray();
      provider1.linkCards.reserve(cards_j.size());

      for (auto it : cards_j) {
        auto const card1_j= it.toObject();
        Card card1;

        card1.id= objExtractValue(provider1_j, QStringLiteral("id")).toInt();
        card1.credits=
            objExtractValue(card1_j, QStringLiteral("credits")).toInt();
        card1.codes_count=
            objExtractValue(card1_j, QStringLiteral("codes_count")).toInt();
        card1.featured=
            objExtractValue(card1_j, QStringLiteral("featured")).toBool();
        card1.title=
            objExtractValue(card1_j, QStringLiteral("title")).toString();
        card1.image_url=
            objExtractValue(card1_j, QStringLiteral("image_url")).toString();
        card1.description=
            objExtractValue(card1_j, QStringLiteral("description")).toString();
        card1.redeem_url=
            objExtractValue(card1_j, QStringLiteral("redeem_url")).toString();

        provider1.linkCards.push_back(std::move(card1));
      }
    }

    providers.push_back(std::move(provider1));
  }

  return providers;
}
