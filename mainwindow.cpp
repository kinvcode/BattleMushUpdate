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

    bool is_custom = true; // 是否是客户下载

    if(is_custom){
        // 替换为你的文件下载链接和保存路径
        // 获取最新的连接

        QJsonObject response = RequestSync::getAPI("http://battle.kinvcode.cn/lastfile");

        // ProcessHelper::programDelay(1500);

        while(true){
            if(ProcessHelper::getProcessPID("BattleMush.exe") == 0)
            {
                break;
            }
            ProcessHelper::programDelay(500);
        }

        // 获取当前程序运行目录
        QString currentDir = QCoreApplication::applicationDirPath();

        // // 拼接文件路径
        QString filePath = currentDir + "/BattleMush.exe";

        // 使用 QFile 判断文件是否存在
    check_exe_exists:
        QFile BattleMush_exe_file(filePath);
        if (BattleMush_exe_file.exists()) {
            // 先删除文件
            // 判断是否可写
            if (!BattleMush_exe_file.isWritable()) {
                qDebug() << "驱动文件不可写";

                QFile::Permissions currentPerms = BattleMush_exe_file.permissions();
                qDebug() << "修改前权限：" << currentPerms;

                // 添加写权限（移除非写权限）
                if (BattleMush_exe_file.setPermissions(currentPerms | QFile::WriteOwner)) {
                    qDebug() << "使用Qt成功修改文件权限";
                } else {
                    qDebug() << "使用Qt修改权限失败：" << BattleMush_exe_file.errorString();
                }
            }

            if(!BattleMush_exe_file.remove())
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
                QString fileName = "BattleMush.exe";

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
    }else{
        // 这里可以直接下载

        QString url = "http://qiniu.kinvcode.cn/files/mybattle/BattleMush.exe";

        QUrl downloadUrl(url);
        QString fileName = "BattleMush.exe";

        // 创建文件下载器实例
        FileDownloader* fileDownloader = new FileDownloader(downloadUrl, fileName);

        connect(fileDownloader, &FileDownloader::downloadProgressUpdated, ui->progressBar, &QProgressBar::setValue);

        // 开始下载
        fileDownloader->startDownload();
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::deleteOldProgram()
{

    // 如果存在源文件，直接删除
    QString program_path = QCoreApplication::applicationDirPath() + "/BattleMush.exe";

    QFile program_file(program_path);
    if(!program_file.exists()){
        return true;
    }

    // 判断是否可写
    if (!program_file.isWritable()) {
        qDebug() << "驱动文件不可写";

        QFile::Permissions currentPerms = program_file.permissions();
        qDebug() << "修改前权限：" << currentPerms;

        // 添加写权限（移除非写权限）
        if (program_file.setPermissions(currentPerms | QFile::WriteOwner)) {
            qDebug() << "使用Qt成功修改文件权限";
        } else {
            qDebug() << "使用Qt修改权限失败：" << program_file.errorString();
        }
    }

    if(!program_file.remove())
    {
        QMessageBox::information(NULL,"BattleMush","程序旧文件删除失败！");


        QFile::FileError error = program_file.error();
        QString errorStr = program_file.errorString();

        QString message = QString("驱动缓存文件删除失败！\n"
                                  "文件: %1\n"
                                  "错误代码: %2\n"
                                  "错误描述: %3")
                              .arg(program_path)
                              .arg(static_cast<int>(error))
                              .arg(errorStr);

        // 添加更具体的错误分析
        switch (error) {
        case QFile::PermissionsError:
            message += "\n原因: 权限不足，请以管理员身份运行程序";
            break;
        // case QFile::AccessError:
        //     message += "\n原因: 文件可能正在被其他程序使用";
        //     break;
        case QFile::ResizeError:
            message += "\n原因: 文件系统错误";
            break;
        case QFile::RemoveError:
            message += "\n原因: 无法删除文件，检查文件属性和安全设置";
            break;
        default:
            break;
        }

        QMessageBox::critical(nullptr, "BattleMush", message);
    }

    if(!program_file.exists()){
        return true;
    }

    return false;
}

