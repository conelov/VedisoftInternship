//
// Created by dym on 13.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#define VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#include <QScopedPointer>

class ConfigCache;

class ConfigLoader {
  static QString configFileName;

public:
  static QScopedPointer<ConfigCache> load(QString const &filePath);
  static QScopedPointer<ConfigCache> load();
};

#endif // VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
