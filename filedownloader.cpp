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
    if (bytesTotal > 0) {
        int progress = static_cast<int>((bytesReceived * 100) / bytesTotal);
        emit downloadProgressUpdated(progress);
        // 处理下载进度，可以根据需要进行显示
        qDebug() << "Download Progress: " << bytesReceived << " / " << bytesTotal;
    }
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
            QMessageBox::information(NULL,"Vega","下载失败，无法保存文件!");
        }
    } else {
        // 处理下载错误
        qDebug() << "Error: " << reply->errorString();
        QMessageBox::information(NULL,"BattleMush","下载失败，请确认云存储是否存在该文件!");
    }

    // 释放资源 会报错
    // reply->deleteLater();
    // networkManager.deleteLater();

    // 弹出消息框
    int ret = QMessageBox::information(
        nullptr, "BattleMush", "BattleMush更新完毕!", QMessageBox::Ok);

    // 判断用户点击的按钮
    if (ret == QMessageBox::Ok) {
        QCoreApplication::quit();  // 结束应用程序
    }
}
