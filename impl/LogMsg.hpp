//
// Created by dym on 12.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_LOGMSG_HPP
#define VEDISOFTINTERNSHIP_LOGMSG_HPP
#include "Deffwd.hpp"
#include "LogMsgState.hpp"
#include <optional>
#include <vector>

#if defined(LOG_Debug)
  #Error "^^ redefinition"
#endif

class LogMsg {
public:
  static void initFromConfigLoader();

private:
  inline static std::optional<LogMsgState> config{};

  static log4cpp::Category &libRoot();

  struct LogLvlImplicit
  {
    LogMsgState::LogLvl lvl;
    constexpr operator std::string_view() const;
  } const _lvl;
  std::string_view const _file, _func;
  size_t _line;
  std::vector<std::string> messages;

public:
  ~LogMsg();
  LogMsg()= delete;
  LogMsg(
      std::string_view file,
      std::string_view func,
      size_t line,
      LogMsgState::LogLvl lvl);

  template<typename T>
  LogMsg &operator<<(T &&arg)
  {
    if (config->isEnabled(_lvl.lvl)) {
      messages.emplace_back(std::forward<T>(arg));
    }
    return *this;
  }
};

#define LOG_Debug                                                              \
  LogMsg                                                                       \
  {                                                                            \
    __FILE__, __FUNCTION__, __LINE__, LogMsgState::Debug                       \
  }
#define LOG_Info                                                               \
  LogMsg                                                                       \
  {                                                                            \
    __FILE__, __FUNCTION__, __LINE__, LogMsgState::Info                         \
  }
#define LOG_Warning                                                            \
  LogMsg                                                                       \
  {                                                                            \
    __FILE__, __FUNCTION__, __LINE__, LogMsgState::Warning                      \
  }
#define LOG_Error                                                              \
  LogMsg                                                                       \
  {                                                                            \
    __FILE__, __FUNCTION__, __LINE__, LogMsgState::Error                        \
  }

#endif // VEDISOFTINTERNSHIP_LOGMSG_HPP
