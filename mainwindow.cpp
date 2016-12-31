#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu * check = new QMenu("Выбор и расчет протяжки",ui->menuBar);

            QAction* cylinder = check->addAction("Цилиндрическая протяжка");
    connect(cylinder, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));


            QAction* facet = check->addAction("Гранная протяжка");
    connect(facet, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));


            QAction* facet_combined = check->addAction("Гранная комбинированная протяжка");
    connect(facet_combined, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));


            QAction* keywey = check->addAction("Шпоночная протяжка");
    connect(keywey, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));


            QAction* slotted = check->addAction("Шлицевая протяжка");
    connect(slotted, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));
    ui->menuBar->addMenu(check);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TestSlot()
{

}
