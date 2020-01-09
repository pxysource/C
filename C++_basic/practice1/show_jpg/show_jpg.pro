TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    showjpg.c

HEADERS += \
    showjpg.h

#指定jpg库的头文件路径，不用加-I选项
INCLUDEPATH += /home/linux/jpg/include
#指定jpg库的路径
LIBS += -L/home/linux/jpg/lib
#jpg库
LIBS += -ljpeg
LIBS += -Wl,-rpath=/home/linux/jpg/lib
