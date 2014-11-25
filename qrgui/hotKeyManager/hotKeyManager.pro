TEMPLATE = lib

DESTDIR = $$PWD/../../bin

TARGET = qrgui-hotkey-manager

LIBS += -L$$PWD/../../bin -lqrgui-preferences-dialog

INCLUDEPATH = \
	$$PWD/ \
	$$PWD/../ \
	$$PWD/../../ \

QT += widgets

CONFIG += c++11

OBJECTS_DIR = .obj
UI_DIR = .ui
MOC_DIR = .moc
RCC_DIR = .moc

DEFINES += QRGUI_HOTKEY_MANAGER_LIBRARY

TRANSLATIONS = $$PWD/../../qrtranslations/ru/qrgui_hotKeyManager_ru.ts

HEADERS += \
	$$PWD/hotKeyManagerDeclSpec.h \
	$$PWD/hotKeyManagerPage.h \
	$$PWD/hotKeyManager.h \
	$$PWD/shortcutEdit.h \

SOURCES += \
	$$PWD/hotKeyManagerPage.cpp \
	$$PWD/hotKeyManager.cpp \
	$$PWD/shortcutEdit.cpp \

FORMS += \
	$$PWD/hotKeyManagerPage.ui \

RESOURCES += \
	$$PWD/hotKeyManager.qrc \
