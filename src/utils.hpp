//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_UTILS_HPP
#define VEDISOFTINTERNSHIP_UTILS_HPP
#include "../src/Deffwd.hpp"
#include <QPixmap>

namespace qml
{
class Card {
  Q_GADGET

public:
  quint32 cash DEBUG_INITNULL(std::numeric_limits<quint32>::max()), point
      DEBUG_INITNULL(std::numeric_limits<quint32>::max());
  QPixmap image;
};

class Provider {
  Q_GADGET

public:
  qsizetype id DEBUG_INITNULL(std::numeric_limits<qsizetype>::max());
  QString title DEUBG_INITNULLSTR;
  QVector<Card *> linkCards;
};
} // namespace qml

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
#endif // VEDISOFTINTERNSHIP_UTILS_HPP
