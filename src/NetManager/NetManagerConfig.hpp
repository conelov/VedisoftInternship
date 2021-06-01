//
// Created by dym on 01.06.2021.
//

#ifndef VEDISOFTINTERNSHIP_NETMANAGERCONFIG_HPP
#define VEDISOFTINTERNSHIP_NETMANAGERCONFIG_HPP
#include <QUrl>

struct NetManagerConfig
{
  QUrl url;
};

inline const NetManagerConfig netManagerDefault{ QStringLiteral(
    "http://office.vedisoft.ru/files/providers.json") };

#endif // VEDISOFTINTERNSHIP_NETMANAGERCONFIG_HPP
