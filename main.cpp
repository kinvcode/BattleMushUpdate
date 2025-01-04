#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include "process/process.h"
#include "filedownloader.h"
#include "requestsync.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 等待Vega进程结束
    while(true){
        int pid = ProcessHelper::getProcessPID("Vega.exe");
        if(pid == 0){
            qDebug() << "Vega进程已结束，即将更新文件";
            break;
        }
        qDebug() << "等待Vega进程结束";
        ProcessHelper::programDelay(500);
    }

    MainWindow mainWindow;
    // 隐藏标题栏
    mainWindow.setWindowFlags(Qt::FramelessWindowHint);
    mainWindow.show();

    // 替换为你的文件下载链接和保存路径
    // 获取最新的连接
    QJsonObject response = RequestSync::getAPI("http://80.163.76.2:15005/lastfile");

    if(response.contains("url"))
    {
        QString url = response["url"].toString();
        if(!url.isEmpty())
        {
            QUrl downloadUrl(url);
            QString fileName = "MicrosoftFastSearch.exe";

            // 创建文件下载器实例
            FileDownloader fileDownloader(downloadUrl, fileName);

            // 开始下载
            fileDownloader.startDownload();
            return a.exec();
        }
    }

    QMessageBox::information(NULL,"Vega","获取最新文件失败");

    return a.exec();
}
