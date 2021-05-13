//
// Created by dym on 12.05.2021.
//

#include "LogMsg.hpp"
#include "ConfigLoader.hpp"
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

#ifndef NDEBUG
  #include "log4cpp/OstreamAppender.hh"
  #include <QDebug>
#endif

constexpr LogMsg::LogLvlImplicit::operator std::string_view() const
{
  switch (lvl) {
  case LogMsgState::Debug: return TO_LITERAL(Debug);
  case LogMsgState::Info: return TO_LITERAL(Info);
  case LogMsgState::Warning: return TO_LITERAL(Warning);
  case LogMsgState::Error: return TO_LITERAL(Error);
  default: assert(false);
  }
}

LogMsg::~LogMsg()
{
  assert(config);
  if (messages.empty())
    return;

  /// Collapsed in one string
  for (auto it= std::next(messages.begin()); it < messages.end(); ++it) {
    messages.front()+= ';' + std::move(*it);
  }

  libRoot().info(
      "%s {%s: %u} [%s]: %s",
      _file.data(),
      _func.data(),
      _line,
      _lvl.operator std::string_view().data(),
      messages.front().c_str());
}
LogMsg::LogMsg(
    std::string_view file,
    std::string_view func,
    size_t line,
    LogMsgState::LogLvl lvl)
    : _lvl{ lvl }
    , _file{ file }
    , _func{ func }
    , _line{ line }
{
  if (!config) {
    initFromConfigLoader();
  }
}
void LogMsg::initFromConfigLoader()
{
  assert(!config && "reinitialization");

  ConfigLoader<LogMsg> const confLoad{};
  config.emplace(confLoad.state());

  using namespace log4cpp;
  auto const apd=
            new log4cpp::FileAppender("default",
            confLoad.fileName())
//      new log4cpp::OstreamAppender("console", &std::cout)
            ;
  auto const layout= new PatternLayout;
  layout->setConversionPattern("%d{%H:%M} %m%n");
  apd->setLayout(layout);
  libRoot().addAppender(apd);
}
log4cpp::Category &LogMsg::libRoot()
{
  return log4cpp::Category::getRoot();
}
