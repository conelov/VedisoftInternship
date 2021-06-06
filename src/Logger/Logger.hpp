//
// Created by dym on 12.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_LOGGER_HPP
#define VEDISOFTINTERNSHIP_LOGGER_HPP
#include <QLatin1String>
#include <QStringList>
#include <qobjectdefs.h>

class LoggerConfig;

class Logger {
  Q_GADGET

public:
  enum Level : quint8
  {
    Debug,
    Info,
    Warninig,
    Error,
    Off,
    count
  };
  Q_ENUM(Level)

  static void loadState(LoggerConfig const &state);

private:
  bool const _logAny;
  Level const _lvl;
  uint const _line;
  char const *const _file, *const _func; /// Because Latin1String allocates
  QStringList _messages;

public:
  ~Logger();
  Logger()= delete;
  Logger(decltype(_func) file, decltype(_func) func, uint line, Level lvl);

  template<typename T>
  Logger &operator<<(T &&arg)
  {
    if (_logAny) {
      _messages.push_back(std::forward<T>(arg));
    }
    return *this;
  }
};

#if defined(LOG_Debug) || defined(LOG_Info) || defined(LOG_Warning) ||         \
    defined(LOG_Error) || defined(LOG_MESSAGE_MANUALLVL)
  #error "^^ redefinition"
#endif

#define LOG_MESSAGE_MANUALLVL(lvl) __FILE__, __FUNCTION__, __LINE__, lvl

#define LOG_Debug Logger(LOG_MESSAGE_MANUALLVL(Logger::Debug))

#define LOG_Info Logger(LOG_MESSAGE_MANUALLVL(Logger::Info))

#define LOG_Warning Logger(LOG_MESSAGE_MANUALLVL(Logger::Warninig))

#define LOG_Error Logger(LOG_MESSAGE_MANUALLVL(Logger::Error))

#endif // VEDISOFTINTERNSHIP_LOGGER_HPP
