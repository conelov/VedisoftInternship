//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_PROVIDER_HPP
#define VEDISOFTINTERNSHIP_PROVIDER_HPP
#include "Card.hpp"

class Provider {
  Q_GADGET

  Q_PROPERTY(uint id MEMBER id CONSTANT)
  Q_PROPERTY(QString title MEMBER title CONSTANT)
  Q_PROPERTY(QString image_url MEMBER image_url CONSTANT)
  Q_PROPERTY(QVariantList cards READ cardsVariantList CONSTANT)

public:
  uint id DEBUG_INITNULL(std::numeric_limits<uint>::max());
  QString title DEUBG_INITNULLSTR, image_url DEUBG_INITNULLSTR;
  QVector<Card> cards;

  QVariantList cardsVariantList() const
  {
    QVariantList list;
    for (auto const &card : cards) {
      list.push_back(QVariant::fromValue(card));
    }
    return list;
  }
};
Q_DECLARE_METATYPE(Provider)

uint qHash(Provider const &data);

#endif // VEDISOFTINTERNSHIP_PROVIDER_HPP
