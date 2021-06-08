//
// Created by dym on 06.06.2021.
//

#ifndef VEDISOFTINTERNSHIP_MARSHALJSONUTILS_HPP
#define VEDISOFTINTERNSHIP_MARSHALJSONUTILS_HPP
#include "src/Logger/Logger.hpp"
#include "src/constant.hpp"
#include <QPair>
#include <QStringRef>
#include "src/entities/Card.hpp"

inline auto splitTitle(QStringRef sourceStr)
{
    decltype(Card::credit) cost;
    {
        auto const begin = sourceStr.indexOf('$');
        if (begin == -1) {
            LOG_Warning << QStringLiteral("not found $ sign");
            return qMakePair(sourceStr.toString(), null_constant_v<decltype(cost)>);
        }
        sourceStr = sourceStr.mid(begin + 1);
    }
    {
        auto const begin = sourceStr.indexOf(' ');
        if (begin == -1) {
            LOG_Warning << QStringLiteral("no separating space found between number and title");
            return qMakePair(sourceStr.toString(), null_constant_v<decltype(cost)>);
        }
        bool ok = false;
        cost = sourceStr.left(begin).toInt(&ok);
        if (!ok) {
            LOG_Warning << QStringLiteral("money number conversion error");
            return qMakePair(sourceStr.toString(), null_constant_v<decltype(cost)>);
        }
        sourceStr = sourceStr.mid(begin + 1);
    }
    {
        auto const begin = sourceStr.indexOf(' ');
        if (begin != -1)
            sourceStr = sourceStr.left(begin);
    }
    return qMakePair(sourceStr.toString(), cost);
}

inline auto splitTitle(QString const &sourceStr)
{
    return splitTitle(sourceStr.midRef(0));
}

#endif // VEDISOFTINTERNSHIP_MARSHALJSONUTILS_HPP
