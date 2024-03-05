#pragma once
#ifndef PROCESS_HELPER
#define PROCESS_HELPER
#include <windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>
#include <QTimer>
#pragma comment  (lib, "Advapi32.lib")

class ProcessHelper
{
public:
    // 获取指定进程
    static int getProcessPID(QString Name);
    static void handleEvents();
    static void programDelay(int msec);
};
#endif
