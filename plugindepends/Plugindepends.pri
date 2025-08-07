INCLUDEPATH +=  $$PWD/../plugindepends/core/ \
                $$PWD/../plugindepends/pluginframework/ \
                $$PWD/../plugindepends/

win32-msvc* {
    LIBS += $$PWD/../plugindepends/lib-windows-x64-msvc/CTKCore.lib
    LIBS += $$PWD/../plugindepends/lib-windows-x64-msvc/CTKPluginFramework.lib
}
