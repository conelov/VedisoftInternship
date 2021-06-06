//
// Created by dym on 06.06.2021.
//

#ifndef VEDISOFTINTERNSHIP_MARSHALJSONUTILS_HPP
#define VEDISOFTINTERNSHIP_MARSHALJSONUTILS_HPP
#include "src/Logger/Logger.hpp"
#include <QPair>
#include <QStringRef>

auto splitTitle(QStringRef sourceStr)
{
  {
    auto const begin= sourceStr.indexOf('$');
    if (begin == -1) {
      LOG_Warning << QStringLiteral("not found $ sign");
    }
    sourceStr= sourceStr.mid(begin + 1);
  }
  uint cost;
  {
    auto const begin= sourceStr.indexOf(' ');
    if (begin == -1) {
      LOG_Warning << QStringLiteral("no separating space found between number and title");
    }
    bool ok= false;
    cost   = sourceStr.left(begin).toUInt(&ok);
    if (!ok) {
      LOG_Warning << QStringLiteral("money number conversion error");
    }
    sourceStr= sourceStr.mid(begin + 1);
  }
  {
    auto const begin= sourceStr.indexOf(' ');
    if (begin != -1)
      sourceStr= sourceStr.left(begin);
  }
  return qMakePair(sourceStr.toString(), cost);
}

auto splitTitle(QString const &sourceStr)
{
  return splitTitle(sourceStr.midRef(0));
}

#endif // VEDISOFTINTERNSHIP_MARSHALJSONUTILS_HPP
