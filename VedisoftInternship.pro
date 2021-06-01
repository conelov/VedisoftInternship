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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rdparty/logger/lib/release/ -llog4cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rdparty/logger/lib/debug/ -llog4cpp
else:unix: LIBS += -L$$PWD/3rdparty/logger/lib/ -llog4cpp

INCLUDEPATH += $$PWD/3rdparty/logger/include
DEPENDPATH += $$PWD/3rdparty/logger/include

DESTDIR = $$PWD/bin

RESOURCES += \
    qml.qrc

HEADERS += \
    src/AppEngine.hpp \
    src/ConfigLoader/ConfigCache.hpp \
    src/ConfigLoader/ConfigLoader.hpp \
    src/DBLink/DBLink.hpp \
    src/DBLink/DBLinkExecutor.hpp \
    src/Logger/Logger.hpp \
    src/Logger/LoggerConfig.hpp \
    src/MarshalJson.hpp \
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
    src/MarshalJson.cpp \
    src/NetManager/NetManager.cpp \
    src/entities/qHashSupport.cpp \
    src/models/ModelProviderCard.cpp

DISTFILES += \
    qml/entities/Card.qml \
    qml/main.qml
