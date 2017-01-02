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
    connect(ui->radioButton, SIGNAL(clicked(bool)), this, SLOT(SwitchTable(bool)));
    connect(ui->radioButton_2, SIGNAL(clicked(bool)), this, SLOT(SwitchTable(bool)));
    ui->tableWidget_2->setVisible(false);
    FillTableCylinderVertical();

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

void MainWindow::SwitchTable(bool)
{
    QTableWidget * tableWidget;

    if(ui->radioButton->isChecked())
    {
        tableWidget=ui->tableWidget;
        tableWidget->setVisible(true);
        ui->tableWidget_2->setVisible(false);

    }
    if(ui->radioButton_2->isChecked())
    {
        tableWidget=ui->tableWidget_2;
        tableWidget->setVisible(true);
        ui->tableWidget->setVisible(false);

    }
    if(tableWidget->rowCount()==0)
        FillTableCylinderVertical();


}

void MainWindow::FillTableCylinderVertical()
{
    QTableWidget * tableWidget;
    QList<tool> toolList;
    if(ui->radioButton->isChecked())
    {
        tableWidget=ui->tableWidget;
        toolList = GetToolsCylinderVertical();
    }
    else if(ui->radioButton_2->isChecked())
    {
        tableWidget=ui->tableWidget_2;
        toolList = GetToolsCylinderHorizontal();
    }
    else
    {
        tableWidget=ui->tableWidget;
        toolList = GetToolsCylinderVertical();
    }

    QStringList labelsForHeader;
    labelsForHeader<<"Модель станка"<<"Тяговая сила,Н"<<"Ход ползунка, мм";
    tableWidget->setColumnCount(labelsForHeader.count());
    tableWidget->setHorizontalHeaderLabels(labelsForHeader);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    tableWidget->setRowCount(toolList.count());
    for(int i = 0; i<toolList.count();i++)
    {
        QTableWidgetItem * model = new QTableWidgetItem();
        QTableWidgetItem * power = new QTableWidgetItem();
        QTableWidgetItem * step = new QTableWidgetItem();
        model->setText(toolList[i].model);
        power->setText(QString::number(toolList[i].power));
        step->setText(QString::number(toolList[i].step));
        tableWidget->setItem(i,0,model);
        tableWidget->setItem(i,1,power);
        tableWidget->setItem(i,2,step);


    }
}

void MainWindow::FillTableCylinderHorizontal()
{

}

QList<tool> MainWindow::GetToolsCylinderVertical()
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

QList<tool> MainWindow::GetToolsCylinderHorizontal()
{
    QList<tool> toolList;

    tool t1={"Горизонтальный","7705",51000,600};
    tool t2={"Горизонтальный","7705А",51000,600};
    tool t3={"Горизонтальный","7705Б",51000,600};
    tool t4={"Горизонтальный","7А705В",51000,800};
    tool t5={"Горизонтальный","7710",102000,1350};
    tool t6={"Горизонтальный","7А710",102000,1200};
//    tool t7={"Горизонтальный","7510",51000,600};


    tool t8={"Горизонтальный","7Б710",102000,1000};

    tool t9={"Горизонтальный","7710В",102000,1000};

    tool t10={"Горизонтальный","7А710Д",102000,1000};

    tool t11={"Горизонтальный","7720",204000,1600};

    tool t12={"Горизонтальный","7Б720",204000,1250};
    tool t13={"Горизонтальный","7720В",204000,1250};

    tool t14={"Горизонтальный","7А720Д",204000,1250};







    toolList.append(t1);
    toolList.append(t2);
    toolList.append(t3);
    toolList.append(t4);
    toolList.append(t5);
    toolList.append(t6);
    toolList.append(t8);
    toolList.append(t9);
    toolList.append(t10);
    toolList.append(t11);
    toolList.append(t12);
    toolList.append(t13);
    toolList.append(t14);
    return toolList;
}
