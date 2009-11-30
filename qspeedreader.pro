# set the build parameters
TARGET = qspeedreader
TEMPLATE = app
DESTDIR = bin

# change output paths for temporary files
OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .ui
RCC_DIR = .rcc
SOURCES += main.cpp \
    mainwindow.cpp \
    settings.cpp \
    colordialog.cpp
HEADERS += mainwindow.h \
    settings.h \
    colordialog.h
FORMS += mainwindow.ui \
    colordialog.ui
OTHER_FILES += README \
    LICENCE
TRANSLATIONS = lang/qspeedreader_en.ts \
    lang/qspeedreader_de.ts

# switch on extra compiler stuff
QMAKE_CXXFLAGS = -ansi \
    -Wall
QMAKE_CXXFLAGS_RELEASE = -mmmx \
    -msse \
    -Os
QMAKE_LFLAGS = -ansi \
    -Wall
QMAKE_LFLAGS_RELEASE = -mmmx \
    -msse \
    -Os
