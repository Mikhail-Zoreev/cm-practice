QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    include \
    thirdparty/qcustomplot


SOURCES += \
    src/abstractaccuratesolution.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/plotdialog.cpp \
    src/rkmethodsolver.cpp \
    src/sampleaccuratesolution.cpp \
    src/sampleequationsystem.cpp \
    src/solutiontaablemodel.cpp \
    thirdparty/qcustomplot/qcustomplot.cpp

HEADERS += \
    include/abstractaccuratesolution.h \
    include/abstractequationsystem.h \
    include/mainwindow.h \
    include/plotdialog.h \
    include/rkmethodsolver.h \
    include/sampleaccuratesolution.h \
    include/sampleequationsystem.h \
    include/solutiontablemodel.h \
    thirdparty/qcustomplot/qcustomplot.h

FORMS += \
    ui/mainwindow.ui \
    ui/plotdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
