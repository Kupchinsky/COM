#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../clientexe/result_checker.h"

#include <QMessageBox>
#include <QTime>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CoInitialize(NULL);

    ResultChecker::check(CoCreateInstance(LIBID_ProcessManagerEx, NULL, CLSCTX_INPROC_SERVER,
                                          IID_IProcessMonitor, (void**) &iPM));
    ResultChecker::check(iPM->QueryInterface(IID_IProcessMonitorRegistrarEx, (void**) &iPMREx));

    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);

    QStringList lbls;
    lbls.append("Pid");
    lbls.append("Process name");
    lbls.append("Status");
    lbls.append("Time");

    ui->tableWidget->setHorizontalHeaderLabels(lbls);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->iPMRExTableWidget->setColumnCount(1);

    QStringList lbls2;
    lbls2.append("Pattern");

    ui->iPMRExTableWidget->setHorizontalHeaderLabels(lbls2);
    ui->iPMRExTableWidget->verticalHeader()->setVisible(false);
    ui->iPMRExTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->iPMRExTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->listView->setModel(new QStandardItemModel());

    qRegisterMetaType<QMap<uint,QPair<uint,QString> >>("QMap<uint,QPair<uint,QString> >");
}

MainWindow::~MainWindow()
{
    delete ui;

    if (this->backgroundThread != NULL) {
        this->backgroundThread->quit();
        delete this->backgroundThread;
    }

    iPM->Release();
    iPMREx->Release();
    CoUninitialize();
}

void MainWindow::showErrorMessage(QWidget *parent, IProcessMonitor *iPM) {
    iPM->AddRef();

    wchar_t *errorMsg;
    unsigned int errorMsgLen;
    QString result;

    if (iPM->getLastError(NULL, &errorMsg, &errorMsgLen) == S_OK) {
        result = QString::fromWCharArray(errorMsg, errorMsgLen);
    } else {
        result = "[getLastError invalid result]";
    }

    QMessageBox::warning(parent, "Error", "Component error: " + result,
                         QMessageBox::Ok, QMessageBox::NoButton);

    iPM->Release();
}

void MainWindow::showError() {
    MainWindow::showErrorMessage(ui->centralWidget, this->iPM);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->pushButton_5->setEnabled(!ui->checkBox->isChecked());

    if (ui->checkBox->isChecked()) {
        this->backgroundThread = new QThread();
        Worker *worker = new Worker(this->iPM);
        worker->moveToThread(this->backgroundThread);

        ui->centralWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(ui->centralWidget, SIGNAL(destroyed(QObject*)), this->backgroundThread, SLOT(deleteLater()));
        connect(this->backgroundThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(this, SIGNAL(stopBackgroundWork()), worker, SLOT(stopWork()));
        connect(this->backgroundThread, SIGNAL(started()), worker, SLOT(doWork()));
        connect(worker, SIGNAL(resultReady(QMap<unsigned int, QPair<unsigned int, QString>>)),
                this, SLOT(handleResults(QMap<unsigned int, QPair<unsigned int, QString>>)));

        this->backgroundThread->start();
    } else {
        emit stopBackgroundWork();
        this->backgroundThread = NULL;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if (iPM->updateStatuses() != S_OK) {
        unsigned int code;
        iPM->getLastError(&code, NULL, NULL);

        if (code != 0) {
            this->showError();
        }
    }

    QMap<unsigned int, QPair<unsigned int, QString>> statuses;

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

    emit handleResults(statuses);
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (ui->checkBox_2->isChecked()) {
        ui->tableWidget->scrollToBottom();
    }
}

void MainWindow::handleResults(QMap<unsigned int, QPair<unsigned int, QString>> statuses) {
    QMapIterator<unsigned int, QPair<unsigned int, QString>> iterator(statuses);

    QString time = QTime::currentTime().toString(Qt::SystemLocaleLongDate);

    while (iterator.hasNext()) {
        iterator.next();
        unsigned int pid = iterator.key();
        QPair<unsigned int, QString> pair = iterator.value();

        int row = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(pid)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(pair.second));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(pair.first)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(time));
    }

    if (ui->checkBox_2->isChecked()) {
        ui->tableWidget->scrollToBottom();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_pushButton_7_clicked()
{
    if (iPMREx->clearPids() != S_OK) {
        this->showError();
    } else {
        QAbstractItemModel *model = ui->listView->model();
        model->removeRows(0, model->rowCount());
    }
}

void MainWindow::on_iPMRExRegisterBtn_clicked()
{
    QString pName = ui->iPMRExInput->text();

    if (iPMREx->registerProcessByName((wchar_t*) pName.toStdWString().c_str()) != S_OK) {
        this->showError();
    } else {
        int row = ui->iPMRExTableWidget->rowCount();

        ui->iPMRExTableWidget->insertRow(row);
        ui->iPMRExTableWidget->setItem(row, 0, new QTableWidgetItem(pName));
        ui->iPMRExInput->clear();
    }
}

void MainWindow::on_iPMRExUnregisterBtn_clicked()
{
    QItemSelectionModel *select = ui->iPMRExTableWidget->selectionModel();

    if (select->hasSelection()) {
        QModelIndexList modellist = select->selectedRows();

        if (modellist.size() != 0) {
            QModelIndex modelIndex = modellist.at(0);
            int row = modelIndex.row();

            QString value = ui->iPMRExTableWidget->item(row, 0)->text();

            if (iPMREx->unregisterProcessByName((wchar_t*)value.toStdWString().c_str()) != S_OK) {
                this->showError();
            } else {
                ui->iPMRExTableWidget->removeRow(row);
            }

            return;
        }
    }

    QMessageBox::warning(ui->centralWidget, "Error", "No selection!",
                         QMessageBox::Ok, QMessageBox::NoButton);
}

void MainWindow::on_iPMRExUnregisterAllBtn_clicked()
{
    if (iPMREx->unregisterAllNames() != S_OK) {
        this->showError();
    } else {
        ui->iPMRExTableWidget->setRowCount(0);
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QStandardItemModel *model = static_cast<QStandardItemModel*>(ui->listView->model());

    foreach(const QModelIndex &index, ui->listView->selectionModel()->selectedIndexes()) {
        QString strPid = model->itemFromIndex(index)->text();

        if (iPMREx->removePid(strPid.toUInt()) != S_OK) {
            this->showError();
        } else {
            model->removeRow(index.row());
        }
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString strPid = ui->lineEdit_2->text().trimmed();

    if (strPid.length() == 0) {
        return;
    }

    if (iPMREx->pushPid(strPid.toUInt()) != S_OK) {
        this->showError();
    } else {
        QStandardItem* item = new QStandardItem(strPid);
        QStandardItemModel *model = static_cast<QStandardItemModel*>(ui->listView->model());
        model->appendRow(item);

        ui->lineEdit_2->setText("");
    }
}
