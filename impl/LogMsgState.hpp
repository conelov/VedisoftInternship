//
// Created by dym on 13.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_LOGMSGSTATE_HPP
#define VEDISOFTINTERNSHIP_LOGMSGSTATE_HPP
#include <bitset>

struct LogMsgState
{
  using UnderType= uint8_t;
  ///  Debug, Info, Warning, Error
  enum LogLvl : UnderType
  {
    Error= 0,
    Warning,
    Info,
    Debug,
    max  = Debug,
    count= max + 1
  };
  std::bitset<4> lvl{};

  [[nodiscard]] bool isEnabled(LogLvl mode) const
  {
    return lvl.test(mode);
  }
};

#endif // VEDISOFTINTERNSHIP_LOGMSGSTATE_HPP
