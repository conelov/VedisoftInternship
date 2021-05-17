//
// Created by dym on 13.05.2021.
//

#include "ConfigLoader.hpp"
#include "src/logger/LoggerConfig.hpp"
#include "ConfigCache.hpp"
#include <QSettings>

namespace
{
constexpr auto fileConfigNameDefault= "config.ini";
} // namespace

QString ConfigLoader::configFileName= fileConfigNameDefault;

QScopedPointer<ConfigCache> ConfigLoader::load(const QString &filePath)
{
  configFileName= filePath;
  return load();
}
QScopedPointer<ConfigCache> ConfigLoader::load()
{
  QScopedPointer<ConfigCache> confArg(new ConfigCache);
  QSettings setting(
      QCoreApplication::applicationDirPath() + '/' + configFileName,
      QSettings::Format::IniFormat);

  setting.beginGroup("appConfig");

  if (!QFileInfo::exists(configFileName)) {
    setting.beginGroup(QStringLiteral("Logger"));
    setting.setValue(QStringLiteral("level"), loggerConfigDefault.level);
    setting.setValue(
        QStringLiteral("logFileName"), loggerConfigDefault.logFileName);
    setting.endGroup();
  }

  setting.beginGroup(QStringLiteral("Logger"));
  confArg->logger->level=
      setting.value(QStringLiteral("level")).value<LoggerConfig::Level>();
  confArg->logger->logFileName=
      setting.value(QStringLiteral("logFileName")).toString();
  setting.endGroup();

  setting.endGroup();
  return decltype(confArg)(confArg.take());
}
