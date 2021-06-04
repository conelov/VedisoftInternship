//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CARD_HPP
#define VEDISOFTINTERNSHIP_CARD_HPP
#include "src/deffwd.hpp"
#include <QString>
#include <QtCore>

#ifndef NDEBUG
  #include <QDebug>
#endif

class Card {
  Q_GADGET

  Q_PROPERTY(bool featured MEMBER featured)
  Q_PROPERTY(uint id MEMBER id)
  Q_PROPERTY(uint codes_count MEMBER codes_count)
  Q_PROPERTY(uint credit MEMBER credit)
  Q_PROPERTY(uint point MEMBER point)

  Q_PROPERTY(QString title MEMBER title)
  Q_PROPERTY(QString image_url MEMBER image_url)
  Q_PROPERTY(QString currency MEMBER currency)
  Q_PROPERTY(QString description MEMBER description)
  Q_PROPERTY(QString redeem_url MEMBER redeem_url)

  Q_PROPERTY(QString creditStr READ creditStr)
  Q_PROPERTY(QString pointStr READ pointStr)

public:
  bool featured DEBUG_INITNULL(false);
  uint id DEBUG_INITNULL(std::numeric_limits<uint>::max()),
      credit DEBUG_INITNULL(std::numeric_limits<uint>::max()),
      point DEBUG_INITNULL(std::numeric_limits<uint>::max()),
      codes_count DEBUG_INITNULL(std::numeric_limits<uint>::max());

  QString title DEUBG_INITNULLSTR, image_url DEUBG_INITNULLSTR,
      currency DEUBG_INITNULLSTR, description DEUBG_INITNULLSTR,
      redeem_url DEUBG_INITNULLSTR;

  QString creditStr() const
  {
    /// TODO: Добавить разделители к числам
    return QString::number(credit);
  }
  QString pointStr() const
  {
    /// TODO: Добавить разделители к числам
    return QString::number(point);
  }
};
Q_DECLARE_METATYPE(Card)

uint qHash(Card const &data);

#endif // VEDISOFTINTERNSHIP_CARD_HPP
