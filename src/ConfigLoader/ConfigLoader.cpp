//
// Created by dym on 13.05.2021.
//

#include "ConfigLoader.hpp"
#include "src/Logger/LoggerConfig.hpp"
#include "src/PropertyGenerator.hpp"
#include "src/deffwd.hpp"
#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>

ConfigCache ConfigLoader::load()
{
    QString const fileFullPath = QCoreApplication::applicationDirPath() + '/' + configFileName;
    QSettings setting(fileFullPath, QSettings::Format::IniFormat);

    /// Init settings file
    if (!QFileInfo::exists(fileFullPath)) {
        setting.setValue(QStringLiteral(TO_LITERAL(Logger) "/level"),
                         QMetaEnum::fromType<Logger::Level>().valueToKey(
                                 configDefault::logger.levelConsole));
        setting.setValue(QStringLiteral(TO_LITERAL(Logger) "/logFileName"),
                         configDefault::logger.logFileName);

        setting.setValue(QStringLiteral(TO_LITERAL(NetManager) "/url"),
                         configDefault::netManager.url.toString());
    }

    ConfigCache confArg;

    confArg.logger.levelFile = confArg.logger.levelConsole =
            static_cast<Logger::Level>(QMetaEnum::fromType<Logger::Level>().keyToValue(
                    setting.value(QStringLiteral(TO_LITERAL(Logger) "/level"))
                            .toString()
                            .toStdString()
                            .c_str()));
    confArg.logger.logFileName =
            setting.value(QStringLiteral(TO_LITERAL(Logger) "/logFileName")).toString();

    confArg.netManager.url =
            setting.value(QStringLiteral(TO_LITERAL(NetManager) "/url")).toString();

    return confArg;
}
