//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_AGGREGATES_HPP
#define VEDISOFTINTERNSHIP_AGGREGATES_HPP
#include "src/deffwd.hpp"
#include <QPixmap>
#include <QVariant>

namespace qml
{
class Card {
  Q_GADGET
  Q_PROPERTY(QString credit MEMBER credit)
  Q_PROPERTY(QString point MEMBER point)

public:
  QString credit, point;
};
} // namespace qml
Q_DECLARE_METATYPE(qml::Card)

namespace qml
{
class Provider {
  Q_GADGET
  Q_PROPERTY(QString title MEMBER title)
  Q_PROPERTY(QVariantList cards MEMBER cards)

public:
  QString title;
  QVariantList cards;
};
} // namespace qml
Q_DECLARE_METATYPE(qml::Provider)

class Card {
public:
  bool featured;
  qsizetype id DEBUG_INITNULL(std::numeric_limits<qsizetype>::max()),
      credits DEBUG_INITNULL(std::numeric_limits<qsizetype>::max()),
      codes_count DEBUG_INITNULL(std::numeric_limits<qsizetype>::max());
  QString title DEUBG_INITNULLSTR, image_url DEUBG_INITNULLSTR,
      currency DEUBG_INITNULLSTR, description DEUBG_INITNULLSTR,
      redeem_url DEUBG_INITNULLSTR;
};

class Provider {
public:
  qsizetype id DEBUG_INITNULL(std::numeric_limits<qsizetype>::max());
  QString title DEUBG_INITNULLSTR, imageUrl DEUBG_INITNULLSTR;
  QVector<Card> linkCards;
};

using ProviderVector= QVector<Provider>;
#endif // VEDISOFTINTERNSHIP_AGGREGATES_HPP
