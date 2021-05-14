//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CONFIGCACHE_HPP
#define VEDISOFTINTERNSHIP_CONFIGCACHE_HPP
#include <QScopedPointer>

class LoggerConfig;

class ConfigCache {
public:
  QScopedPointer<LoggerConfig> logger;

  ~ConfigCache();
  ConfigCache();
};

#endif // VEDISOFTINTERNSHIP_CONFIGCACHE_HPP
