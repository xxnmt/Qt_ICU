#include "main_dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // 关闭硬件OpenGL加速，根治显卡驱动全局渲染残留黑块
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    // 统一渲染风格，消除系统主题渲染bug
    QApplication::setStyle("Fusion");

    QApplication a(argc, argv);
    Main_Dialog w;
    w.show();
    return a.exec();
}
