cmake_minimum_required(VERSION 3.10)

# 目录名保留带点，仅用于内部项目名
project(hierarch.da.com VERSION 1.0.0 LANGUAGES CXX)

# Qt 自动化
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

# 需要的 Qt5 模块
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets SerialPort)

# 公共头文件路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/pluginframework
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends
)

# 源文件
set(SOURCES
    comwidget.cpp
    qpluginactivator.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDACIFD.h
    comwidget.h
    qpluginactivator.h
)

set(UI_FILES
    ComWidget.ui
)

set(RES_FILES
    resource.qrc
)

# 指定输出库名：hierarch_da_com
set(LIB_NAME hierarch_da_com)

add_library(${LIB_NAME} SHARED
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RES_FILES}
)

# 链接 Qt 库
target_link_libraries(${LIB_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::SerialPort
	$<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKCore.lib>
    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKPluginFramework.lib>
)

# 去掉 lib 前缀，统一输出到 plugins 目录
set_target_properties(${LIB_NAME} PROPERTIES
    PREFIX ""                           # Linux/macOS 去掉 lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins   # Windows DLL
)

# 可选安装规则
# install(TARGETS ${LIB_NAME} DESTINATION plugins)