//
// Created by dym on 15.05.2021.
//

#include "MarshalJson.hpp"
#include "src/utils.hpp"

QVector<Provider> MarshalJson::deserialize(const QJsonDocument &jsonIn)
{
  QVector<Provider> providers;
  auto const providers_j=
      jsonIn.object().value(QStringLiteral("providers")).toArray();
  providers.reserve(providers_j.size());

  for (auto it : providers_j) {
    auto const provider1_j= it.toObject();
    Provider provider1;
    
    provider1.id   = provider1_j.value(QStringLiteral("id")).toInt();
    provider1.title= provider1_j.value(QStringLiteral("title")).toString();
    provider1.imageUrl= provider1_j.value(QStringLiteral("image_url")).toString();
    {
      auto const cards_j = provider1_j.value(QStringLiteral("gift_cards")).toArray();
      provider1.linkCards.reserve(cards_j.size());
      
      for(auto it: cards_j){
        auto const card1_j = it.toObject();
        Card card1;

        card1.id         = card1_j.value(QStringLiteral("id")).toInt();
        card1.credits    = card1_j.value(QStringLiteral("credits")).toInt();
        card1.codes_count= card1_j.value(QStringLiteral("codes_count")).toInt();
        card1.featured   = card1_j.value(QStringLiteral("featured")).toBool();
        card1.title      = card1_j.value(QStringLiteral("title")).toString();
        card1.image_url  = card1_j.value(QStringLiteral("image_url")).toString();
        card1.description=
            card1_j.value(QStringLiteral("description")).toString();
        card1.redeem_url= card1_j.value(QStringLiteral("redeem_url")).toString();

        provider1.linkCards.push_back(std::move(card1));
      }
    }

    providers.push_back(std::move(provider1));
  }

  return providers;
}
