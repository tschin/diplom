#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"Hello World!";
    qDebug()<<"Ho-ho-ho";

}

MainWindow::~MainWindow()
{
    delete ui;
}
