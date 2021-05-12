cmake_minimum_required(VERSION 3.19)
project(VedisoftInternship)
set(CMAKE_CXX_STANDARD 20)
set(QT_VERSION 5)

#set(CMAKE_CXX_LINK_EXECUTABLE "-lpthread")
set(${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED Threads::Threads)
set(${PROJECT_NAME}_INCLUDE_DIR impl)
set(${PROJECT_NAME}_files
        qml.qrc
        impl/LogMsg.cpp impl/LogMsg.hpp
        impl/Deffwd.hpp)

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Core Quick REQUIRED)
find_package(Threads REQUIRED)
list(APPEND ${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED
        Qt${QT_VERSION}::Core Qt${QT_VERSION}::Quick
        )
find_package(log4cpp REQUIRED)
list(APPEND ${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED
        ${QCustomPlot_LIBRARIES}
        )
list(APPEND ${PROJECT_NAME}_INCLUDE_DIR
        ${QCustomPlot_INCLUDE_DIRS}
        )
add_subdirectory("$ENV{CLP_DIR}/googletest" gtestBuild)

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
        RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin"
        )
target_compile_definitions(${PROJECT_NAME}_main
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

add_executable(${PROJECT_NAME}_tests
        tests/loger.cpp
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
set_target_properties(${PROJECT_NAME}_main PROPERTIES
        AUTOMOC ON
#        AUTORCC ON
        INCLUDE_CURRENT_DIR ON
        RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin"
        )

add_executable(${PROJECT_NAME}_testLogerExec
        tests/loger_main.cpp
        ${${PROJECT_NAME}_files}
        )
target_link_libraries(${PROJECT_NAME}_testLogerExec
        PUBLIC
        ${${PROJECT_NAME}_REQUIRED_LIBS_QUALIFIED}
        )
target_include_directories(${PROJECT_NAME}_testLogerExec PUBLIC
        ${${PROJECT_NAME}_INCLUDE_DIR}
        )
