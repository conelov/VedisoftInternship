//
// Created by dym on 13.05.2021.
//

#include "ConfigLoader.hpp"
#include "LogMsgState.hpp"
#include <QFileInfo>
#include <QSettings>

class ConfigLoaderBase {
  inline static bool _firstCall             = true;
  static constexpr std::string_view filePath= "./config.ini";

public:
  QSettings setting;

  ConfigLoaderBase()= delete;
  ConfigLoaderBase(QString const &group)
      : setting(filePath.data(), QSettings::Format::IniFormat)
  {
    /// Init default config file
    if (std::exchange(_firstCall, false) &&
        !QFileInfo::exists(filePath.data())) {
      setting.setValue(TO_LITERAL(LogMsg) "/state/0", true);
      setting.setValue(TO_LITERAL(LogMsg) "/state/1", true);
      setting.setValue(TO_LITERAL(LogMsg) "/state/2", true);
      setting.setValue(TO_LITERAL(LogMsg) "/state/3", true);
      setting.setValue(TO_LITERAL(LogMsg) "/fileName", "log.ini");
    }

    setting.beginGroup(group);
  }
};

ConfigLoader<LogMsg>::~ConfigLoader()= default;
ConfigLoader<LogMsg>::ConfigLoader()
    : base(new ConfigLoaderBase(TO_LITERAL(LogMsg)))
{}
LogMsgState ConfigLoader<LogMsg>::state() const
{
  base->setting.beginGroup("state");
  LogMsgState stateRet;

  for (LogMsgState::UnderType i{}; i < LogMsgState::LogLvl::count; ++i) {
    if (base->setting.value(QString::number(i)).value<bool>()) {
      stateRet.lvl.set(i);
    }
  }

  base->setting.endGroup();
  return stateRet;
}
std::string ConfigLoader<LogMsg>::fileName() const
{
#ifndef NDEBUG
  auto const name=
      base->setting.value("fileName", "ERRINIT").toString().toStdString();
  assert(name != "ERRINIT" && "dont init default config file");
  return name;
#else
  return base->setting.value("fileName", "config.ini").toString().toStdString();
#endif
}