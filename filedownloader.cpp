#include "filedownloader.h"

FileDownloader::FileDownloader(const QUrl &url, const QString &fileName, QObject *parent)
    : QObject(parent), url(url), fileName(fileName)
{
    connect(&networkManager, &QNetworkAccessManager::finished, this, &FileDownloader::onDownloadFinished);
}

void FileDownloader::startDownload()
{
    QNetworkRequest request(url);
    networkReply = networkManager.get(request);
    connect(networkReply, &QNetworkReply::downloadProgress, this, &FileDownloader::onDownloadProgress);
}

void FileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // 处理下载进度，可以根据需要进行显示
    qDebug() << "Download Progress: " << bytesReceived << " / " << bytesTotal;
}

void FileDownloader::onDownloadFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // 保存下载的文件到当前程序的运行目录
        QString filePath = QCoreApplication::applicationDirPath() + "/" + fileName;

        QFile outputFile(filePath);
        if (outputFile.open(QIODevice::WriteOnly)) {
            outputFile.write(reply->readAll());
            outputFile.close();
            qDebug() << "Download finished. File saved to: " << filePath;
        } else {
            qDebug() << "Error: Could not open file for writing.";
        }
    } else {
        // 处理下载错误
        qDebug() << "Error: " << reply->errorString();
    }

    // 释放资源
    reply->deleteLater();
    networkManager.deleteLater();
    QMessageBox::information(NULL,"Vega","Vega更新完毕!");
    QCoreApplication::quit();  // 结束应用程序
}
