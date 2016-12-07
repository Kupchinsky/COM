#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QPair>
#include "../serverdll/component.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static void showErrorMessage(QWidget *parent, IProcessMonitor *iPM);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    IProcessMonitor *iPM;
    QThread *backgroundThread = NULL;

    void showError();

public slots:
    void handleResults(QMap<unsigned int, QPair<unsigned int, QString>> statuses);

signals:
    void stopBackgroundWork();
};

class Worker : public QObject
{
    Q_OBJECT

private:
    IProcessMonitor *iPM;
    bool isWorking = true;

public:
    Worker(IProcessMonitor *iPM) {
        this->iPM = iPM;
        this->iPM->AddRef();
    }

public slots:
    void doWork() {
        QMap<unsigned int, QPair<unsigned int, QString>> statuses;

        while (isWorking) {
            Sleep(2000);

            iPM->updateStatuses();

            unsigned int code;
            iPM->getLastError(&code, NULL, NULL);

            if (code != 0) {
                MainWindow::showErrorMessage(NULL, this->iPM);
            }

            statuses.clear();

            unsigned int resultPid;
            wchar_t *resultPname;
            unsigned int resultPnamelen;
            unsigned int resultStatus;

            if (iPM->getChangedStatusFirst(&resultPid, &resultPname, &resultPnamelen, &resultStatus) == S_OK) {
                QString pnameStr = QString::fromWCharArray(resultPname, resultPnamelen);
                statuses[resultPid] = QPair<unsigned int, QString>(resultStatus, pnameStr);

                while (iPM->getChangedStatusNext(&resultPid, &resultPname, &resultPnamelen, &resultStatus) == S_OK) {
                    pnameStr = QString::fromWCharArray(resultPname, resultPnamelen);
                    statuses[resultPid] = QPair<unsigned int, QString>(resultStatus, pnameStr);
                }
            }

            emit resultReady(statuses);
        }

        iPM->Release();
    }

    void stopWork() {
        isWorking = false;
    }

signals:
    void resultReady(QMap<unsigned int, QPair<unsigned int, QString>> statuses);
};
#endif // MAINWINDOW_H
