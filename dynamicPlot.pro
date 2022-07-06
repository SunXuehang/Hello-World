QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += EIGEN_NO_DEBUG
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart.cpp \
    chartview.cpp \
    gnss_signal.cpp \
    main.cpp \
    math_operation.cpp \
    plot_window.cpp \
    receiver.cpp \
    trace_init.cpp

HEADERS += \
    chart.h \
    chartview.h \
    gnss_signal.h \
    math_operation.h \
    plot_window.h \
    receiver.h \
    trace_init.h

FORMS += \
    plot_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
