//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_PROVIDER_HPP
#define VEDISOFTINTERNSHIP_PROVIDER_HPP
#include "Card.hpp"

class Provider
{
    Q_GADGET

    Q_PROPERTY(uint id MEMBER id)
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString image_url MEMBER image_url)
    Q_PROPERTY(QVariantList cards READ cardsVariantList)

public:
    uint id DEBUG_INITNULL(std::numeric_limits<uint>::max());
    QString title DEUBG_INITNULLSTR;
    QString image_url DEUBG_INITNULLSTR;
    QVector<Card> cards;

    QVariantList cardsVariantList() const;
};
Q_DECLARE_METATYPE(Provider)

uint qHash(Provider const &data);

#endif // VEDISOFTINTERNSHIP_PROVIDER_HPP
