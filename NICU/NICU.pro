QT += widgets
QT += widgets serialport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ecgtest_dialog.cpp \
    heart_data.cpp \
    main.cpp \
    main_dialog.cpp \
    serial_dialog.cpp \
    serial_tool.cpp \
    user_data.cpp

HEADERS += \
    All_Header.h \
    ecgtest_dialog.h \
    heart_data.h \
    main_dialog.h \
    serial_dialog.h \
    serial_tool.h \
    user_data.h

FORMS += \
    ecgtest_dialog.ui \
    main_dialog.ui \
    serial_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# RESOURCES += \
#     Resource.qrc
