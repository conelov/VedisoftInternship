//
// Created by dym on 01.06.2021.
//

#ifndef VEDISOFTINTERNSHIP_NETMANAGERCONFIG_HPP
#define VEDISOFTINTERNSHIP_NETMANAGERCONFIG_HPP
#include <QUrl>

class NetManagerConfig
{
  Q_GADGET
  Q_PROPERTY(QUrl url MEMBER url)

public:
  QUrl url;
};

namespace configDefault
{
inline const NetManagerConfig netManager{ QStringLiteral(
    "http://office.vedisoft.ru/files/providers.json") };
}
#endif // VEDISOFTINTERNSHIP_NETMANAGERCONFIG_HPP
