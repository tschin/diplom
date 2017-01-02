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
    FillTableTool();
    FillTableMaterial();

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
        FillTableTool();


}

void MainWindow::FillTableTool()
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

void MainWindow::FillTableMaterial()
{
    QTableWidget * tableWidget = ui->tableWidget_3;
    QList<material> materialList=GetMaterial();

    QStringList labelsForHeader;
    labelsForHeader<<"Группа материала"<<"Марка материала";
    tableWidget->setColumnCount(labelsForHeader.count());
    tableWidget->setHorizontalHeaderLabels(labelsForHeader);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    tableWidget->setRowCount(materialList.count());
    for(int i = 0; i<materialList.count();i++)
    {
        QTableWidgetItem * group = new QTableWidgetItem();
        QTableWidgetItem * mark = new QTableWidgetItem();
        group->setText(materialList[i].group);
        mark->setText(materialList[i].mark);
        tableWidget->setItem(i,0,group);
        tableWidget->setItem(i,1,mark);
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

QList<material> MainWindow::GetMaterial()
{
    QList<material> listMaterials;
    QStringList first;
    QStringList second;

    first<<"сталь автоматная конструкционная"<<"сталь углеродистая конструкционная качественная"<<"сталь углеродистая конструкционная качественная"
        <<"сталь углеродистая конструкционная качественная"<<"сталь легированная конструкционная хромистая"<<"сталь легированная конструкционная хромистая"<<
            "сталь легированная конструкционная хромистая"<<"сталь легированная конструкционная марганцовистая"<<"сталь легированная конструкционная марганцовистая"<<
        "сталь легированная конструкционная марганцовистая"<<"сталь легированная конструкционная хромисто-марганцевая"<<"сталь легированная конструкционная хромисто-марганцевая"
       <<"сталь легированная конструкционная хромисто-марганцевая"<<"сталь легированная конструкционная хромокремнистая"<<"сталь легированная конструкционная хромомолибденовая"
        <<"сталь легированная конструкционная хромомолибденовая"<<"сталь легированная конструкционная хромованадиевая"
        <<"сталь легированная конструкционная хромованадиевая"<<"сталь легированная конструкционная хромоникелевая и с бором"
        <<"сталь легированная конструкционная хромоникелевая и с бором"<<"сталь легированная конструкционная хромоникелевая и с бором"
        <<"сталь легированная конструкционная хромоникелевая и с бором"<<"сталь легированная конструкционная хромокремнемарганцевая"
       <<"cталь легированная конструкционная хромомарганцовоникелевая и с бором и титаном"<<"сталь легированная конструкционная хромомарганцовоникелевая и с бором и титаном"
        <<"сталь легированная конструкционная хромомарганцовоникелевая и с бором и титаном"<<"сталь легированная конструкционная хромоникельмолибденовая"
        <<"сталь легированная конструкционная хромоникельмолибденовая"<<"сталь легированная конструкционная хромоникельмолибденовая"
        <<"сталь легированная конструкционная хромоникельмолибденовая"<<"сталь легированная конструкционная хромоникельванадиевая"
        <<"сталь легированная конструкционная хромоалюминиевая и с молибденом"<<"сталь шарикоподшипниковая"<<"сталь быстрорежущая"<<"чугун серый"<<"чугун серый"
       <<"чугун ковкий (ферритный)"<<"чугун ковкий"<<"чугун антифрикционный ковкий"<<"чугун антифрикционный серый"<<"бронза безоловянная"<<"бронза безоловянная"
        <<"бронза безоловянная"<<"бронза безоловянная"<<"бронза оловянная"<<"бронза оловянная"<<"бронза оловянная"<<"бронза оловянная"<<"бронза оловянная"<<"латунь"
        <<"латунь"<<"латунь"<<"латунь"<<"латунь"<<"алюминиевый сплав"<<"алюминиевый сплав"<<"алюминиевый сплав"<<"алюминиевый сплав"<<"алюминиевый сплав"<<"медь";
    second<<"А12, А20, А30"<<"10, 15, 20, 25"<<"30, 35, 40, 50"<<"60, 70, 80"<<"15Х, 15ХА, 20Х, 30Х"<<"35Х, 30ХРА, 38ХА"<<"40Х, 45Х, 50Х"<<"15Г, 20Г, 25Г, 30Г, 33Г"
        <<"40Г, 45Г, 35Г2, 45Г2, 50Г2"<<"60Г, 65Г, 70Г"<<"18ХГ, 20ХГР"<<"18ХГТ"<<"30ХГТ, 35ХГФ, 40ХГТР"<<"33ХС, 38ХС, 40ХС"<<"15ХМ"<<"30ХМА, 35ХМ"<<"15ХФ"<<"40ХФА"
        <<"12ХН2, 12ХН3А, 12Х2Н4А"<<"20ХН, 20ХНР, 20ХН3А"<<"20Х2Н4А, 30ХН3А"<<"40ХН 45ХН, 50ХН"<<"20ХГСА, 25ХГСА, 30ХГС"<<"20ХГНР"<<"38ХГН"<<"15ХГН2ТА"<<"25Х2Н4МА, 18Х2Н4МА"
        <<"40Х2Н2МА, 38Х2Н2МА"<<"14Х2Н, 3МА, 20ХН2М"<<"40ХН2МА"<<"20ХН4ФА"<<"38Х2Ю, 38Х2МЮА"<<"ШХ15"<<"Р18, Р9, Р6АМ5"<<"СЧ10, СЧ15, СЧ18, СЧ20, СЧ21"<<"СЧ24, СЧ25, СЧЗО, СЧ35, СЧ40"
        <<"КЧ 30-6, КЧ 33-8, КЧ 35-10, КЧ 37-12"<<"КЧ 40-3, КЧ 45-6, КЧ 50-4"<<"АЧК-1, АЧК-2"<<"АЧС-1, АЧС-2, АЧС-3"<<"БрА5, БрА7, БрАЖ9-4"<<"БрАЖ9-4, БрАЖНЮ-4-4"
        <<"БрАЖМц 10-3-1,5, БрАМц9-2"<<"БрКМц3-1, БрКН1-3"<<"БрОЦС5-5-5, БрОЦС3-12-5"<<"БрОЦСН3-7-5-1, БрОЦС6-6-3"<<"БрОЦС4-4-17, БрОЦС3,5-6-5"<<"БрОЦС4-4-4-2,5, БрОФ6,5-0,15"
        <<"БрОФ4-0,25, БрОФ6,5-1,5"<<"ЛЦ40С, ЛЦ40Сд, ЛЦ40Мц 1,5"<<"ЛЦ40МцЗЖ, ЛЦ38Мц2С2"<<"ЛЦЗОАЗ, ЛЦ25С2"<<"ЛЦ23А6ЖЗМц2, ЛЦ16КЗ, Л63"<<"ЛС59-1, ЛМц58-2, ЛАЖ60-1-1, ЛС62-1"
        <<"АЛ1, АЛ2, АЛ3, АЛ4, АЛ5"<<"АЛ6, АЛ 7, АЛ8, АЛ9, АЛ 10"<<"АЛ19, АЛ20, АЛ21, Д1, Д6"<<"Д16, Б95, АВ, АК2, АК4, АК6"<<"АК8, АД, АД1, АМг2, АМц, Амг3"<<"М1, М2, М3";
    material m;
    for(int i=0; i<first.count();i++)
    {
        m.group=first[i];
        m.mark = second[i];
        listMaterials.append(m);
    }
    return listMaterials;

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
