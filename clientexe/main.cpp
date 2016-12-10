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

void print_status(unsigned int pid, QString pname, unsigned int status) {
    qDebug() << pname << "(" + QString::number(pid) + ")" << "Status: " +  QString::number(status);
}

int main(int argc, char **argv)
{
    CoInitialize(NULL);

    IUnknown *iUnk;
    ResultChecker::check(CoCreateInstance(LIBID_ProcessManager, NULL, CLSCTX_INPROC_SERVER,
                                          IID_IUnknown, (void**) &iUnk));

    IProcessMonitor *iPM;
    IProcessMonitorRegistrar *iPMR;

    ResultChecker::check(iUnk->QueryInterface(IID_IProcessMonitor, (void**) &iPM));
    ResultChecker::check(iUnk->QueryInterface(IID_IProcessMonitorRegistrar, (void**) &iPMR));

    qDebug() << "[IProcessMonitorRegistrar] Registering by pids...";

    QVector<unsigned int> processes;
    //processes.push_back();

    foreach (unsigned int pid, processes) {
        qDebug() << "[IProcessMonitorRegistrar] Registering" << pid << "by pid";

        if (iPMR->pushPid(pid) != S_OK) {
            wchar_t *errorMsg;
            unsigned int errorMsgLen;

            if (iPMR->getLastError(NULL, &errorMsg, &errorMsgLen) == S_OK) {
                qDebug() << "[IProcessMonitorRegistrar] Registering failed!" << QString::fromWCharArray(errorMsg, errorMsgLen);
            }
        }
    }

    thread thrdWaitKey(thrd_waitkey);
    qDebug() << "Monitoring... Press any key to stop";

    forever {
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

            print_status(resultPid, QString::fromWCharArray(resultPname, resultPnamelen),
                         resultStatus);
            while (iPM->getChangedStatusNext(&resultPid, &resultPname, &resultPnamelen, &resultStatus) == S_OK) {
                print_status(resultPid, QString::fromWCharArray(resultPname, resultPnamelen),
                             resultStatus);
            }

            qDebug() << "============================";
        } else {
            qDebug() << time << "No statuses changed at this time";
        }
    }

    iUnk->Release();
    iPM->Release();
    iPMR->Release();

    CoUninitialize();
    return 0;
}
