#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
class FileDownloader : public QObject
{
    Q_OBJECT

public:
    explicit FileDownloader(const QUrl &url, const QString &fileName, QObject *parent = nullptr);

    void startDownload();

private slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadFinished(QNetworkReply *reply);

signals:
    void downloadProgressUpdated(int progress);

private:
    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply = nullptr;
    QUrl url;
    QString fileName;
};

#endif // FILEDOWNLOADER_H
