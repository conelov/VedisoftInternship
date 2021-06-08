//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CARD_HPP
#define VEDISOFTINTERNSHIP_CARD_HPP
#include "src/constant.hpp"
#include <QString>
#include <QtCore>

class Card
{
    Q_GADGET

    Q_PROPERTY(bool featured MEMBER featured)

    Q_PROPERTY(uint id MEMBER id)
    Q_PROPERTY(uint codes_count MEMBER codes_count)

    Q_PROPERTY(int credit MEMBER credit)
    Q_PROPERTY(int point MEMBER point)

    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString image_url MEMBER image_url)
    Q_PROPERTY(QString currency MEMBER currency)
    Q_PROPERTY(QString description MEMBER description)
    Q_PROPERTY(QString redeem_url MEMBER redeem_url)

    Q_PROPERTY(QString creditStr READ creditStr)
    Q_PROPERTY(QString pointStr READ pointStr)

public:
    bool featured DEBUG_INITNULL(bool);

    uint id DEBUG_INITNULL(uint);
    uint codes_count DEBUG_INITNULL(uint);

    int credit DEBUG_INITNULL(int);
    int point DEBUG_INITNULL(int);

    QString title DEBUG_INITNULL(QString);
    QString image_url DEBUG_INITNULL(QString);
    QString currency DEBUG_INITNULL(QString);
    QString description DEBUG_INITNULL(QString);
    QString redeem_url DEBUG_INITNULL(QString);

    Q_INVOKABLE QString creditStr() const;
    Q_INVOKABLE QString pointStr() const;
};
Q_DECLARE_METATYPE(Card)

uint qHash(Card const &data);

bool isValidForGui(Card const &card);

#endif // VEDISOFTINTERNSHIP_CARD_HPP
