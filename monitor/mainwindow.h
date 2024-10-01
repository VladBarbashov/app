#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include "tempreader.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateInfo(QDateTime dateTime, float temp);

private:
    Ui::MainWindow *ui;

    TempReader tempReader;
};


#endif // MAINWINDOW_H
