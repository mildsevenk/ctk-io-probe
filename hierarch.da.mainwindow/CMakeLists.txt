cmake_minimum_required(VERSION 3.10)

# 项目名保留目录可读，输出库名改为下划线
project(hierarch.da.mainwindow VERSION 1.0.0 LANGUAGES CXX)

# Qt 自动化
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

# 所需 Qt5 模块
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# 公共头文件目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/pluginframework
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends
)

# 源文件
set(SOURCES
    mainwindow.cpp
    qpluginactivator.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDACIFD.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDADataShowFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDAMainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/IDAWidget.h
    mainwindow.h
    qpluginactivator.h
)

set(UI_FILES
    MainWindow.ui
)

set(RES_FILES
    resource.qrc
)

# 指定输出库名
set(LIB_NAME hierarch_da_mainwindow)

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
	$<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKCore.lib>
    $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/../plugindepends/lib-windows-x64-msvc/CTKPluginFramework.lib>
)

# 产物设置
set_target_properties(${LIB_NAME} PROPERTIES
    PREFIX ""                           # 去掉 lib 前缀
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)

# 可选安装
# install(TARGETS ${LIB_NAME}
#         LIBRARY DESTINATION plugins
#         RUNTIME DESTINATION plugins)