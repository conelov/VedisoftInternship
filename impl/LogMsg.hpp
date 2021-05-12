//
// Created by dym on 12.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_LOGMSG_HPP
#define VEDISOFTINTERNSHIP_LOGMSG_HPP

#include "Deffwd.hpp"
#include <QScopedPointer>
#include <QStringList>

#if defined(LOG_DEBUG)
  #error "^^ redefinition"
#endif

class LogMsg {
public:
  ///  Debug, Info, Warning, Error
  enum LogLvl : uint8_t
  {
    debug,
    info,
    warning,
    error
  };

private:
#ifndef NDEBUG
  inline static bool _isInitConfig= false;
#endif
  // Pimpl pattern
  struct Config;
  static QScopedPointer<Config> _config;

public:
  static void initFromConfigLoader(ConfigLoader const &cfg);

private:
  static log4cpp::Category &libRoot();

  struct LogLvlImplicit
  {
    LogLvl lvl;
    constexpr operator std::string_view() const;
  } _lvl;
  std::string_view _file, _func;
  QStringList messages;

public:
  ~LogMsg();
  LogMsg()= delete;
  LogMsg(std::string_view file, std::string_view func, LogLvl lvl);

  template<typename T>
  LogMsg &operator<<(T &&arg)
  {
    messages << std::forward<T>(arg);
    return *this;
  }
};

#define LOG_DEBUG LogMsg(__FILE__, Q_FUNC_INFO, LogMsg::debug)

#endif // VEDISOFTINTERNSHIP_LOGMSG_HPP
