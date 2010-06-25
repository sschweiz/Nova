HEADERS += include/nwmmainwindow.h \
    include/nwmrender.h \
    include/nwmrenderwidget.h \
    include/qdockbutton.h \
    include/nwmdockwidget.h \
    include/nwmlistwidget.h \
    include/nwmoutputdock.h \
    include/nwmresultswidget.h \
    include/nwmresultitem.h \
    include/nwmtriggereditorwidget.h \
    include/nwmapp.h \
    include/nwmmodel.h \
    include/nwmtreeitem.h \
    include/nwmpropertywidget.h \
    include/nwmcomponentwidget.h \
    include/nwmaboutdialog.h
SOURCES += src/nwmmainwindow.cpp \
    src/entry.cpp \
    src/nwmrender.cpp \
    src/nwmrenderwidget.cpp \
    src/qdockbutton.cpp \
    src/nwmdockwidget.cpp \
    src/nwmlistwidget.cpp \
    src/nwmoutputdock.cpp \
    src/nwmresultswidget.cpp \
    src/nwmresultitem.cpp \
    src/nwmtriggereditorwidget.cpp \
    src/nwmapp.cpp \
    src/nwmmodel.cpp \
    src/nwmtreeitem.cpp \
    src/nwmpropertywidget.cpp \
    src/nwmcomponentwidget.cpp \
    src/nwmaboutdialog.cpp
QT += opengl
LIBS += -lqscintilla2
RESOURCES += nwm.qrc
FORMS += nwmaboutdialog.ui
OBJECTS_DIR = obj
MOC_DIR = obj
RCC_DIR = src
INCLUDEPATH += include
TARGET = Nova
DESTDIR = bin
