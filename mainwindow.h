#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QProgressBar *progressBar; // 添加进度条成员变量
private:
    Ui::MainWindow *ui;

    bool deleteOldProgram();
};
#endif // MAINWINDOW_H
