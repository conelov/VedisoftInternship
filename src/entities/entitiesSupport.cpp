//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
#define VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
#include "Card.hpp"
#include "Provider.hpp"
#include "src/PropertyGenerator.hpp"
#include "src/utils.hpp"
#include <QVariant>

namespace {
template<typename T>
inline uint qHashTemplate(T &&data)
{
    PropertyGenerator pg { data };
    auto extract = [&pg, first = true]() mutable -> uint {
        for (; pg; ++pg) {
            auto const type = pg.property().type();
            switch (type) {
            default: continue;
            case QVariant::Type::UInt:
                first = false;
                return qHash(pg.read().toUInt());
            case QVariant::Type::Int:
                first = false;
                return qHash(pg.read().toInt());
            case QVariant::Type::String:
                first = false;
                return qHash(pg.read().toString());
            }
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

template<typename T>
QString costToString(T && cost)
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

bool isValidForGui(Card const &card)
{
    auto const range = { card.credit, card.point };
    return std::all_of(range.begin(), range.end(), [](auto const i) {
        if (i > 1'000'000 || i < 0 || i == null_constant_v<decltype(i)>) {
            return false;
        }
        return true;
    });
}

bool isValidForGui(Provider const &provider)
{
    return !isWhiteSpace(provider.title);
}

#endif // VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
