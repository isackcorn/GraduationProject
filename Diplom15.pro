QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculate_error.cpp \
    finded_value.cpp \
    main.cpp \
    mainwindow.cpp \
    one_sample.cpp \
    qcustomplot.cpp \
    simulate.cpp \
    two_samples.cpp

HEADERS += \
    calculate_error.h \
    finded_value.h \
    mainwindow.h \
    one_sample.h \
    qcustomplot.h \
    simulate.h \
    two_samples.h

FORMS += \
    finded_value.ui \
    mainwindow.ui \
    one_sample.ui \
    simulate.ui \
    two_samples.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
