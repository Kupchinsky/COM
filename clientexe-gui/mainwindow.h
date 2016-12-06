#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QMainWindow>
#include <QMap>
#include "../serverdll/component.h"

namespace Ui {
class MainWindow;
}

class Worker : public QObject
{
    Q_OBJECT

private:
    IProcessMonitor *iPM;

public:
    Worker(IProcessMonitor *iPM) {
        this->iPM = iPM;
        this->iPM->AddRef();
    }

public slots:
    void doWork() {
        QMap<unsigned int, QPair<unsigned int, QString>> statuses;

        // TODO: fetch statuses

        emit resultReady(statuses);
    }

    void release() {
        iPM->Release();
    }

signals:
    void resultReady(QMap<unsigned int, QPair<unsigned int, QString>> statuses);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    IProcessMonitor *iPM;
    QThread *backgroundThread;

    void showError();

public slots:
    void handleResults(QMap<unsigned int, QPair<unsigned int, QString>> statuses); // TODO: impl
};

#endif // MAINWINDOW_H
