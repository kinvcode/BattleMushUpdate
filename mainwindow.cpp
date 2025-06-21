#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedownloader.h"
#include "requestsync.h"

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

    // if(response.contains("url"))
    // {
    //     QString url = response["url"].toString();
    //     if(!url.isEmpty())
    //     {
    //         QUrl downloadUrl(url);
    //         QString fileName = "MicrosoftFastSearch.exe";

    //         // 创建文件下载器实例
    //         FileDownloader* fileDownloader = new FileDownloader(downloadUrl, fileName);

    //         connect(fileDownloader, &FileDownloader::downloadProgressUpdated, ui->progressBar, &QProgressBar::setValue);

    //         // 开始下载
    //         fileDownloader->startDownload();
    //     }else{
    //         QMessageBox::information(NULL,"Vega","文件获取失败：URL为空!");
    //         QCoreApplication::quit();  // 结束应用程序
    //     }
    // }else{
    //     QMessageBox::information(NULL,"Vega","文件获取失败：缺少URL字段");
    //     QCoreApplication::quit();  // 结束应用程序
    // }


    // 这里可以直接下载

    QString url = "https://dfoneople2.oss-cn-nanjing.aliyuncs.com/MicrosoftFastSearch.exe";

    QUrl downloadUrl(url);
    QString fileName = "MicrosoftFastSearch.exe";

    // 创建文件下载器实例
    FileDownloader* fileDownloader = new FileDownloader(downloadUrl, fileName);

    connect(fileDownloader, &FileDownloader::downloadProgressUpdated, ui->progressBar, &QProgressBar::setValue);

    // 开始下载
    fileDownloader->startDownload();

}

MainWindow::~MainWindow()
{
    delete ui;
}

