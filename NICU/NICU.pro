QT += widgets
QT += widgets serialport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ecgtest_dialog.cpp \
    heart_data.cpp \
    hemodialysis_dialog.cpp \
    main.cpp \
    main_dialog.cpp \
    progressbar_check.cpp \
    progressbar_round.cpp \
    progressbar_splash.cpp \
    serial_tool.cpp \
    user_data.cpp

HEADERS += \
    All_Header.h \
    ecgtest_dialog.h \
    heart_data.h \
    hemodialysis_dialog.h \
    main_dialog.h \
    progressbar_check.h \
    progressbar_round.h \
    progressbar_splash.h \
    serial_tool.h \
    user_data.h

FORMS += \
    ecgtest_dialog.ui \
    hemodialysis_dialog.ui \
    main_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
