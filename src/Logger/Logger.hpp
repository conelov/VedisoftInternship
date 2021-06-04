//
// Created by dym on 12.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_LOGGER_HPP
#define VEDISOFTINTERNSHIP_LOGGER_HPP
#include "LoggerConfig.hpp"

namespace log4cpp
{
class Category;
}

class Logger {
  inline static LoggerConfig config= loggerConfigDefault;
  static void initLib();
  static log4cpp::Category &libRoot();

public:
  static void loadState(LoggerConfig const &state);

private:
  LoggerConfig::Level _lvl;
  qsizetype _line;
  QString _file, _func;
  QStringList messages;

public:
  ~Logger();
  Logger()= delete;
  Logger(
      QString const &file,
      QString const &func,
      qsizetype line,
      LoggerConfig::Level lvl);

  template<typename T>
  Logger &operator<<(T &&arg)
  {
    if (_lvl <= config.level) {
      messages.push_back(std::forward<T>(arg));
    }
    return *this;
  }
};

#if defined(LOG_Debug) || defined(LOG_Info) || defined(LOG_Warning) ||         \
    defined(LOG_Error)
  #Error "^^ redefinition"
#endif

#define LOG_Debug                                                              \
  Logger                                                                       \
  {                                                                            \
    QStringLiteral(__FILE__), __FUNCTION__, __LINE__, LoggerConfig::Debug      \
  }
#define LOG_Info                                                               \
  Logger                                                                       \
  {                                                                            \
    QStringLiteral(__FILE__), __FUNCTION__, __LINE__, LoggerConfig::Info       \
  }
#define LOG_Warning                                                            \
  Logger                                                                       \
  {                                                                            \
    QStringLiteral(__FILE__), __FUNCTION__, __LINE__, LoggerConfig::Warning    \
  }
#define LOG_Error                                                              \
  Logger                                                                       \
  {                                                                            \
    QStringLiteral(__FILE__), __FUNCTION__, __LINE__, LoggerConfig::Error      \
  }
#endif // VEDISOFTINTERNSHIP_LOGGER_HPP
