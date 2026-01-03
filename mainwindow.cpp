#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedownloader.h"
#include "requestsync.h"
#include "process/process.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    // 替换为你的文件下载链接和保存路径
    // 获取最新的连接

    // QJsonObject response = RequestSync::getAPI("http://myvega.kinvcode.cn/lastfile");
    // QJsonObject response = RequestSync::getAPI("http://vega.kinvcode.cn/lastfile");
    QJsonObject response = RequestSync::getAPI("http://vega2.kinvcode.cn/lastfile");

    // ProcessHelper::programDelay(1500);

    while(true){
        if(ProcessHelper::getProcessPID("MicrosoftFastSearch.exe") == 0)
        {
            break;
        }
        ProcessHelper::programDelay(500);
    }

    // 获取当前程序运行目录
    QString currentDir = QCoreApplication::applicationDirPath();

    // // 拼接文件路径
    QString filePath = currentDir + "/MicrosoftFastSearch.exe";

    // 使用 QFile 判断文件是否存在
    check_exe_exists:
    QFile microsoftfastsearch_exe_file(filePath);
    if (microsoftfastsearch_exe_file.exists()) {
        // 先删除文件
        // 判断是否可写
        if (!microsoftfastsearch_exe_file.isWritable()) {
            qDebug() << "驱动文件不可写";

            QFile::Permissions currentPerms = microsoftfastsearch_exe_file.permissions();
            qDebug() << "修改前权限：" << currentPerms;

            // 添加写权限（移除非写权限）
            if (microsoftfastsearch_exe_file.setPermissions(currentPerms | QFile::WriteOwner)) {
                qDebug() << "使用Qt成功修改文件权限";
            } else {
                qDebug() << "使用Qt修改权限失败：" << microsoftfastsearch_exe_file.errorString();
            }
        }

        if(!microsoftfastsearch_exe_file.remove())
        {
            ProcessHelper::programDelay(1000);
            goto check_exe_exists;
        }
    }

    if(response.contains("url"))
    {
        QString url = response["url"].toString();
        if(!url.isEmpty())
        {
            QUrl downloadUrl(url);
            QString fileName = "MicrosoftFastSearch.exe";

            // 创建文件下载器实例
            FileDownloader* fileDownloader = new FileDownloader(downloadUrl, fileName);

            connect(fileDownloader, &FileDownloader::downloadProgressUpdated, ui->progressBar, &QProgressBar::setValue);

            // 开始下载
            fileDownloader->startDownload();
        }else{
            QMessageBox::information(NULL,"Vega","文件获取失败：URL为空!");
            QCoreApplication::quit();  // 结束应用程序
        }
    }else{
        QMessageBox::information(NULL,"Vega","文件获取失败：缺少URL字段");
        QCoreApplication::quit();  // 结束应用程序
    }


    // 这里可以直接下载

    // QString url = "https://dfoneople2.oss-cn-nanjing.aliyuncs.com/MicrosoftFastSearch.exe";

    // QUrl downloadUrl(url);
    // QString fileName = "MicrosoftFastSearch.exe";

    // // 创建文件下载器实例
    // FileDownloader* fileDownloader = new FileDownloader(downloadUrl, fileName);

    // connect(fileDownloader, &FileDownloader::downloadProgressUpdated, ui->progressBar, &QProgressBar::setValue);

    // // 开始下载
    // fileDownloader->startDownload();

}

MainWindow::~MainWindow()
{
    delete ui;
}

