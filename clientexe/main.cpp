#include <QDebug>
#include <QException>
#include <QTime>
#include <windows.h>
#include <cassert>
#include <thread>

#include "../serverdll/component.h"
#include "result_checker.h"

using namespace std;

bool isExit = false;

void thrd_waitkey() {
    getchar();
    isExit = true;
}

void print_status(unsigned int pid, unsigned int status) {
    qDebug() << "";
}

int main(int argc, char **argv)
{
    CoInitialize(NULL);

    IProcessMonitor *iPM;
    ResultChecker::check(CoCreateInstance(LIBID_ProcessManager, NULL, CLSCTX_INPROC_SERVER,
                                          IID_IProcessMonitor, (void**) &iPM));

    qDebug() << "Registering...";

    QVector<QString> processes;
    processes.push_back("explorer.exe");
    processes.push_back("Skype.exe");
    processes.push_back("pageant.exe");

    foreach (QString processName, processes) {
        qDebug() << "Registering " << processName << " [by name]";

        wchar_t *str = (wchar_t*) processName.toStdWString().c_str();

        if (iPM->registerProcessByName(str) != S_OK) {
            qDebug() << "Registering failed!";
        }
    }

    thread thrdWaitKey(thrd_waitkey);
    qDebug() << "Monitoring... Press any key to stop";

    while (true) {
        if (isExit) {
            thrdWaitKey.join();
            qDebug() << "[Stopped by user request]";
            break;
        }

        Sleep(2000L);

        iPM->updateStatuses();

        unsigned int resultPid;
        wchar_t *resultPname;
        unsigned int resultPnamelen;
        unsigned int resultStatus;

        QString time = QTime::currentTime().toString(Qt::SystemLocaleLongDate);

        if (iPM->getChangedStatusFirst(&resultPid, &resultPname, &resultPnamelen, &resultStatus) == S_OK) {
            qDebug() << time << "Changed statuses:";
            qDebug() << "============================";

            print_status(resultPid, resultStatus);
            while (iPM->getChangedStatusNext(&resultPid, &resultPname, &resultPnamelen, &resultStatus) == S_OK) {
                print_status(resultPid, resultStatus);
            }

            qDebug() << "============================";
        } else {
            qDebug() << time << "No statuses changed at this time";
        }
    }

    ResultChecker::check(iPM->Release());

    CoUninitialize();
    return 0;
}
