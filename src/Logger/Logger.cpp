//
// Created by dym on 12.05.2021.
//
#include "Logger.hpp"
#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "src/Logger/LoggerConfig.hpp"
#include <QCoreApplication>
#include <QStringBuilder>

namespace {
LoggerConfig _config = configDefault::logger;
QScopedPointer<spdlog::logger> _log;

spdlog::level::level_enum lvlToSpdlogLvl(Logger::Level const lvl)
{
    using spdLvl = spdlog::level::level_enum;
    switch (lvl) {
    case Logger::Debug:
        return spdLvl ::debug;
    case Logger::Info:
        return spdLvl ::info;
    case Logger::Warninig:
        return spdLvl::warn;
    case Logger::Error:
        return spdLvl ::err;
    default:
        LOG_Error << "unknown log level when converting";
        return {};
    }
}
} // namespace

void Logger::loadState(const LoggerConfig &state)
{
    _config = state;
    _log.reset();
}

Logger::Logger(decltype(_func) file, decltype(_func) func, uint line, Logger::Level lvl)
    : _logAny { lvl >= _config.levelFile || lvl >= _config.levelConsole }
    , _lvl { lvl }
    , _line { line }
    , _file { file }
    , _func { func }
{
    if (!(_logAny && !_log))
        return;

    /// Init lib-logger
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    console_sink->set_level(lvlToSpdlogLvl(_config.levelConsole));

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_st>(
            (QCoreApplication::applicationDirPath() % '/' % _config.logFileName)
                    .toLocal8Bit().toStdString(),
            false);
    file_sink->set_level(lvlToSpdlogLvl(_config.levelFile));

    _log.reset(new spdlog::logger("generalLog", { std::move(console_sink), std::move(file_sink) }));
    _log->set_level(spdlog::level::trace); /// Because trace is minimal level
    _log->set_pattern("[%R][%l]: %v");
}

Logger::~Logger()
{
    if (!_logAny)
        return;

    _log->log(lvlToSpdlogLvl(_lvl),
              (QString(_file) % ' ' % QString(_func) % ' ' % QString::number(_line) % ": "
               % _messages.join(_config.separatorMessages))
                      .toLocal8Bit()
                      .toStdString());
}
