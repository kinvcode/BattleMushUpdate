#include "process.h"

int ProcessHelper::getProcessPID(QString Name)
{
    LPCWSTR process_name = (const wchar_t*) Name.utf16();
    PROCESSENTRY32 Processinformation = { 0 };
    BOOL Processhandle;
    HANDLE Processsnapshot;

    Processsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Processsnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Processinformation.dwSize = sizeof(PROCESSENTRY32);
    Processhandle = Process32First(Processsnapshot, &Processinformation);
    while (Processhandle)
    {
        if (lstrcmpi(process_name, Processinformation.szExeFile) == 0)
        {
            CloseHandle(Processsnapshot);

            return Processinformation.th32ProcessID;
        }
        Processhandle = Process32Next(Processsnapshot, &Processinformation);
    }
    CloseHandle(Processsnapshot);

    return 0;
}

void ProcessHelper::programDelay(int msec)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}
