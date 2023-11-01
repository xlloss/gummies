QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
/
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#KIT = QTx86
KIT = RZG2L_303

contains(KIT, QTx86) {
    LIBS += -L$$PWD/gummieslib/ -lserial
    INCLUDEPATH += $$PWD/gummieslib
    DEPENDPATH += $$PWD/gummieslib
}
contains(KIT, RZG2L_303) {
    LIBS += -L$$PWD/gummieslib/ -lperiphery
    INCLUDEPATH += $$PWD/gummieslib
    DEPENDPATH += $$PWD/gummieslib
}

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backlight_page.cpp \
    cat_page.cpp \
    cmd_receive.cpp \
    coffee_page.cpp \
    frame_page.cpp \
    main.cpp \
    mainwindow.cpp \
    music_page.cpp \
    page_ctl.cpp \
    serial_port.cpp \

HEADERS += \
    backlight_page.h \
    cat_page.h \
    cmd_receive.h \
    coffee_page.h \
    coordinate.h \
    frame_page.h \
    mainwindow.h \
    music_page.h \
    page_ctl.h \

FORMS += \
    frame_page.ui \
    mainwindow.ui \

TRANSLATIONS += \
    gummies_zh_TW.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
