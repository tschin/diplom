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
    connect(cylinder, SIGNAL(triggered(bool)), this, SLOT(Cylinder()));


            QAction* facet = check->addAction("Гранная протяжка");
    connect(facet, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));


            QAction* facet_combined = check->addAction("Гранная комбинированная протяжка");
    connect(facet_combined, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));


            QAction* keywey = check->addAction("Шпоночная протяжка");
    connect(keywey, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));


            QAction* slotted = check->addAction("Шлицевая протяжка");
    connect(slotted, SIGNAL(triggered(bool)), this, SLOT(TestSlot()));
    ui->menuBar->addMenu(check);
    FillTable();

   // ui->





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TestSlot()
{

}

void MainWindow::Cylinder()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::FillTable()
{
    QStringList labelsForHeader;
    labelsForHeader<<"Модель станка"<<"Тяговая сила,Н"<<"Ход ползунка, мм";
    ui->tableWidget->setHorizontalHeaderLabels(labelsForHeader);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QList<tool> toolList = GetTools();
    ui->tableWidget->setRowCount(toolList.count());
    for(int i = 0; i<toolList.count();i++)
    {
        QTableWidgetItem * model = new QTableWidgetItem();
        QTableWidgetItem * power = new QTableWidgetItem();
        QTableWidgetItem * step = new QTableWidgetItem();
        model->setText(toolList[i].model);
        power->setText(QString::number(toolList[i].power));
        step->setText(QString::number(toolList[i].step));
        ui->tableWidget->setItem(i,0,model);
        ui->tableWidget->setItem(i,1,power);
        ui->tableWidget->setItem(i,2,step);


    }
}

QList<tool> MainWindow::GetTools()
{
    QList<tool> toolList;

    tool t1={"Вертикальный","7510",102000,1400};

    tool t2={"Вертикальный","7510М",102000,1400};
    tool t3={"Вертикальный","7А510",102000,1250};
    tool t4={"Вертикальный","7520",204000,1600};
    tool t5={"Вертикальный","7А520",204000,1600};
    tool t6={"Вертикальный","7530М",306000,1800};
    tool t7={"Вертикальный","7540",408000,2000};
    tool t8={"Вертикальный","7551",714000,2000};
    tool t9={"Вертикальный","7552",1020000,2000};
    toolList.append(t1);
    toolList.append(t2);
    toolList.append(t3);
    toolList.append(t4);
    toolList.append(t5);
    toolList.append(t6);
    toolList.append(t7);
    toolList.append(t8);
    toolList.append(t9);
    return toolList;


}
