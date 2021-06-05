//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_LOGGERCONFIG_HPP
#define VEDISOFTINTERNSHIP_LOGGERCONFIG_HPP
#include "src/Logger/Logger.hpp"

class LoggerConfig {
  Q_GADGET
  Q_PROPERTY(Logger::Level levelFile MEMBER levelFile)
  Q_PROPERTY(Logger::Level levelConsole MEMBER levelConsole)
  Q_PROPERTY(QString logFileName MEMBER logFileName)
  Q_PROPERTY(QChar separatorMessages MEMBER separatorMessages)

public:
  Logger::Level levelFile;
  Logger::Level levelConsole;
  QChar separatorMessages;
  QString logFileName;
};

#ifdef LOGGER_LEVEL_INIT
  #error "^^ redefinition"
#endif
#ifndef NDEBUG
  #define LOGGER_LEVEL_INIT(lvl) Logger::Level::Debug
#else
  #define LOGGER_LEVEL_INIT(lvl) lvl
#endif

namespace configDefault
{
inline const LoggerConfig logger{ LOGGER_LEVEL_INIT(Logger::Level::Warninig),
                                  LOGGER_LEVEL_INIT(Logger::Level::Error),
                                  ' ',
                                  QStringLiteral("logApp_defaultName.txt") };
}
#endif // VEDISOFTINTERNSHIP_LOGGERCONFIG_HPP
