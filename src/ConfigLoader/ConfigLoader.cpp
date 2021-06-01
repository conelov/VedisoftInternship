//
// Created by dym on 13.05.2021.
//

#include "ConfigLoader.hpp"
#include "ConfigCache.hpp"
#include "src/Logger/LoggerConfig.hpp"
#include "src/NetManager/NetManagerConfig.hpp"
#include "src/deffwd.hpp"
#include <QSettings>

namespace
{
constexpr auto fileConfigNameDefault= "config.ini";
} // namespace

QString ConfigLoader::configFileName= fileConfigNameDefault;

ConfigCache ConfigLoader::load(const QString &filePath)
{
  configFileName= filePath;
  return load();
}
ConfigCache ConfigLoader::load()
{
  ConfigCache confArg;
  QSettings setting(
      QCoreApplication::applicationDirPath() + '/' + configFileName,
      QSettings::Format::IniFormat);

  setting.beginGroup("appConfig");

  if (!QFileInfo::exists(configFileName)) {
    setting.beginGroup(QStringLiteral(TO_LITERAL(Logger)));
    setting.setValue(QStringLiteral("level"), loggerConfigDefault.level);
    setting.setValue(
        QStringLiteral("logFileName"), loggerConfigDefault.logFileName);
    setting.endGroup();

    setting.beginGroup(QStringLiteral(TO_LITERAL(NetManager)));
    setting.setValue(QStringLiteral("url"), netManagerDefault.url);
    setting.endGroup();
  }

  setting.beginGroup(QStringLiteral(TO_LITERAL(Logger)));
  confArg.logger.level=
      setting.value(QStringLiteral("level")).value<LoggerConfig::Level>();
  confArg.logger.logFileName=
      setting.value(QStringLiteral("logFileName")).toString();
  setting.endGroup();

  setting.beginGroup(QStringLiteral(TO_LITERAL(NetManager)));
  confArg.netManager.url= setting.value(QStringLiteral("url")).toUrl();
  setting.endGroup();

  setting.endGroup();
  return confArg;
}
