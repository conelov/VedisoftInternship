//
// Created by dym on 12.05.2021.
//

#include "LogMsg.hpp"
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>

#include <QDebug>

constexpr LogMsg::LogLvlImplicit::operator std::string_view() const
{
  switch (lvl) {
  case debug: return TO_LITERAL(debug);
  case info: return TO_LITERAL(info);
  case warning: return TO_LITERAL(warning);
  case error: return TO_LITERAL(error);
  default: assert(false);
  }
}

LogMsg::~LogMsg()
{
  qDebug() << "test: " << _file.data() << _func.data()
           << _lvl.operator std::string_view().data() << messages;
}
LogMsg::LogMsg(std::string_view file, std::string_view func, LogLvl lvl)
    : _lvl{ lvl }
    , _file{ file }
    , _func{ func }
{}
void LogMsg::initFromConfigLoader(const ConfigLoader &cfg)
{
#ifndef NDEBUG
  if (std::exchange(_isInitConfig, true))
    assert(false && "reinitialization");
#endif

  libRoot().addAppender(new log4cpp::FileAppender("default", "logs.ini"));
}
log4cpp::Category &LogMsg::libRoot()
{
#ifndef NDEBUG
  if (!_isInitConfig)
    assert(false && "libLogRoot entity not initialize");
#endif
  return log4cpp::Category::getRoot();
}
