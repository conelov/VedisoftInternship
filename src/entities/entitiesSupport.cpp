//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
#define VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
#include "Card.hpp"
#include "Provider.hpp"
#include "src/PropertyGenerator.hpp"
#include <QVariant>

namespace {
template<typename T>
inline uint qHashTemplate(T &&data)
{
    PropertyGenerator pg { data };
    auto extract = [&pg, first = true]() mutable -> uint {
        for (; pg; ++pg) {
            auto const type = pg.property().type();
            if (type != QVariant::Type::UInt)
                continue;
            first = false;
            return qHash(pg.read().toUInt());
        }
        /// suppression warning
        assert(!first);
        return {};
        ///
    };
    uint hash = extract();
    while (++pg) {
        hash ^= extract();
    }
    return hash;
}

QString costToString(uint const cost)
{
    return QLocale {}.toString(static_cast<double>(cost), 'f', 2);
}
} // namespace

uint qHash(Card const &data)
{
    return qHashTemplate(data);
}

uint qHash(Provider const &data)
{
    uint hash = qHashTemplate(data);
    for (auto const &card : data.cards) {
        hash ^= qHash(card);
    }
    return hash;
}

QString Card::creditStr() const
{
    return QChar('$') + costToString(credit);
}

QString Card::pointStr() const
{
    return costToString(point);
}

QVariantList Provider::cardsVariantList() const
{
    QVariantList list;
    for (auto const &card : cards) {
        list.push_back(QVariant::fromValue(card));
    }
    return list;
}

#endif // VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
