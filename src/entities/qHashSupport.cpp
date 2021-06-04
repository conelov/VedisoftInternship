//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
#define VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
#include "Card.hpp"
#include "Provider.hpp"
#include "src/PropertyGenerator.hpp"
#include <QVariant>

namespace
{
template<typename T>
inline uint qHashTemplate(T &&data)
{
  PropertyGenerator pg{ data };
  auto extract= [&pg, first= true]() mutable -> uint
  {
    for (; pg; ++pg) {
      auto const type= pg.property().type();
      if (type != QVariant::Type::UInt)
        continue;
      first= false;
      return qHash(pg.read().toUInt());
    }
    assert(!first);
    return {};
  };
  uint hash= extract();
  while (++pg) {
    hash^= extract();
  }
  return hash;
}
} // namespace

uint qHash(Card const &data)
{
  return qHashTemplate(data);
}

uint qHash(Provider const &data)
{
  uint hash= qHashTemplate(data);
  for (auto const &card : data.cards) {
    hash^= qHash(card);
  }
  return hash;
}

#endif // VEDISOFTINTERNSHIP_QHASHSUPPORT_CPP
