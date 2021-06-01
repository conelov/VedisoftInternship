//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_LOGGERCONFIG_HPP
#define VEDISOFTINTERNSHIP_LOGGERCONFIG_HPP
#include <QtCore>

class LoggerConfig {
  Q_GADGET

public:
  using LevelUndertype= quint8;
  enum Level : LevelUndertype
  {
    Error,
    Debug,
    Info,
    Warning
  } level;
  Q_ENUM(Level)
  QString logFileName;
};

inline const LoggerConfig loggerConfigDefault{
  LoggerConfig::Level::Info, QStringLiteral("logApp_defaultName.txt")
};
#endif // VEDISOFTINTERNSHIP_LOGGERCONFIG_HPP
