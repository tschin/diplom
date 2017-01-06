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
    connect(ui->verticalRadioButton, SIGNAL(clicked(bool)), this, SLOT(SwitchTable(bool)));
    connect(ui->horizontalRadioButton, SIGNAL(clicked(bool)), this, SLOT(SwitchTable(bool)));
    ui->horizontalTableWidget->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->radioButton_5, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));

    connect(ui->radioButton_6, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(ui->radioButton_7, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(ui->radioButton_8, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(ui->radioButton_9, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(ui->radioButton_10, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(ui->radioButton_11, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(ui->radioButton_12, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(ui->radioButton_13, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));

    listHBRadioButton.append(ui->radioButton_5);
    listHBRadioButton.append(ui->radioButton_6);
    listHBRadioButton.append(ui->radioButton_7);
    listHBRadioButton.append(ui->radioButton_8);
    listHBRadioButton.append(ui->radioButton_9);
    listHBRadioButton.append(ui->radioButton_10);
    listHBRadioButton.append(ui->radioButton_11);
    listHBRadioButton.append(ui->radioButton_12);
    listHBRadioButton.append(ui->radioButton_13);

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

    if(ui->verticalRadioButton->isChecked())
    {
        tableWidget=ui->verticalTableWidget;
        tableWidget->setVisible(true);
        ui->horizontalTableWidget->setVisible(false);

    }
    if(ui->horizontalRadioButton->isChecked())
    {
        tableWidget=ui->horizontalTableWidget;
        tableWidget->setVisible(true);
        ui->verticalTableWidget->setVisible(false);

    }
    if(tableWidget->rowCount()==0)
        FillTableTool();


}

void MainWindow::FillTableTool()
{
    QTableWidget * tableWidget;
    QList<tool> toolList;
    if(ui->verticalRadioButton->isChecked())
    {
        tableWidget=ui->verticalTableWidget;
        toolList = GetToolsCylinderVertical();
    }
    else if(ui->horizontalRadioButton->isChecked())
    {
        tableWidget=ui->horizontalTableWidget;
        toolList = GetToolsCylinderHorizontal();
    }
    else
    {
        tableWidget=ui->verticalTableWidget;
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
    QTableWidget * tableWidget = ui->materialTableWidget;
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

void MainWindow::WriteFile(QString string)
{
    QString newString = string+"\n";

    QFile fileOut(QDir::homePath()+"/fileout.txt");
    if(fileOut.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream writeStream(&fileOut);
        writeStream << newString;
        fileOut.close();
    }
}

void MainWindow::on_pushButton_clicked()
{
    int code =0;


    QString typ_stanok, model_stanok;
    int P_stanok, Lpx_stanok;
    //заготовка
    QString mat_zag;
    int cod_zag, HB_zag;
    //обработка
    bool usadka;
    QString  mat_sozh;
    int  cod_sozh;
    //отверстие
    double Ra;
    int D0, D, L, Kvalitet, HiOtkl, LowOtkl;
    //выходной текст
    QString TxtFileName; //результаты

    //ввод параметров станка

    if (ui->verticalRadioButton->isChecked()) {
        typ_stanok='вертикальный';
        model_stanok=ui->verticalTableWidget->item(ui->verticalTableWidget->currentRow(),0)->text();
        P_stanok=ui->verticalTableWidget->item(ui->verticalTableWidget->currentRow(),1)->text().toInt();
        Lpx_stanok=ui->verticalTableWidget->item(ui->verticalTableWidget->currentRow(),2)->text().toInt();
    } else if(ui->horizontalRadioButton->isChecked())
    {
        typ_stanok='горизонтальный';

        model_stanok=ui->horizontalTableWidget->item(ui->verticalTableWidget->currentRow(),0)->text();
        P_stanok=ui->horizontalTableWidget->item(ui->verticalTableWidget->currentRow(),1)->text().toInt();
        Lpx_stanok=ui->horizontalTableWidget->item(ui->verticalTableWidget->currentRow(),2)->text().toInt();
    };

    //ввод параметров заготовки
    mat_zag=ui->materialTableWidget->item(ui->materialTableWidget->currentRow(),0)->text();
    cod_zag=ui->materialTableWidget->currentRow();
    HB_zag=ui->materialSpinBox->value();
    //ввод параметров обработки
    if (ui->usadkaRadioButton->isChecked())
        usadka=true;
    else
        usadka=false;

    mat_sozh=hbString;
    cod_sozh=indexHBRadioButton;
    //ввод параметров отверстия
    D0=ui->d0SpinBox->value();
    D=ui->d_spinBox->value();
    L=ui->l_spinBox->value();
    Kvalitet=ui->kval_spinBox->value();
    HiOtkl=ui->hi_spinBox->value();
    LowOtkl=ui->low_spinBox->value();
    Ra=(double)ui->ra_spinBox->value();
    //      val(Edit_Ra.Text,Ra,code);
    //    //запуск процедуры расчёта
    //      Protyagka_Tzil(
    //        //станок
    //          typ_stanok, model_stanok, P_stanok, Lpx_stanok,
    //        //заготовка
    //          mat_zag, cod_zag, HB_zag,
    //        //обработка
    //          usadka, mat_sozh, cod_sozh,
    //        //отверстие
    //          Ra, D0, D, L, Kvalitet, HiOtkl, LowOtkl,
    //        //выходной текст
    //          TxtFileName);

}

void MainWindow::slotRadioToggled(bool)
{
    QRadioButton * rb = qobject_cast<QRadioButton*>(sender());
    if (!rb) return;
    hbString = rb->text();
    indexHBRadioButton=listHBRadioButton.indexOf(rb);
}
