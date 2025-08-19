cmake_minimum_required(VERSION 3.10)

project(Application VERSION 1.0.0 LANGUAGES CXX)

# Qt 必备三件套
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

# 查找 Qt5 模块
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# 公共头文件目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/pluginframework
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends
)

# 生成可执行文件
add_executable(Application
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDAMainWindow.h
)

# 链接 Qt 库
target_link_libraries(Application
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
	$<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKCore.lib>
    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKPluginFramework.lib>
)

# Windows 专用：Debug 带控制台，Release 不带
if(WIN32)
    set_target_properties(Application PROPERTIES
        WIN32_EXECUTABLE $<$<CONFIG:Debug>:FALSE>$<$<CONFIG:Release>:TRUE>
    )
endif()

# macOS 专用：不生成 .app 目录
if(APPLE)
    set_target_properties(Application PROPERTIES
        MACOSX_BUNDLE FALSE
    )
endif()