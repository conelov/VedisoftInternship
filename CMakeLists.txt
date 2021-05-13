cmake_minimum_required(VERSION 3.19)
project(VedisoftInternship)
set(CMAKE_CXX_STANDARD 20)
set(QT_VERSION 5)

set(${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED
        Threads::Threads
        "${PROJECT_SOURCE_DIR}/3rdparty/logger/lib/liblog4cpp.so"
        )
set(${PROJECT_NAME}_INCLUDE_DIR
        impl
        3rdparty/logger/include/
        )
set(${PROJECT_NAME}_files
        qml.qrc
        impl/LogMsg.cpp impl/LogMsg.hpp
        impl/Deffwd.hpp impl/ConfigLoader.cpp impl/ConfigLoader.hpp impl/LogMsgState.hpp)

find_package(Threads REQUIRED)

add_subdirectory("$ENV{CLP_DIR}/googletest" gtestBuild)

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Core Quick REQUIRED)
list(APPEND ${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED
        Qt${QT_VERSION}::Core Qt${QT_VERSION}::Quick
        )

add_executable(${PROJECT_NAME}_main
        main.cpp
        ${${PROJECT_NAME}_files}
        )
target_link_libraries(${PROJECT_NAME}_main
        PUBLIC
        ${${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED}
        )
target_include_directories(${PROJECT_NAME}_main PUBLIC
        ${${PROJECT_NAME}_INCLUDE_DIR}
        )
set_target_properties(${PROJECT_NAME}_main PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        INCLUDE_CURRENT_DIR ON
        )
target_compile_definitions(${PROJECT_NAME}_main
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

add_executable(${PROJECT_NAME}_touchTests
        touchTests/main.cpp
        ${${PROJECT_NAME}_files}
        )
target_link_libraries(${PROJECT_NAME}_touchTests
        PUBLIC
        ${${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED}
        )
target_include_directories(${PROJECT_NAME}_touchTests PUBLIC
        ${${PROJECT_NAME}_INCLUDE_DIR}
        )
set_target_properties(${PROJECT_NAME}_touchTests PROPERTIES
        AUTOMOC ON
#        AUTORCC ON
        INCLUDE_CURRENT_DIR ON
        )
