#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
, tempReader(TempReader("/dev/ttyUSB0")) {
    connect(&tempReader, &TempReader::updateInfo, this, &MainWindow::updateInfo, Qt::QueuedConnection);
    ui->setupUi(this);
    tempReader.start();
}

MainWindow::~MainWindow() {
    tempReader.stop();
    delete ui;
}

void MainWindow::updateInfo(QDateTime dateTime, float temp) {
    ui->dateTimeEdit->setDateTime(dateTime);
    ui->tempLEdit->setText(QString::number(temp));
}
