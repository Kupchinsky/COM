#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../clientexe/result_checker.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CoInitialize(NULL);

    ResultChecker::check(CoCreateInstance(LIBID_ProcessManager, NULL, CLSCTX_INPROC_SERVER,
                                          IID_IProcessMonitor, (void**) &iPM));

    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);

    QStringList lbls;
    lbls.append("Pid");
    lbls.append("Process name");
    lbls.append("Status");
    lbls.append("Time");

    ui->tableWidget->setHorizontalHeaderLabels(lbls);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidgetR->setColumnCount(2);

    QStringList lbls2;
    lbls2.append("Pid/Name");
    lbls2.append("Type");

    ui->tableWidgetR->setHorizontalHeaderLabels(lbls2);
    ui->tableWidgetR->verticalHeader()->setVisible(false);
    ui->tableWidgetR->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetR->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;

    iPM->Release();
    CoUninitialize();
}

void MainWindow::on_pushButton_2_clicked()
{
    // Pid
    if (ui->radioButton->isChecked()) {
        uint pid = ui->lineEdit->text().toUInt();

        if (iPM->registerProcessByPid(pid) != S_OK) {
            QMessageBox::warning(ui->centralWidget, "Error", "Something went wrong", QMessageBox::Ok, QMessageBox::Cancel);
        } else {
            int row = ui->tableWidgetR->rowCount();

            ui->tableWidgetR->insertRow(row);
            ui->tableWidgetR->setItem(row, 0, new QTableWidgetItem(QString::number(pid)));
            ui->tableWidgetR->setItem(row, 1, new QTableWidgetItem("Pid"));

            ui->lineEdit->clear();
        }
    } else {
        QString pName = ui->lineEdit->text();

        if (iPM->registerProcessByName((wchar_t*) pName.toStdWString().c_str()) != S_OK) {
            QMessageBox::warning(ui->centralWidget, "Error", "Something went wrong", QMessageBox::Ok, QMessageBox::Cancel);
        } else {
            int row = ui->tableWidgetR->rowCount();

            ui->tableWidgetR->insertRow(row);
            ui->tableWidgetR->setItem(row, 0, new QTableWidgetItem(pName));
            ui->tableWidgetR->setItem(row, 1, new QTableWidgetItem("Process name"));

            ui->lineEdit->clear();
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if (iPM->unregisterAllProcesses() != S_OK) {
        QMessageBox::warning(ui->centralWidget, "Error", "Something went wrong", QMessageBox::Ok, QMessageBox::Cancel);
    } else {
        ui->tableWidgetR->setRowCount(0);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QItemSelectionModel *select = ui->tableWidgetR->selectionModel();

    if (select->hasSelection()) {
        QModelIndexList modellist = select->selectedRows();

        if (modellist.size() != 0) {
            QModelIndex modelIndex = modellist.at(0);
            int row = modelIndex.row();

            QString value = ui->tableWidgetR->item(row, 0)->text();
            QString type = ui->tableWidgetR->item(row, 1)->text();

            HRESULT result;

            if (type == "Pid") {
                result = iPM->unregisterProcessByPid(value.toUInt());
            } else {
                result = iPM->unregisterProcessByName((wchar_t*)value.toStdWString().c_str());
            }

            if (result != S_OK) {
                QMessageBox::warning(ui->centralWidget, "Error", "Something went wrong", QMessageBox::Ok, QMessageBox::Cancel);
            } else {
                ui->tableWidgetR->removeRow(row);
            }
        }
    }
}
