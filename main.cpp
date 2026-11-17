#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include "process/process.h"
#include "filedownloader.h"
#include "requestsync.h"
#include <QProgressBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // // 等待Vega进程结束
    // while(true){
    //     int pid = ProcessHelper::getProcessPID("Vega.exe");
    //     if(pid == 0){
    //         qDebug() << "Vega进程已结束，即将更新文件";
    //         break;
    //     }
    //     qDebug() << "等待Vega进程结束";
    //     ProcessHelper::programDelay(500);
    // }

    MainWindow mainWindow;
    // 隐藏标题栏
    mainWindow.setWindowFlags(Qt::FramelessWindowHint);
    mainWindow.show();

    return a.exec();
}
