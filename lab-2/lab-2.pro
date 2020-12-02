QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    include

SOURCES += \
    src/equationssystemmodel.cpp \
    src/gaussmethodsolver.cpp \
    src/matrix.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/newequationssystemdialog.cpp \
    src/solutionmodel.cpp

HEADERS += \
    include/equationssystemmodel.h \
    include/equationssystemsolver.h \
    include/gaussmethodsolver.h \
    include/matrix.h \
    include/mainwindow.h \
    include/newequationssystemdialog.h \
    include/solutionmodel.h

FORMS += \
    ui/mainwindow.ui \
    ui/newequationssystemdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
