QT += core
QT -= gui

CONFIG += c++11

TARGET = dlibface
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    stfz_facematch.cpp \
    stfz_facedetect.cpp

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_objdetect.so \
        /usr/local/lib/libopenblas_sandybridgep-r0.2.19.so \
        /usr/local/lib/libdlib.a                           \
        /usr/lib/x86_64-linux-gnu/libjpeg.so.8              \
        /lib/x86_64-linux-gnu/libpng12.so.0                 \
        /usr/lib/x86_64-linux-gnu/libX11.so.6

HEADERS += \
    stfz_facematch.h \
    stfz_facedetect.h
