//
// Created by dym on 13.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#define VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#include "src/ConfigLoader/ConfigCache.hpp"

class ConfigCache;

class ConfigLoader {
  static QString configFileName;

public:
  static ConfigCache load(QString const &filePath);
  static ConfigCache load();
};

#endif // VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
