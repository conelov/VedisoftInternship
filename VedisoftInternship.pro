QT += quick sql network

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DESTDIR = $$PWD/bin

RESOURCES += \
    qml.qrc

INCLUDEPATH += $$PWD/3rdparty/spdlog/include

HEADERS += \
    3rdparty/spdlog/include/spdlog/async.h \
    3rdparty/spdlog/include/spdlog/async_logger-inl.h \
    3rdparty/spdlog/include/spdlog/async_logger.h \
    3rdparty/spdlog/include/spdlog/cfg/argv.h \
    3rdparty/spdlog/include/spdlog/cfg/env.h \
    3rdparty/spdlog/include/spdlog/cfg/helpers-inl.h \
    3rdparty/spdlog/include/spdlog/cfg/helpers.h \
    3rdparty/spdlog/include/spdlog/common-inl.h \
    3rdparty/spdlog/include/spdlog/common.h \
    3rdparty/spdlog/include/spdlog/details/backtracer-inl.h \
    3rdparty/spdlog/include/spdlog/details/backtracer.h \
    3rdparty/spdlog/include/spdlog/details/circular_q.h \
    3rdparty/spdlog/include/spdlog/details/console_globals.h \
    3rdparty/spdlog/include/spdlog/details/file_helper-inl.h \
    3rdparty/spdlog/include/spdlog/details/file_helper.h \
    3rdparty/spdlog/include/spdlog/details/fmt_helper.h \
    3rdparty/spdlog/include/spdlog/details/log_msg-inl.h \
    3rdparty/spdlog/include/spdlog/details/log_msg.h \
    3rdparty/spdlog/include/spdlog/details/log_msg_buffer-inl.h \
    3rdparty/spdlog/include/spdlog/details/log_msg_buffer.h \
    3rdparty/spdlog/include/spdlog/details/mpmc_blocking_q.h \
    3rdparty/spdlog/include/spdlog/details/null_mutex.h \
    3rdparty/spdlog/include/spdlog/details/os-inl.h \
    3rdparty/spdlog/include/spdlog/details/os.h \
    3rdparty/spdlog/include/spdlog/details/periodic_worker-inl.h \
    3rdparty/spdlog/include/spdlog/details/periodic_worker.h \
    3rdparty/spdlog/include/spdlog/details/registry-inl.h \
    3rdparty/spdlog/include/spdlog/details/registry.h \
    3rdparty/spdlog/include/spdlog/details/synchronous_factory.h \
    3rdparty/spdlog/include/spdlog/details/tcp_client-windows.h \
    3rdparty/spdlog/include/spdlog/details/tcp_client.h \
    3rdparty/spdlog/include/spdlog/details/thread_pool-inl.h \
    3rdparty/spdlog/include/spdlog/details/thread_pool.h \
    3rdparty/spdlog/include/spdlog/details/windows_include.h \
    3rdparty/spdlog/include/spdlog/fmt/bin_to_hex.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/chrono.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/color.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/compile.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/core.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/format-inl.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/format.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/locale.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/os.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/ostream.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/posix.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/printf.h \
    3rdparty/spdlog/include/spdlog/fmt/bundled/ranges.h \
    3rdparty/spdlog/include/spdlog/fmt/chrono.h \
    3rdparty/spdlog/include/spdlog/fmt/fmt.h \
    3rdparty/spdlog/include/spdlog/fmt/ostr.h \
    3rdparty/spdlog/include/spdlog/formatter.h \
    3rdparty/spdlog/include/spdlog/fwd.h \
    3rdparty/spdlog/include/spdlog/logger-inl.h \
    3rdparty/spdlog/include/spdlog/logger.h \
    3rdparty/spdlog/include/spdlog/pattern_formatter-inl.h \
    3rdparty/spdlog/include/spdlog/pattern_formatter.h \
    3rdparty/spdlog/include/spdlog/sinks/android_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/ansicolor_sink-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/ansicolor_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/base_sink-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/base_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/basic_file_sink-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/basic_file_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/daily_file_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/dist_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/dup_filter_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/hourly_file_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/msvc_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/null_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/ostream_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/ringbuffer_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/rotating_file_sink-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/rotating_file_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/sink-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/sink.h \
    3rdparty/spdlog/include/spdlog/sinks/stdout_color_sinks-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/stdout_color_sinks.h \
    3rdparty/spdlog/include/spdlog/sinks/stdout_sinks-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/stdout_sinks.h \
    3rdparty/spdlog/include/spdlog/sinks/syslog_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/systemd_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/tcp_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/win_eventlog_sink.h \
    3rdparty/spdlog/include/spdlog/sinks/wincolor_sink-inl.h \
    3rdparty/spdlog/include/spdlog/sinks/wincolor_sink.h \
    3rdparty/spdlog/include/spdlog/spdlog-inl.h \
    3rdparty/spdlog/include/spdlog/spdlog.h \
    3rdparty/spdlog/include/spdlog/stopwatch.h \
    3rdparty/spdlog/include/spdlog/tweakme.h \
    3rdparty/spdlog/include/spdlog/version.h \
    src/AppEngine.hpp \
    src/ConfigLoader/ConfigCache.hpp \
    src/ConfigLoader/ConfigLoader.hpp \
    src/DBLink/DBLink.hpp \
    src/DBLink/DBLinkExecutor.hpp \
    src/Logger/Logger.hpp \
    src/Logger/LoggerConfig.hpp \
    src/MarshalJson/MarshalJson.hpp \
    src/MarshalJson/MarshalJsonUtils.hpp \
    src/NetManager/NetManager.hpp \
    src/NetManager/NetManagerConfig.hpp \
    src/PropertyGenerator.hpp \
    src/deffwd.hpp \
    src/entities/Card.hpp \
    src/entities/Provider.hpp \
    src/models/ModelProviderCard.hpp \
    src/utils.hpp

SOURCES += \
    main.cpp \
    src/AppEngine.cpp \
    src/ConfigLoader/ConfigLoader.cpp \
    src/DBLink/DBLink.cpp \
    src/Logger/Logger.cpp \
    src/MarshalJson/MarshalJson.cpp \
    src/NetManager/NetManager.cpp \
    src/entities/entitiesSupport.cpp \
    src/models/ModelProviderCard.cpp
