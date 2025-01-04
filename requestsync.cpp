#include "requestsync.h"

QJsonObject RequestSync::getAPI(const QString path, bool is_encrypt)
{
    QJsonObject jsonObject;

    //QString domain = QString(STRINGIFY_MACRO(API_URL));
    //QString api = domain + path;
    QString api =  path;

    // 创建QNetworkAccessManager对象
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // 设置请求URL
    QUrl url(api);

    // 创建HTTP请求
    QNetworkRequest request(url);

    // 发送GET请求
    QNetworkReply *reply = manager->get(request);

    // 创建事件循环
    QEventLoop loop;

    // 连接请求完成的信号
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            // 读取响应数据
            QByteArray responseData = reply->readAll();

            // 解析JSON数据
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
            jsonObject = jsonDocument.object();
        } else {
            // 处理错误
            qDebug() << "HTTP请求错误: " << reply->errorString();
        }

        // 释放资源
        reply->deleteLater();
        manager->deleteLater();

        // 退出事件循环
        loop.quit();
    });

    // 启动事件循环
    loop.exec();

    return jsonObject;
}
