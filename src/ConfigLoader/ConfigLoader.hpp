//
// Created by dym on 13.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#define VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#include "ConfigCache.hpp"

class QString;
class ConfigCache;

class ConfigLoader {
public:
  inline static QString configFileName= QStringLiteral("config.ini");
  static ConfigCache load();
};

#endif // VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
