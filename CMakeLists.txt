cmake_minimum_required(VERSION 3.16)
project(VedisoftInternship)
set(CMAKE_CXX_STANDARD 17)
set(QT_VERSION 5)

find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Core Quick Sql REQUIRED)
#find_package(Threads REQUIRED)
add_subdirectory("$ENV{CLP_DIR}/googletest" gtestBuild)
add_subdirectory("${PROJECT_SOURCE_DIR}/3rdparty/spdlog" spdlogBuild)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(${PROJECT_NAME}_RESOURCES
        qml.qrc
        )

add_library(${PROJECT_NAME}_impl STATIC
        ${${PROJECT_NAME}_RESOURCES}
        src/Logger/Logger.cpp src/Logger/Logger.hpp
        src/Logger/LoggerConfig.hpp
        src/deffwd.hpp
        src/ConfigLoader/ConfigLoader.cpp src/ConfigLoader/ConfigLoader.hpp
        src/ConfigLoader/ConfigCache.hpp
        src/entities/Card.hpp
        src/entities/Provider.hpp
        src/MarshalJson/MarshalJson.cpp src/MarshalJson/MarshalJson.hpp
        src/utils.hpp
        src/AppEngine.hpp src/AppEngine.cpp
        src/models/ModelProviderCard.hpp src/models/ModelProviderCard.cpp
        src/DBLink/DBLink.cpp src/DBLink/DBLink.hpp
        src/entities/Provider.hpp
        src/PropertyGenerator.hpp
        src/entities/entitiesSupport.cpp
        src/DBLink/DBLinkExecutor.hpp
        src/NetManager/NetManager.cpp src/NetManager/NetManager.hpp src/NetManager/NetManagerConfig.hpp
        src/MarshalJson/MarshalJsonUtils.hpp
        $<$<CONFIG:Debug>:testValues/values.hpp>
        $<$<CONFIG:Debug>:testValues/json.hpp>
        )
target_link_libraries(${PROJECT_NAME}_impl PUBLIC
#        Threads::Threads
#        "${PROJECT_SOURCE_DIR}/3rdparty/log4cpp/lib_nix/liblog4cpp.so"
        Qt${QT_VERSION}::Core Qt${QT_VERSION}::Quick Qt${QT_VERSION}::Sql
        spdlog
        )
target_include_directories(${PROJECT_NAME}_impl PUBLIC
        "${PROJECT_SOURCE_DIR}"
#        "${PROJECT_SOURCE_DIR}/3rdparty/log4cpp/include/"
        "${PROJECT_SOURCE_DIR}/3rdparty/spdlog/include"
        )
target_compile_definitions(${PROJECT_NAME}_impl
        PUBLIC $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
        )

add_executable(${PROJECT_NAME}_main
        main.cpp
        ${${PROJECT_NAME}_RESOURCES}
        )
target_link_libraries(${PROJECT_NAME}_main PUBLIC
        ${PROJECT_NAME}_impl
        )


function(addTestSubproj NAME)
    set(SubprojDir "${PROJECT_SOURCE_DIR}/tests/${NAME}")
    set(testFile ${SubprojDir}/${NAME}_test.cpp)
    set(mainFile ${SubprojDir}/${NAME}_main.cpp)
    file(MAKE_DIRECTORY ${SubprojDir})
    if (NOT EXISTS ${testFile})
        configure_file(cmakeTemplates/testTemplate.cpp.in ${testFile})
    endif ()
    if (NOT EXISTS ${mainFile})
        configure_file(cmakeTemplates/testMainFileTemplate.cpp.in ${mainFile})
    endif ()
    add_executable(${NAME}_test
            ${testFile}
            ${mainFile}
            ${${PROJECT_NAME}_RESOURCES}
            )
    target_link_libraries(${NAME}_test PUBLIC
            ${PROJECT_NAME}_impl
            gtest
            )
    set_target_properties(${NAME}_test PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${SubprojDir}/bin"
            )
endfunction()

addTestSubproj(DB)
addTestSubproj(Json)

function(addTouchSubproj NAME)
    set(SubprojDir "${PROJECT_SOURCE_DIR}/touchSubproj/${NAME}")
    set(touchMainFile ${SubprojDir}/${NAME}_touch.cpp)
    file(MAKE_DIRECTORY ${SubprojDir})
    if (NOT EXISTS ${touchMainFile})
        configure_file(cmakeTemplates/touchTemplate.cpp.in ${touchMainFile})
    endif ()
    add_executable(${NAME}_touch
            ${touchMainFile}
            ${${PROJECT_NAME}_RESOURCES}
            )
    target_link_libraries(${NAME}_touch PUBLIC
            ${PROJECT_NAME}_impl
            )
    set_target_properties(${NAME}_touch PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${SubprojDir}/bin"
            )
endfunction()

addTouchSubproj(DB)
addTouchSubproj(Logger)
addTouchSubproj(Json)