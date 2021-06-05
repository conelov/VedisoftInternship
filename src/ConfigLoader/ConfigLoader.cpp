//
// Created by dym on 13.05.2021.
//

#include "ConfigLoader.hpp"
#include "src/Logger/LoggerConfig.hpp"
#include "src/PropertyGenerator.hpp"
#include "src/deffwd.hpp"
#include <QCoreApplication>
#include <QSettings>

namespace
{
auto constexpr appBuildType=
#ifndef NDEBUG
    1
#else
    2
#endif
    ;
} // namespace

ConfigCache ConfigLoader::load()
{
  ConfigCache confArg;
  QSettings setting(
      QCoreApplication::applicationDirPath() + QChar('/') + configFileName,
      QSettings::Format::IniFormat);

  setting.beginGroup("appConfig");

  /// Init settings file
  if (setting.value(QStringLiteral(TO_LITERAL(appBuildType)), 0).toUInt() !=
      appBuildType) {
    setting.clear();
    setting.setValue(QStringLiteral(TO_LITERAL(appBuildType)), appBuildType);

    setting.beginGroup(QStringLiteral(TO_LITERAL(Logger)));
    for (PropertyGenerator pg{ configDefault::logger }; pg; ++pg) {
      setting.setValue(pg.property().name(), pg.read());
    }
    setting.endGroup();

    setting.beginGroup(QStringLiteral(TO_LITERAL(NetManager)));
    for (PropertyGenerator pg(configDefault::netManager); pg; ++pg) {
      setting.setValue(pg.property().name(), pg.read());
    }
    setting.endGroup();
  }

  setting.beginGroup(QStringLiteral(TO_LITERAL(Logger)));
  for (PropertyGenerator pg{ confArg.logger }; pg; ++pg) {
    pg.write(setting.value(pg.property().name()));
  }
  setting.endGroup();

  setting.beginGroup(QStringLiteral(TO_LITERAL(NetManager)));
  for (PropertyGenerator pg(confArg.netManager); pg; ++pg) {
    pg.write(setting.value(pg.property().name()));
  }
  setting.endGroup();

  setting.endGroup();
  return confArg;
}
