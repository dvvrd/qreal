QT += widgets

CONFIG += c++11

INCLUDEPATH += \
	$$PWD/../../.. \
	$$PWD/../../../qrgui/ \
	$$PWD/../../../qrtext/include/ \

LIBS += -L$$PWD/../../../bin -lqrkernel -lqrutils -lqrgui-preferences-dialog

TRANSLATIONS = $$PWD/../../../qrtranslations/ru/plugins/visualDebugSupport_ru.ts

HEADERS = \
	$$PWD/visualDebuggerPlugin.h \
	$$PWD/visualDebuggerPreferencesPage.h \

SOURCES = \
	$$PWD/visualDebuggerPlugin.cpp \
	$$PWD/visualDebuggerPreferencesPage.cpp \

FORMS += \
	$$PWD/visualDebuggerPreferencesPage.ui \

RESOURCES += \
	$$PWD/visualDebugger.qrc \

include($$PWD/interpreter/interpreter.pri)
