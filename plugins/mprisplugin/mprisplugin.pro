include($$PWD/../plugins.pri)

unix:!mac:!android {
    QT += dbus
    DEFINES += HAVE_DBUS

    HEADERS += $$PWD/mprisadapter.h \
           $$PWD/mpriscontroller.h \
           $$PWD/mprisplugin.h

    SOURCES += $$PWD/mprisadapter.cpp \
           $$PWD/mpriscontroller.cpp \
           $$PWD/mprisplugin.cpp
}

OTHER_FILES += $$PWD/metadata.json

