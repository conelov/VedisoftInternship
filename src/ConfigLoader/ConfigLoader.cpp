//
// Created by dym on 13.05.2021.
//

#include "ConfigLoader.hpp"
#include "src/Logger/LoggerConfig.hpp"
#include "src/PropertyGenerator.hpp"
#include "src/deffwd.hpp"
#include <QCoreApplication>
#include <QSettings>

namespace {
auto constexpr appBuildType =
#ifndef NDEBUG
        2
#else
        1
#endif
        ;
} // namespace

ConfigCache ConfigLoader::load()
{
    QSettings setting(QCoreApplication::applicationDirPath() + QChar('/') + configFileName,
                      QSettings::Format::IniFormat);

    setting.beginGroup("appConfig");

    /// Init settings file
    if (setting.value(QStringLiteral(TO_LITERAL(appBuildType)), 0).toUInt() != appBuildType) {
        setting.clear();
        setting.setValue(QStringLiteral(TO_LITERAL(appBuildType)), appBuildType);

        for (PropertyGenerator pg { configDefault::logger }; pg; ++pg) {
            setting.setValue(pg.property().name(), pg.read());
        }
        for (PropertyGenerator pg(configDefault::netManager); pg; ++pg) {
            setting.setValue(pg.property().name(), pg.read());
        }
    }

    ConfigCache confArg;
    for (PropertyGenerator pg { confArg.logger }; pg; ++pg) {
        QLatin1String const propName { pg.property().name() };
        if (propName == "levelFile" || propName == "levelConsole") {
            pg.write(setting.value(pg.property().name())
                             .value<std::underlying_type_t<Logger::Level>>());
            continue;
        }
        pg.write(setting.value(pg.property().name()));
    }
    for (PropertyGenerator pg(confArg.netManager); pg; ++pg) {
        pg.write(setting.value(pg.property().name()));
    }

    setting.endGroup();
    return confArg;
}
