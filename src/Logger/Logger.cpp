//
// Created by dym on 12.05.2021.
//

#include "Logger.hpp"
#include "src/ConfigLoader/ConfigLoader.hpp"
#include "src/utils.hpp"
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

#ifndef NDEBUG
  #include "log4cpp/OstreamAppender.hh"
  #include <QDebug>
#endif

namespace
{
static bool _initOnce= true;
}

void Logger::loadState(const LoggerConfig &state)
{
  config= state;
  initLib();
}
log4cpp::Category &Logger::libRoot()
{
  if (exchange(_initOnce, false)) {
    initLib();
  }
  return log4cpp::Category::getRoot();
}
void Logger::initLib()
{
  using namespace log4cpp;
  auto const apd= new FileAppender(
      "default",
      (QCoreApplication::applicationDirPath() + '/' + config.logFileName)
          .toStdString())
      //  new log4cpp::OstreamAppender("console", &std::cout)
      ;
  auto const layout= new PatternLayout;
  layout->setConversionPattern("%d{%H:%M} %m%n");
  apd->setLayout(layout);
  if (!_initOnce) {
    libRoot().removeAllAppenders();
  }
  libRoot().addAppender(apd);
}
Logger::~Logger()
{
  if (messages.isEmpty())
    return;

  /// Collapsed in one string
  for (auto it= std::next(messages.begin()); it < messages.end(); ++it) {
    messages.front()+= ';' + *it;
  }

  libRoot().info(
      "%s {%s: %u} [%s]: %s",
      _file.toStdString().c_str(),
      _func.toStdString().c_str(),
      _line,
      QMetaEnum::fromType<LoggerConfig::Level>().valueToKey(_lvl),
      messages.front().toStdString().c_str());
}
Logger::Logger(
    const QString &file,
    const QString &func,
    qsizetype line,
    LoggerConfig::Level lvl)
    : _lvl{ lvl }
    , _line{ line }
    , _file{ file }
    , _func{ func }
{}
