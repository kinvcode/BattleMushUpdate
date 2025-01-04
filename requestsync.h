#ifndef REQUESTSYNC_H
#define REQUESTSYNC_H

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#define STR_VALUE(arg) #arg
#define STRINGIFY_MACRO(x) STR_VALUE(x)

class RequestSync
{
public:
    static QJsonObject getAPI(const QString path, bool is_encrypt = true);
};

#endif // REQUESTSYNC_H
