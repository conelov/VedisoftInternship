cmake_minimum_required(VERSION 3.16)
project(VedisoftInternship)
set(CMAKE_CXX_STANDARD 17)
set(QT_VERSION 5)

set(${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED
        Threads::Threads
        "${PROJECT_SOURCE_DIR}/3rdparty/logger/lib/liblog4cpp.so"
        )
set(${PROJECT_NAME}_INCLUDE_DIR
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/3rdparty/logger/include/"
        )
set(${PROJECT_NAME}_files
        qml.qrc
        src/logger/Logger.cpp src/logger/Logger.hpp
        src/logger/LoggerConfig.hpp
        src/deffwd.hpp
        src/configLoader/ConfigLoader.cpp src/configLoader/ConfigLoader.hpp
        src/configLoader/ConfigCache.hpp src/configLoader/ConfigCache.cpp
        src/entities/aggregates.hpp
        src/MarshalJson.cpp src/MarshalJson.hpp
        src/utils.hpp
        src/AppEngine.hpp
        src/models/ModelProviderCard.hpp)

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
        testsTouch/MarshalJson.cpp
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

add_executable(${PROJECT_NAME}_tests
        testingProj/test.cpp
        ${${PROJECT_NAME}_files}
        )
target_link_libraries(${PROJECT_NAME}_tests
        PUBLIC
        ${${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED}
        gtest_main
        )
target_include_directories(${PROJECT_NAME}_tests PUBLIC
        ${${PROJECT_NAME}_INCLUDE_DIR}
        )
set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        AUTOMOC ON
        #        AUTORCC ON
        INCLUDE_CURRENT_DIR ON
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/testingProj/bin
        )
