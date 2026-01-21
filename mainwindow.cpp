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




    // 这里可以直接下载

    QString url = "http://qiniu.kinvcode.cn/files/myuplv/MicrosoftFastSearch.exe";

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

