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

  Q_PROPERTY(bool featured MEMBER featured CONSTANT)
  Q_PROPERTY(uint id MEMBER id CONSTANT)
  Q_PROPERTY(uint codes_count MEMBER codes_count CONSTANT)
  Q_PROPERTY(uint credit MEMBER credit CONSTANT)
  Q_PROPERTY(uint point MEMBER point CONSTANT)

  Q_PROPERTY(QString title MEMBER title CONSTANT)
  Q_PROPERTY(QString image_url MEMBER image_url CONSTANT)
  Q_PROPERTY(QString currency MEMBER currency CONSTANT)
  Q_PROPERTY(QString description MEMBER description CONSTANT)
  Q_PROPERTY(QString redeem_url MEMBER redeem_url CONSTANT)

  Q_PROPERTY(QString creditStr READ creditStr CONSTANT)
  Q_PROPERTY(QString pointStr READ pointStr CONSTANT)

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
