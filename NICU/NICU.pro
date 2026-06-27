QT += widgets
QT += widgets serialport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bloodpressure.cpp \
    bloodpressure_dialog.cpp \
    ecgtest_dialog.cpp \
    heart_data.cpp \
    hemodialysis_dialog.cpp \
    main.cpp \
    main_dialog.cpp \
    plot_data.cpp \
    progressbar_check.cpp \
    progressbar_round.cpp \
    progressbar_splash.cpp \
    serial_tool.cpp \
    user_data.cpp

HEADERS += \
    All_Header.h \
    bloodpressure.h \
    bloodpressure_dialog.h \
    ecgtest_dialog.h \
    heart_data.h \
    hemodialysis_dialog.h \
    main_dialog.h \
    plot_data.h \
    progressbar_check.h \
    progressbar_round.h \
    progressbar_splash.h \
    serial_tool.h \
    user_data.h

FORMS += \
    bloodpressure_dialog.ui \
    ecgtest_dialog.ui \
    hemodialysis_dialog.ui \
    main_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

# 定义必要的宏
DEFINES += QT_DLL QWT_DLL

# 头文件路径
INCLUDEPATH += D:/Qt/6.11.1/mingw_64/include/QtQwt

# 库文件路径
LIBS += -L"D:/Qt/6.11.1/mingw_64/lib"
# 根据构建模式链接对应的库
CONFIG(debug, debug|release) {
    LIBS += -lqwtd
} else {
    LIBS += -lqwt
}
