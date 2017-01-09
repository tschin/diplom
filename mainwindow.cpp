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

void MainWindow::WriteFile(QString nameFile, QString string)
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

void MainWindow::Pril_UdNagruzka(double Sz, int gamma_, int cod_zag__, int HB_zag__, int cod_sozh__, double Ra__, double *q)
{

    double q_, Kpm,Kpo,Kpk;

    q_= *q;


      if ( Sz>=0.4)  {
        if (gamma_>=20)  q_=751;
        if (gamma_<20) q_=791;
        if (gamma_<15) q_=846;
      }
      if (( Sz>=0.39) &&(  Sz<0.4))  {
        if (gamma_>=20) q_=733;
        if (gamma_<20) q_=771;
        if (gamma_<15) q_=825;
      }
      if ((Sz>=0.38) &&(  Sz<0.39))  {
         if (gamma_>=20) q_=714;
         if (gamma_<20) q_=752;
         if (gamma_<15) q_=805;
      }
      if ((  Sz>=0.37) &&(  Sz<0.38))  {
         if (gamma_>=20) q_=696;
         if (gamma_<20) q_=733;
         if (gamma_<15) q_=784;
      }
      if ((  Sz>=0.36) &&(  Sz<0.37))  {
         if (gamma_>=20) q_=678;
         if (gamma_<20) q_=713;
         if (gamma_<15) q_=763;
      }
      if ((  Sz>=0.35) &&(  Sz<0.36)) {
         if (gamma_>=20) q_=659;
         if (gamma_<20) q_=694;
         if (gamma_<15) q_=743;
      }
      if ((  Sz>=0.34) &&(  Sz<0.35)) {
         if (gamma_>=20) q_=641;
         if (gamma_<20) q_=675;
         if (gamma_<15) q_=722;
      }
      if ((  Sz>=0.33) &&(  Sz<0.34)) {
         if (gamma_>=20) q_=623;
         if (gamma_<20) q_=655;
         if (gamma_<15) q_=708;
      }
      if ((  Sz>=0.32) &&(  Sz<0.33)) {
         if (gamma_>=20) q_=604;
         if (gamma_<20) q_=628;
         if (gamma_<15) q_=687;
      }
      if ((  Sz>=0.31) &&(  Sz<0.32)) {
         if (gamma_>=20) q_=586;
         if (gamma_<20) q_=617;
         if (gamma_<15) q_=666;
      }
      if ((  Sz>=0.30) &&(  Sz<0.31)) {
         if (gamma_>=20) q_=567;
         if (gamma_<20) q_=597;
         if (gamma_<15) q_=645;
      }
      if ((  Sz>=0.29) &&(  Sz<0.30)) {
         if (gamma_>=20) q_=549;
         if (gamma_<20) q_=579;
         if (gamma_<15) q_=624;
      }
      if ((  Sz>=0.28) &&(  Sz<0.29)) {
         if (gamma_>=20) q_=531;
         if (gamma_<20) q_=559;
         if (gamma_<15) q_=604;
      }
      if ((  Sz>=0.27) &&(  Sz<0.28)) {
         if (gamma_>=20) q_=512;
         if (gamma_<20) q_=539;
         if (gamma_<15) q_=583;
      }
      if ((  Sz>=0.26) &&(  Sz<0.27)) {
         if (gamma_>=20) q_=494;
         if (gamma_<20) q_=520;
         if (gamma_<15) q_=562;
      }
      if ((  Sz>=0.25) &&(  Sz<0.26)) {
         if (gamma_>=20) q_=471;
         if (gamma_<20) q_=501;
         if (gamma_<15) q_=541;
      }
      if ((  Sz>=0.24) &&(  Sz<0.25)) {
         if (gamma_>=20) q_=453;
         if (gamma_<20) q_=481;
         if (gamma_<15) q_=525;
      }
      if ((  Sz>=0.23) &&(  Sz<0.24)) {
         if (gamma_>=20) q_=434;
         if (gamma_<20) q_=462;
         if (gamma_<15) q_=504;
      }
      if ((  Sz>=0.22) &&(  Sz<0.23)) {
         if (gamma_>=20) q_=416;
         if (gamma_<20) q_=443;
         if (gamma_<15) q_=483;
      }
      if ((  Sz>=0.21) &&(  Sz<0.22)) {
         if (gamma_>=20) q_=398;
         if (gamma_<20) q_=423;
         if (gamma_<15) q_=462;
      }
      if ((  Sz>=0.20) &&(  Sz<0.21)) {
         if (gamma_>=20) q_=380;
         if (gamma_<20) q_=404;
         if (gamma_<15) q_=433;
      }
      if ((  Sz>=0.19) &&(  Sz<0.20)) {
         if (gamma_>=20) q_=362;
         if (gamma_<20) q_=385;
         if (gamma_<15) q_=419;
      }
      if ((  Sz>=0.18) &&(  Sz<0.19)) {
         if (gamma_>=20) q_=343;
         if (gamma_<20) q_=365;
         if (gamma_<15) q_=402;
      }
      if ((  Sz>=0.17) &&(  Sz<0.18)) {
         if (gamma_>=20) q_=325;
         if (gamma_<20) q_=381;
         if (gamma_<15) q_=446;
      }
      if ((  Sz>=0.16) &&(  Sz<0.17)) {
         if (gamma_>=20) q_=304;
         if (gamma_<20) q_=327;
         if (gamma_<15) q_=360;
      }
      if ((  Sz>=0.15) &&(  Sz<0.16)) {
         if (gamma_>=20) q_=286;
         if (gamma_<20) q_=312;
         if (gamma_<15) q_=338;
      }
      if ((  Sz>=0.14) &&(  Sz<0.15)) {
         if (gamma_>=20) q_=268;
         if (gamma_<20) q_=288;
         if (gamma_<15) q_=320;
      }
      if ((  Sz>=0.13) &&(  Sz<0.14)) {
         if (gamma_>=20) q_=250;
         if (gamma_<20) q_=269;
         if (gamma_<15) q_=298;
      }
      if ((  Sz>=0.12) &&(  Sz<0.13)) {
         if (gamma_>=20) q_=232;
         if (gamma_<20) q_=249;
         if (gamma_<15) q_=277;
      }
      if ((  Sz>=0.11) &&(  Sz<0.12)) {
         if (gamma_>=20) q_=212;
         if (gamma_<20) q_=230;
         if (gamma_<15) q_=258;
      }
      if ((  Sz>=0.10) &&(  Sz<0.11)) {
         if (gamma_>=20) q_=194;
         if (gamma_<20) q_=212;
         if (gamma_<15) q_=236;
      }
      if ((  Sz>=0.09) &&(  Sz<0.10)) {
         if (gamma_>=20) q_=176;
         if (gamma_<20) q_=191;
         if (gamma_<15) q_=216;
      }
      if ((  Sz>=0.08) &&(  Sz<0.09)) {
         if (gamma_>=20) q_=157;
         if (gamma_<20) q_=172;
         if (gamma_<15) q_=195;
      }
      if ((  Sz>=0.07) &&(  Sz<0.08)) {
         if (gamma_>=20) q_=139;
         if (gamma_<20) q_=153;
         if (gamma_<15) q_=174;
      }
      if ((  Sz>=0.06) &&(  Sz<0.07)) {
         if (gamma_>=20) q_=121;
         if (gamma_<20) q_=134;
         if (gamma_<15) q_=153;
      }
      if ((  Sz>=0.05) &&(  Sz<0.06)) {
         if (gamma_>=20) q_=103;
         if (gamma_<20) q_=114;
         if (gamma_<15) q_=132;
      }
      if ((  Sz>=0.04) &&(  Sz<0.05)) {
         if (gamma_>=20) q_=84;
         if (gamma_<20) q_=95;
         if (gamma_<15) q_=112;
      }
      if ((  Sz>=0.03) &&(  Sz<0.04)) {
         if (gamma_>=20) q_=67;
         if (gamma_<20) q_=76;
         if (gamma_<15) q_=91;
      }
      if ((  Sz>=0.02) &&(  Sz<0.03)) {
         if (gamma_>=20) q_=48;
         if (gamma_<20) q_=56;
         if (gamma_<15) q_=70;
      }
      if ((  Sz<0.02)) {
         if (gamma_>=20) q_=30;
         if (gamma_<20) q_=37;
         if (gamma_<15) q_=48;
      }
      Kpm=1.0;


      if(cod_zag__>=1 && cod_zag__<=4)
      {
          if (HB_zag__>336) Kpm=1.4;
          if (HB_zag__<=336) Kpm=1.3;
          if (HB_zag__<=229) Kpm=1.0;

      }
      if(cod_zag__>=5 && cod_zag__<=40)
      {
          if (HB_zag__<229) Kpm=0.5;
          if (HB_zag__>=229) Kpm=0.7;

      }


      if(cod_zag__>=41 && cod_zag__<=60)
          Kpm=0.4;


      Kpo=1.0;
      if(cod_zag__ >=1 && cod_zag__ <=34)

      {
          if (cod_sozh__==0) Kpo=1.3;
          if (cod_sozh__==1) Kpo=1.0;
          if (cod_sozh__==2) Kpo=0.8;
          if (cod_sozh__==3) Kpo=1.1;
          if (cod_sozh__==4) Kpo=1.1;
          if (cod_sozh__==5) Kpo=1.1;
          if (cod_sozh__==6) Kpo=1.0;
          if (cod_sozh__==7) Kpo=1.0;
          if (cod_sozh__==8) Kpo=1.0;
        }
        if(cod_zag__ >=35 && cod_zag__ <=60){
          if (cod_sozh__==0) Kpo=1.0;
            else Kpo=0.8;
        }

      Kpk=1.2;
      if (Ra__<=20) Kpk=1.1;
      if (Ra__<=2.5) Kpk=1.0;
      double result = q_*Kpm*Kpo*Kpk;
      q= &result ;

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
    ////Val(Edit_Ra.Text,Ra,code);
    //запуск процедуры расчёта
    Protyagka_Tzil(
                //станок
                typ_stanok, model_stanok, P_stanok, Lpx_stanok,
                //заготовка
                mat_zag, cod_zag, HB_zag,
                //обработка
                usadka, mat_sozh, cod_sozh,
                //отверстие
                Ra, D0, D, L, Kvalitet, HiOtkl, LowOtkl,
                //выходной текст
                TxtFileName);

}

void MainWindow::slotRadioToggled(bool)
{
     QRadioButton * rb =  qobject_cast<QRadioButton*>(sender());
    if (!rb) return;
    hbString = rb->text();
    indexHBRadioButton=listHBRadioButton.indexOf(rb);
}

void MainWindow::Protyagka_Tzil(
QString typ_stanok_,  QString model_stanok_, int P_stanok_, int Lpx_stanok_,  QString mat_zag_, int cod_zag_, int HB_zag_,
bool usadka_,  QString mat_sozh_, int cod_sozh_, double Ra_, int D0_, int D_, int L_, int Kvalitet_, int HiOtkl_, int LowOtkl_,  QString nameFile
)
{
  QString F;
 int n, i, j, g, code, type_xvostovik, gamma_rezhzub, Zper, Zkal,
  gamma_kalzub, Zmax_o, Zmax_g, var_opt_o, shema, nk, komplekt,komplekt1,komplekt2;
  QString temp,temp1,temp2,temp3,temp4,temp5, temp6, forma_rezhzub, forma_kalzub;
 double Lnp_o, Lnp_g, Ldop_d, Ldop_st_o, Ldop_st_g, l1,lp_o,lp_g,lk_o,lk_g,lz, dx,Fx, Px,P1_o,P1_g,Pp_o,Pp_g, shag_zub, Zmax_zub,b_o,h_kan, Trezh_o, Trezh_g, Tkal, Dzat_o, Dzat_g;
 double tp_o, tp_g, tk_o, tk_g, K_o,K_g, Szk_o,Szk_g, Sz, q;
 double hkp_o,rsp_o,bp_o,Rdp_o,Fkp_o;
 double hkp_g,rsp_g,bp_g,Rdp_g,Fkp_g;
 double hkk_o,rsk_o,bk_o,Rdk_o,Fkk_o;
 double hkk_g,rsk_g,bk_g,Rdk_g,Fkk_g;
 double hkk,rsk,bk,Rdk,Fkk;
   QVariant Szk;
  bool Error_o, Error_g;
 double dzp_o[41][1001], Perimetr_o[41][1001], P_tek_o[41][1001], P_all_o[41][1001];
 double Szp_o[41], q_o[41];
 double  dzp_g[6][41][1001], Perimetr_g[6][41][1001], P_tek_g[6][41][1001], P_all_g[6][41][1001];
 double  Szp_g[6][41], q_g[6][41];
 double A,Aper_o, Aper_g, Totv, Tizg, delta, Dmax, Dkal, max, min;
 int  Zp_o[41];
 int  Zp_g[6][41], kol_grupp[6][41];
 int  var_opt_g[6];
 int Zk_o, Zk_g;
 double d,b_g,h_vik,lambda_n,lambda_vik,l_n,l_vik,a_vik,R_vik,R_krug;
 int n_vik;
 double d_per,b_g_per,h_vik_per,lambda_n_per,lambda_vik_per,l_n_per,l_vik_per,a_vik_per,
  R_vik_per,R_krug_per;
 int  n_vik_per;

 //int  n_vik_per;

 //создание файла данных
   QString TxtFileName_="Протяжка цилиндрическая.txt";
   F=TxtFileName_;

 //вывод исходных данных
   WriteFile(F, "ИСХОДНЫЕ ДАННЫЕ ДЛЯ ПРОЕКТИРОВАНИЯ ЦИЛИНДРИЧЕСКОЙ ПРОТЯЖКИ");
   WriteFile(F, "");
   WriteFile(F, "Диаметр предварительно обработанного отверстия: D0= "+QString::number(D0_)+" мм");
   WriteFile(F, "Диаметр отверстия, получаемого протягиванием: D= "+QString::number(D_)+" мм"+" (+"+QString::number(HiOtkl_)+"; -"+QString::number(LowOtkl_)+" мкм)");
   WriteFile(F, "Длина отверстия, получаемого протягиванием: L= "+QString::number(L_)+" мм");

   WriteFile(F, "Квалитет отверстия: "+QString::number(Kvalitet_)+";  шероховатость отверстия: Ra= "+temp+" мкм");
   WriteFile(F, "Материал заготовки: "+mat_zag_+";  твёрдость НВ= "+QString::number(HB_zag_));
   WriteFile(F, "Тип протяжного станка: "+typ_stanok_+";  модель станка: "+model_stanok_);
   WriteFile(F, "Номинальная тяговая сила протяжного станка: Pc= "+QString::number(P_stanok_)+" Н");
   WriteFile(F, "Максимальная длина хода ползуна протяжного станка: Lpx= "+QString::number(Lpx_stanok_)+" мм");

   if (usadka_)
       temp="усадкой";
   else
       temp="разбиением";

   WriteFile(F, "Процесс резания сопровождается: "+temp+" отверстия");
   WriteFile(F, "Использование СОЖ: "+mat_sozh_);
   WriteFile(F, "");
 //начало расчёта
   WriteFile(F, "");
   WriteFile(F, "РАССЧИТАННЫЕ ПАРАМЕТРЫ ЦИЛИНДРИЧЕСКОЙ ПРОТЯЖКИ");
   WriteFile(F, "");

   ////Pril_Hvostovik(D0_, type_xvostovik, dx, Fx);

   l1=280+L_;

   //Pril_Zadnapr(D_, lz);

  ////str(dx:4:1,temp);
   WriteFile(F, "Выбираем хвостовик "+QString::number(type_xvostovik)+" типа с диаметром d1= "+temp+" мм (см. приложение)");
   //str(l1:5:1,temp);
   WriteFile(F, "Расстояние от торца хвостовика до первого зуба: l1= "+temp+" мм");
   //str(Fx:5:1,temp);
   WriteFile(F, "Площадь сечения хвостовика, определяющая его прочность: Fx= "+temp+" мм^2");
 //выбор материала протяжки
 if (D0_<=14)
 {
   Px=Fx*250; //для хвостовика из констр. стали
   if (Px>0.8*P_stanok_)
     WriteFile(F, "Материал хвостовика: сталь 40X по ГОСТ 4543-71;  рабочей части: сталь Р18 по ГОСТ 19265-73");
   else {
     WriteFile(F, "Изготавливаем цельную протяжку из быстрорежущей стали Р18 по ГОСТ 19265-73");
     Px=Fx*300;
   }
 }
 else {
   Px=Fx*250; //для хвостовика из констр. стали
   WriteFile(F, "Материал хвостовика: сталь 40X по ГОСТ 4543-71;  рабочей части: сталь Р18 по ГОСТ 19265-73");
 };
 //выбор углов и формы зубьев
   //Pril_Ugol(cod_zag_, HB_zag_, forma_rezhzub, gamma_rezhzub, forma_kalzub, gamma_kalzub);
 //расчёт допусков и усадки (разбиения)
   A=D_-D0_;
   Totv=0.001*(double)(HiOtkl_-LowOtkl_);
   if (Totv<=0.025) delta=0;
   if ((Totv>0.025) && (Totv<0.03)) delta=0.002;
   if ((Totv>=0.03)&&(Totv<0.035)) delta=0.004;
   if ((Totv>=0.035)&&(Totv<0.05)) delta=0.005;
   if ((Totv>=0.05)&&(Totv<0.1)) delta=0.01;
   if ((Totv>=0.1)&&(Totv<0.17)) delta=0.02;
   if ((Totv>=0.17)&&(Totv<0.29)) delta=0.03;
   if ((Totv>=0.29)&&(Totv<=0.34)) delta=0.04;
   if (Totv>0.34) delta=0.05;
   Dmax=D_+0.001*HiOtkl_;
   Tizg=Totv/5;
   if (!usadka_) Dkal=Dmax-2*delta;
   else Dkal=Dmax+2*delta;
 //
 //расчёт зубьев по одинарной схеме резания
 //
   shag_zub=1.7*sqrt(L_);
  Pril_Kanavka(shag_zub, &tp_o,&hkp_o,&rsp_o,&bp_o,&Rdp_o,&Fkp_o);
   P1_o=0.25*3.14*400*pow((D0_-2*hkp_o),2);
   if ((Px<=P1_o)&&(Px<=0.8*P_stanok_)) Pp_o=Px;
   if ((P1_o<=Px)&&(P1_o<=0.8*P_stanok_)) Pp_o=P1_o;
   if ((0.8*P_stanok_<=P1_o)&&(0.8*P_stanok_<=Px)) Pp_o=0.8*P_stanok_;
   Zmax_zub=int(L_/tp_o+1);
  ////str(Zmax_zub:3:0,temp);
   Zmax_o=temp.toInt();
   if ((cod_zag_==35)||(cod_zag_==36)||(cod_zag_==37)||(cod_zag_==38)
    ||(cod_zag_=39)||(cod_zag_=40)) K_o=2.5;
   else K_o=3.5;
   Szk=Fkp_o/(K_o*L_);
  ////str(Szk:2:2, temp);
   //Val(temp, Szk_o, code);
 //расчёт вариантов диаметров режущих зубьев
   for (int i=1; i<=40; i++) {
     Szp_o[i]=0;
     q_o[i]=0;
     for (int j=1; j<=1000; j++){
       dzp_o[i][j]=0;
       Perimetr_o[i][j]=0;
       P_tek_o[i][j]=0;
       P_all_o[i][j]=0;
     }
   }
   Szp_o[1]=0.01;
   for (int i=2; i<=40; i++)
        Szp_o[i]=Szp_o[i-1]+0.01;
   for (int i=1; i<=40; i++){
     Sz=Szp_o[i];

    Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

     q_o[i]=q*1.2;
     dzp_o[i][1]=D0_;
     Perimetr_o[i][1]=3.1416*dzp_o[i][1];
     P_tek_o[i][1]=q_o[i]*Perimetr_o[i][1];
     P_all_o[i][1]=P_tek_o[i][1];
     int j=1;
     while (dzp_o[i][j]<Dkal-2*Szp_o[i]) {
         j=j+1;
         dzp_o[i][j]=dzp_o[i][j-1]+2*Szp_o[i];
                 Perimetr_o[i][j]=3.1416*dzp_o[i][j];
                 P_tek_o[i][j]=Perimetr_o[i][j]*q_o[i];
                 if (j<=Zmax_o)
                 P_all_o[i][j]=P_all_o[i][j-1]+P_tek_o[i][j];
                 else
                 P_all_o[i][j]=P_all_o[i][j-1]+P_tek_o[i][j]-P_tek_o[i][j-Zmax_o];
                 Zp_o[i]=j;
    }
  }
   i=1;  var_opt_o=0;
   while (Szp_o[i]<=Szk_o) {
     max=P_all_o[i][1];
     for (int j=2; j<=Zp_o[i]; j++) {
       if (P_all_o[i][j]>=max)
           max=P_all_o[i][j];
    }
     if (max<=Pp_o)
     var_opt_o=i;
     i=i+1;
  }
 //расчёт стружкоделительных канавок
   Sz=Szp_o[var_opt_o];
   //Pril_Struzhka(Sz,hkp_o,D_, b_o);
   nk=round(3.1416*D_/b_o);
   if (nk %2!=0)
                   nk=nk+1;
   h_kan=5*Sz;
 //расчёт переходных и калибрующих зубьев
   //Aper_o=(Dkal-dzp_o[var_opt_o][Zp_o[var_opt_o]])/2;
   Zper=2; Zkal=4;
   if (Ra_<=20){Zper=3; Zkal=5;}
   if (Ra_<=2.5){Zper=5; Zkal=6;}
   if (Ra_<=1.25){Zper=6; Zkal=7;}
   Sz=Aper_o/Zper;
   Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);
   q=q*1.2;
   for (int i=1; i<=Zper; i++) {
     dzp_o[var_opt_o][Zp_o[var_opt_o]+i]=dzp_o[var_opt_o][Zp_o[var_opt_o]+i-1]+2*Aper_o/Zper;
     Perimetr_o[var_opt_o][Zp_o[var_opt_o]+i]=3.1416*dzp_o[var_opt_o][Zp_o[var_opt_o]+i];
     P_tek_o[var_opt_o][Zp_o[var_opt_o]+i]=Perimetr_o[var_opt_o][Zp_o[var_opt_o]+i]*q;
  }
   lp_o=tp_o*(Zp_o[var_opt_o]+Zper-1);
   Trezh_o=0.3*Szp_o[var_opt_o];
   if (Trezh_o>0.02) Trezh_o=0.02;
   Sz=0.01;

  Pril_UdNagruzka(Sz,gamma_kalzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

   q=q*1.2;
   for (int i=1; i<=Zkal; i++) {
     dzp_o[var_opt_o][Zp_o[var_opt_o]+i+Zper]=dzp_o[var_opt_o][Zp_o[var_opt_o]+i-1+Zper];
     Perimetr_o[var_opt_o][Zp_o[var_opt_o]+i+Zper]=3.1416*dzp_o[var_opt_o][Zp_o[var_opt_o]+i+Zper];
     P_tek_o[var_opt_o][Zp_o[var_opt_o]+i+Zper]=q*Perimetr_o[var_opt_o][Zp_o[var_opt_o]+i+Zper];
  }

   shag_zub=tp_o*2/3;

  Pril_Kanavka(shag_zub, &tk_o,&hkk_o,&rsk_o,&bk_o,&Rdk_o,&Fkk_o);

   lk_o=tk_o*Zkal;
   Lnp_o=l1+lp_o+lk_o+lz;
   Ldop_d=40*D0_;
   Ldop_st_o=lp_o+lk_o+lz+L_;
   Dzat_o=(D0_-hkp_o)*sin(qDegreesToRadians((double)45))/sin(qDegreesToRadians((double)gamma_rezhzub));
 //
 //расчёт зубьев по групповой схеме резания
 //
   shag_zub=2*sqrt(L_);

  Pril_Kanavka(shag_zub, &tp_g,&hkp_g,&rsp_g,&bp_g,&Rdp_g,&Fkp_g);

   P1_g=0.25*3.14*400*pow((D0_-2*hkp_g),2);
   if ((Px<=P1_g)&&(Px<=0.8*P_stanok_)) Pp_g=Px;
   if ((P1_g<=Px)&&(P1_g<=0.8*P_stanok_)) Pp_g=P1_g;
   if ((0.8*P_stanok_<=P1_g)&&(0.8*P_stanok_<=Px)) Pp_g=0.8*P_stanok_;
   Zmax_zub=int(L_/tp_g+1);
   //str(Zmax_zub:3:0,temp);
   Zmax_g=temp.toInt();
   if ((cod_zag_=35)||(cod_zag_=36)||(cod_zag_=37)||(cod_zag_=38)
    ||(cod_zag_=39)||(cod_zag_=40)) K_g=2;
             else K_g=3;
   Szk=Fkp_g/(K_g*L_);
  ////str(Szk:2:2, temp);
  // //Val(temp, Szk_g, code);
 //расчёт вариантов диаметров режущих зубьев
   for (int n=2; n<=5; n++) {
     for (int i=1; i<=40; i++) {
       Szp_g[n][i]=0;
         q_g[n][i]=0;
       kol_grupp[n][i]=0;
       for (int j=1; j<=1000; j++) {
         dzp_g[n][i][j]=0;
         Perimetr_g[n][i][j]=0;
         P_tek_g[n][i][j]=0;
         P_all_g[n][i][j]=0;
      }
    }
  }
 //расчёт при числе зубьев в группе = 2
   n=2;
     Szp_g[n][1]=0.01;
     for (int i=2; i<=40;i++)
                 Szp_g[n][i]=Szp_g[n][i-1]+0.01;
     for (int i=1; i<=40; i++) {
       dzp_g[n][i][1]=D0_;
       Perimetr_g[n][i][1]=3.1416*dzp_g[n][i][1];

       Sz=Szp_g[n][1];

       Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

       P_tek_g[n][i][1]=q*Perimetr_g[n][i][1];
       P_all_g[n][i][1]=P_tek_g[n][i][1];
       Sz=Szp_g[n][i];

       Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

         q_g[n][i]=q;
       j=1; kol_grupp[n][i]=0;
       while (dzp_g[n][i][j]<Dkal-2*Szp_g[n][i]) {
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1]+2*Szp_g[n][i];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           if (Szp_g[n][i]<=0.04) dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.01;
                   else dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.02;
           Sz=Szp_g[n][i]-0.01;
           Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q;
           if (j<=Zmax_g)
                   P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
           kol_grupp[n][i]=kol_grupp[n][i]+1;
      }
       Zp_g[n][i]=kol_grupp[n][i]*n+1;
    }
 //расчёт при числе зубьев в группе = 3
   n=3;
     Szp_g[n][1]=0.01;
     for (int i=2; i<=40; i++) Szp_g[n][i]=Szp_g[n][i-1]+0.01;
     for (int i=1; i<=40;i++) {
       dzp_g[n][i][1]=D0_;
       Perimetr_g[n][i][1]=3.1416*dzp_g[n][i][1];
       Sz=Szp_g[n][1];

       Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

       P_tek_g[n][i][1]=q*Perimetr_g[n][i][1];

       P_all_g[n][i][1]=P_tek_g[n][i][1];
       Sz=Szp_g[n][i];

       Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

         q_g[n][i]=q;
       j=1; kol_grupp[n][i]=0;
       while (dzp_g[n][i][j]<Dkal-2*Szp_g[n][i]) {
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1]+2*Szp_g[n][i];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           if (Szp_g[n][i]<=0.04) dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.01;
                   else dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.02;
           Sz=Szp_g[n][i]-0.01;
           Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_,&q);
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q;
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
           kol_grupp[n][i]=kol_grupp[n][i]+1;
      }
       Zp_g[n][i]=kol_grupp[n][i]*n+1;
    }
 //расчёт при числе зубьев в группе = 4
   n=4;
     Szp_g[n][1]=0.01;
     for (int i=2; i<=40; i++) Szp_g[n][i]=Szp_g[n][i-1]+0.01;
     for (int i=1; i<=40; i++) {
       dzp_g[n][i][1]=D0_;
       Perimetr_g[n][i][1]=3.1416*dzp_g[n][i][1];
       Sz=Szp_g[n][1];

       Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

       P_tek_g[n][i][1]=q*Perimetr_g[n][i][1];
       P_all_g[n][i][1]=P_tek_g[n][i][1];
       Sz=Szp_g[n][i];
      Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);
         q_g[n][i]=q;
       j=1; kol_grupp[n][i]=0;
       while (dzp_g[n][i][j]<Dkal-2*Szp_g[n][i]) {
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1]+2*Szp_g[n][i];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           if (Szp_g[n][i]<=0.04) dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.01;
                   else dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.02;
           Sz=Szp_g[n][i]-0.01;
           Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q;
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
           kol_grupp[n][i]=kol_grupp[n][i]+1;
      }
       Zp_g[n][i]=kol_grupp[n][i]*n+1;
    }
 //расчёт при числе зубьев в группе = 5
   n=5;
     Szp_g[n][1]=0.01;
     for (int i=2; i<=40; i++) Szp_g[n][i]=Szp_g[n][i-1]+0.01;
     for (int i=1; i<=40; i++) {
       dzp_g[n][i][1]=D0_;
       Perimetr_g[n][i][1]=3.1416*dzp_g[n][i][1];
       Sz=Szp_g[n][1];

      Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

       P_tek_g[n][i][1]=q*Perimetr_g[n][i][1];
       P_all_g[n][i][1]=P_tek_g[n][i][1];
       Sz=Szp_g[n][i];
       Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);
         q_g[n][i]=q;
       j=1; kol_grupp[n][i]=0;
       while (dzp_g[n][i][j]<Dkal-2*Szp_g[n][i]) {
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1]+2*Szp_g[n][i];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           dzp_g[n][i][j]=dzp_g[n][i][j-1];
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q_g[n][i];
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
         j=j+1;
           if (Szp_g[n][i]<=0.04) dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.01; else dzp_g[n][i][j]=dzp_g[n][i][j-1]-0.02;
           Sz=Szp_g[n][i]-0.01;
           Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);
           Perimetr_g[n][i][j]=3.1416*dzp_g[n][i][j]/n;
           P_tek_g[n][i][j]=Perimetr_g[n][i][j]*q;
           if (j<=Zmax_g) P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j];
              else P_all_g[n][i][j]=P_all_g[n][i][j-1]+P_tek_g[n][i][j]-P_tek_g[n][i][j-Zmax_g];
           kol_grupp[n][i]=kol_grupp[n][i]+1;
      }
       Zp_g[n][i]=kol_grupp[n][i]*n+1;
    }
 //выбор оптимального варианта
   for (int n=2; n<=5; n++) var_opt_g[n]=0;
   for (int n=2; n<=5;n++) {
     i=1;
     while (Szp_g[n][i]<=Szk_g) {
       max=P_all_g[n][i][1];
       for (int j=2; j<=Zp_g[n][i]; j++) {
         if (P_all_g[n][i][j]>=max) max=P_all_g[n][i][j];
      }
       if (max<=Pp_g) var_opt_g[n]=i;
       i=i+1;
    }
  }
   n=2; min=Zp_g[n][var_opt_g[n]];
   for (int i=3; i<=5; i++) {
     if (min>Zp_g[i][var_opt_g[i]]){min=Zp_g[i][var_opt_g[i]]; n=i;}
  }
 //расчёт выкружек на режущих зубьях
   Sz=Szp_g[n][var_opt_g[n]];

  // Pril_Struzhka(Sz,hkp_g,D_, b_g);

   if (n==2) l_n=2*b_g;
   if (n==3) l_n=2.2*b_g;
   if (n==4) l_n=3.2*b_g;
   if (n==5) l_n=4.2*b_g;
   lambda_n=360*l_n/(3.1416*D_);
   n_vik=floor(360/lambda_n)+4;
   if (n_vik % 2!=0) n_vik=n_vik+1;
   lambda_n=360/n_vik;
   l_n=(lambda_n/360)*(3.1416*D_);
   if (n=2) b_g=l_n/2;
   if (n=3) b_g=l_n/2.2;
   if (n=4) b_g=l_n/3.2;
   if (n=5) b_g=l_n/4.2;
   l_vik=l_n-b_g;
   lambda_vik=360*l_vik/(3.1416*D_);
   a_vik=D_*sin(qDegreesToRadians(lambda_vik/2));
   h_vik=10*Szp_g[n][var_opt_g[n]];
   d=h_vik-0.5*D_*(1-cos(qDegreesToRadians(lambda_vik/2)));
   R_vik=0.5*d+0.125*a_vik*a_vik/d;
   R_krug=R_vik*cos(qDegreesToRadians(35.0));
   if (R_krug>=100) R_krug=125;
   if ((R_krug<100)&&(R_krug>=80)) R_krug=100;
   if ((R_krug<80)&&(R_krug>=62.5)) R_krug=80;
   if ((R_krug<62.5)&&(R_krug>=50)) R_krug=62.5;
   if ((R_krug<50)&&(R_krug>=40)) R_krug=50;
   if ((R_krug<40)&&(R_krug>=30)) R_krug=40;
   if ((R_krug<30)&&(R_krug>=25)) R_krug=30;
   if ((R_krug<25)&&(R_krug>=22.5)) R_krug=25;
   if ((R_krug<22.5)&&(R_krug>=17.5)) R_krug=22.5;
   if ((R_krug<17.5)&&(R_krug>=15)) R_krug=17.5;
   if ((R_krug<15)&&(R_krug>=12.5)) R_krug=15;
   if ((R_krug<12.5)) R_krug=12.5;
   R_vik=R_krug/cos(qDegreesToRadians(35.0));
   h_vik=0.5*D_*(1-cos(qDegreesToRadians(lambda_vik/2)))+R_vik*(1-cos(asin(0.5*a_vik/R_vik)));
 //расчёт выкружек на переходных зубьях
   Sz=Szp_g[n][var_opt_g[n]];
  // Pril_Struzhka(Sz,hkp_g,D_, b_g_per);
   l_n_per=1.8*b_g_per;
   lambda_n_per=360*l_n_per/(3.1416*D_);
   n_vik_per=floor(360/lambda_n_per)+2;
   if (n_vik_per % 2!=0) n_vik_per=n_vik_per+1;
   lambda_n_per=360/n_vik_per;
   l_n_per=(lambda_n_per/360)*(3.1416*D_);
   b_g_per=l_n_per/1.8;
   l_vik_per=l_n_per-b_g_per;
   lambda_vik_per=360*l_vik_per/(3.1416*D_);
   a_vik_per=D_*sin(qDegreesToRadians(lambda_vik_per/2));
   h_vik_per=6*Szp_g[n][var_opt_g[n]];
   d_per=h_vik_per-0.5*D_*(1-cos(qDegreesToRadians(lambda_vik_per/2)));
   R_vik_per=0.5*d_per+0.125*a_vik_per*a_vik_per/d_per;
   R_krug_per=R_vik_per*cos(qDegreesToRadians(35.0));
   if (R_krug_per<=12.5) R_krug_per=10;
   if ((R_krug_per>12.5)&&(R_krug_per<=15)) R_krug_per=12.5;
   if ((R_krug_per>15)&&(R_krug_per<=17.5)) R_krug_per=15;
   if ((R_krug_per>17.5)&&(R_krug_per<=22.5)) R_krug_per=17.5;
   if ((R_krug_per>22.5)&&(R_krug_per<=25)) R_krug_per=22.5;
   if ((R_krug_per>25)&&(R_krug_per<=30)) R_krug_per=25;
   if ((R_krug_per>30)&&(R_krug_per<=40)) R_krug_per=30;
   if ((R_krug_per>40)&&(R_krug_per<=50)) R_krug_per=40;
   if ((R_krug_per>50)&&(R_krug_per<=62.5)) R_krug_per=50;
   if ((R_krug_per>62.5)&&(R_krug_per<=80)) R_krug_per=62.5;
   if ((R_krug_per>80)&&(R_krug_per<=100)) R_krug_per=80;
   if (R_krug_per>100) R_krug_per=100;
   R_vik_per=R_krug_per/cos(qDegreesToRadians(35.0));
   h_vik_per=0.5*D_*(1-cos(qDegreesToRadians(lambda_vik_per/2)))+R_vik_per*(1-cos(asin(0.5*a_vik_per/R_vik_per)));
 //расчёт переходных и калибрующих зубьев
   Aper_g=(Dkal-dzp_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]])/2;
   Zper=2; Zkal=4;
   if (Ra_<=20){Zper=3; Zkal=5;}
   if (Ra_<=2.5){Zper=5; Zkal=6;}
   if (Ra_<=1.25){Zper=6; Zkal=7;}
   Sz=Aper_g/Zper;

   Pril_UdNagruzka(Sz,gamma_rezhzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);

   for (int i=1; i<=Zper; i++) {
     dzp_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i]=dzp_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i-1]+2*Aper_g/Zper;
     Perimetr_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i]=0.6*3.1416*dzp_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i];
     P_tek_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i]=Perimetr_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i]*q;
  }
   lp_g=tp_g*(Zp_g[n][var_opt_g[n]]+Zper-1);
   Trezh_g=0.2*Szp_g[n][var_opt_g[n]];
   Sz=0.01;
   Pril_UdNagruzka(Sz,gamma_kalzub,cod_zag_,HB_zag_,cod_sozh_,Ra_, &q);
   for (int i=1; i<=Zkal; i++) {
     dzp_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i+Zper]=dzp_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i-1+Zper];
     Perimetr_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i+Zper]=3.1416*dzp_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i-1+Zper];
     P_tek_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i+Zper]=q*Perimetr_g[n][var_opt_g[n]][Zp_g[n][var_opt_g[n]]+i-1+Zper];
  }
   shag_zub=tp_g*2/3;
  Pril_Kanavka(shag_zub, &tk_g,&hkk_g,&rsk_g,&bk_g,&Rdk_g,&Fkk_g);
   lk_g=tk_g*Zkal;
   Lnp_g=l1+lp_g+lk_g+lz;
   Ldop_d=40*D0_;
   Ldop_st_g=lp_g+lk_g+lz+L_;
   Dzat_g=(D0_-hkp_g)*sin(qDegreesToRadians(45.0))/sin(qDegreesToRadians((double)gamma_rezhzub));
 //
 //выбор схемы резания
 //
   if (var_opt_o==0) Error_o=true;
   if ((var_opt_g[2]==0)&&(var_opt_g[3]=0)&&(var_opt_g[4]=0)&&(var_opt_g[5]=0)) Error_g=true;
   if ((Error_o==false)&&(Error_g==false)&&(lp_o<=lp_g)) shema=0;
             else shema=1;
   if ((Error_o==true)&&(Error_g==false)) shema=1;
   if ((Error_o==false)&&(Error_g==true)) shema=0;
   if ((Error_o==true)&&(Error_g=true)) shema=-1;
 //
 //вывод данных
 //
   WriteFile(F, "");
  if( shema==-1){//без вариантов
         WriteFile(F, "Тяговая сила данного протяжного станка не может обеспечить обработку отверстия");
        // CloseFile(F); Exit;
      }
    if( shema==0){//одинарная схема
       // //str(tp_o:3:1, temp);
         WriteFile(F, "Шаг режущих и переходных зубьев: tp= "+temp+" мм (см. приложение)");
        ////str(hkp_o:3:1, temp1);//str(rsp_o:3:1, temp2);//str(bp_o:3:1, temp3);//str(Rdp_o:3:1, temp4);
         WriteFile(F, "Параметры стружечных канавок: h= "+temp1+" мм, r= "+temp2+" мм, b= "+temp3+" мм, R= "+temp4+" мм");
        ////str(tk_o:3:1, temp);
         WriteFile(F, "Шаг калибрующих зубьев: tk= "+temp+" мм (см. приложение)");
        ////str(hkk_o:3:1, temp1);//str(rsk_o:3:1, temp2);//str(bk_o:3:1, temp3);//str(Rdk_o:3:1, temp4);
         WriteFile(F, "Параметры стружечных канавок: h= "+temp1+" мм, r= "+temp2+" мм, b= "+temp3+" мм, R= "+temp4+" мм");
         WriteFile(F, "");
         //str(Px:7:1, temp);
         WriteFile(F, "Наибольшее усилие, допустимое хвостовиком из условий прочности: Рх= "+temp+" Н");
        ////str(P1_o:7:1, temp);
         WriteFile(F, "Наибольшее усилие, допустимое прочностью протяжки по первому зубу: Р1= "+temp+" Н");
        ////str(Pp_o:7:1, temp);
         WriteFile(F, "Расчётная сила резания min(Px, P1, 0.8*Pc) : Рр= "+temp+" Н");
         WriteFile(F, "");
         WriteFile(F, "Расчёт режущих зубьев протяжки ведём по одинарной схеме резания");
         WriteFile(F, "Число одновременно работающих зубьев: Zmax= "+QString::number(Zmax_o));
        ////str(Szp_o[var_opt_o]:2:3, temp);
         WriteFile(F, "Принимаем подачу, допустимую по размещению стружки и усилию резания: Sz= "+temp+" мм");
         for (int i=1; i<=Zp_o[var_opt_o]; i++) {
           //str(dzp_o[var_opt_o][i]:4:3, temp1);
           //str(Perimetr_o[var_opt_o][i]:7:1, temp2);
           //str(P_tek_o[var_opt_o][i]:7:0, temp3);
           //str(Trezh_o:2:3, temp);
           WriteFile(F, "Режущий зуб №"+QString::number(i)+": диаметр dz= "+temp1+"(-"+temp+") мм,  рабочий периметр Пz= "+temp2+" мм,  нагрузка Pz= "+temp3+" Н");
        }
         for(int i=Zp_o[var_opt_o]+1; i<=Zp_o[var_opt_o]+Zper;i++) {
//          //str(dzp_o[var_opt_o][i]:4:3, temp1);
//          //str(Perimetr_o[var_opt_o][i]:7:1, temp2);
//          //str(P_tek_o[var_opt_o][i]:7:0, temp3);
//          //str(Trezh_o:2:3, temp);
           WriteFile(F, "Переходный зуб №"+QString::number(i)+": диаметр dz= "+temp1+"(-"+temp+") мм,  рабочий периметр Пz= "+temp2+" мм,  нагрузка Pz= "+temp3+" Н");
        }
         for (int i=Zp_o[var_opt_o]+Zper+1; i<= Zp_o[var_opt_o]+Zper+Zkal; i++) {
          temp1 =   QString::number(dzp_o[var_opt_o][i]);
          temp2 =   QString::number(Perimetr_o[var_opt_o][i]);
          temp3 =   QString::number(P_tek_o[var_opt_o][i]);

           if (usadka_==true) Tkal=Tizg+delta;
           else Tkal=Tizg-delta;
           temp=   QString::number(Tkal);
           WriteFile(F, "Калибрующий зуб №"+QString::number(i)+": диаметр dz= "+temp1+"(-"+temp+") мм,  рабочий периметр Пz= "+temp2+" мм,  нагрузка Pz= "+temp3+" Н");
        }
         WriteFile(F, "Всего зубьев: "+QString::number(Zp_o[var_opt_o]+Zper+Zkal)+"; в том числе: режущих - "+QString::number(Zp_o[var_opt_o])+", переходных - "+QString::number(Zper)+", калибрующих - "+QString::number(Zkal));
         WriteFile(F, "На зубьях №№ 1-"+QString::number(Zp_o[var_opt_o]+Zper)+" в шахматном порядке выполняем стружкоделительные канавки: "+QString::number(nk)+" канавок");
         temp =   QString::number(h_kan);

         WriteFile(F, "Глубина стружкоделительных канавок: С= "+temp+" мм (см. приложение)");
         WriteFile(F, "");
         WriteFile(F, "Передний угол на режущих и переходных зубьях: "+QString::number(gamma_rezhzub)+" градусов,  задний угол: 3 градуса,  форма зуба: "+forma_rezhzub+" (см. приложение)");
         WriteFile(F, "Передний угол на калибрующих зубьях: "+QString::number(gamma_kalzub)+" градусов,  задний угол: 1 градус,  форма зуба: "+forma_kalzub+" (см. приложение)");
         WriteFile(F, "Угол правки шлифовального круга для заточки переднего угла : 45 градусов");
         temp =   QString::number(Dzat_o);
         WriteFile(F, "Наибольший диаметр круга для заточки: Dзат="+temp+" мм");
         WriteFile(F, "");


         temp=QString::number(lp_o);


         WriteFile(F, "Длина режущей и переходной части протяжки: lp= "+temp+" мм");
        //str(lk_o:5:1,temp);
         temp=QString::number(lk_o);
         WriteFile(F, "Длина калибрующей части протяжки: lk= "+temp+" мм");
         //str(lz:5:1,temp);
         WriteFile(F, "Длина задней направляющей части протяжки: lz= "+temp+" мм");
         //str(Lnp_o:5:1,temp);
         WriteFile(F, "Полная длина протяжки: Lпр= "+temp+" мм");
         WriteFile(F, "");
         //str(Ldop_d:6:1,temp);
         WriteFile(F, "Допустимая длина протяжки из условий жёсткости: L_доп1=40*D0= "+temp+" мм");
         //str(Ldop_st_o:6:1,temp);
         WriteFile(F, "Ход ползуна станка необходимый для данной протяжки: L_доп2=lp+lk+lz+L= "+temp+" мм");
         if ((Ldop_d>=Lnp_o)&&(Ldop_st_o<=Lpx_stanok_)) WriteFile(F, "Все условия ограничения на длину выполняются");
         if ((Ldop_d<Lnp_o)&&(Ldop_st_o<=Lpx_stanok_)) {
           komplekt=floor(Lnp_o/Ldop_d)+1;
           WriteFile(F, "Длина протяжки не проходит по жёсткости, проектируем комплект протяжек из: "+QString::number(komplekt)+" штук");
        }
         if ((Ldop_d>=Lnp_o)&&(Ldop_st_o>Lpx_stanok_)){
           komplekt=floor(Ldop_st_o/Lpx_stanok_)+1;
           WriteFile(F, "Длина хода ползуна станка не обеспечит работу протяжки, проектируем комплект протяжек из: "+QString::number(komplekt)+" штук");
        }
         if ((Ldop_d<Lnp_o)&&(Ldop_st_o>Lpx_stanok_)){
           komplekt1=floor(Lnp_o/Ldop_d)+1;
           komplekt2=floor(Ldop_st_o/Lpx_stanok_)+1;
           if (komplekt1>=komplekt2) komplekt=komplekt1;
           else komplekt=komplekt2;
           WriteFile(F, "Длина протяжки не проходит по жёсткости и ходу ползуна, проектируем комплект протяжек из: "+QString::number(komplekt)+" штук");
        }
      }
    if( shema==1){//групповая схема
         //str(tp_g:3:1, temp);
         WriteFile(F, "Шаг режущих и переходных зубьев: tp= "+temp+" мм (см. приложение)");
         //str(hkp_g:3:1, temp1);//str(rsp_g:3:1, temp2);//str(bp_g:3:1, temp3);//str(Rdp_g:3:1, temp4);
         WriteFile(F, "Параметры стружечных канавок: h= "+temp1+" мм, r= "+temp2+" мм, b= "+temp3+" мм, R= "+temp4+" мм");
         //str(tk_g:3:1, temp);
         WriteFile(F, "Шаг калибрующих зубьев: tk= "+temp+" мм (см. приложение)");
         //str(hkk_g:3:1, temp1);//str(rsk_g:3:1, temp2);//str(bk_g:3:1, temp3);//str(Rdk_g:3:1, temp4);
         WriteFile(F, "Параметры стружечных канавок: h= "+temp1+" мм, r= "+temp2+" мм, b= "+temp3+" мм, R= "+temp4+" мм");
         WriteFile(F, "");
         //str(Px:7:1, temp);
         WriteFile(F, "Наибольшее усилие, допустимое хвостовиком из условий прочности: Рх= "+temp+" Н");
         //str(P1_g:7:1, temp);
         WriteFile(F, "Наибольшее усилие, допустимое прочностью протяжки по первому зубу: Р1= "+temp+" Н");
         //str(Pp_g:7:1, temp);
         WriteFile(F, "Расчётная сила резания min(Px, P1, 0.8*Pc) : Рр= "+temp+" Н");
         WriteFile(F, "");
         WriteFile(F, "Расчёт режущих зубьев протяжки ведём по групповой схеме резания");
         WriteFile(F, "Число одновременно работающих зубьев: Zmax= "+QString::number(Zmax_g)+"; число зубьев в группе: nг= "+QString::number(n));
         //str(Szp_g[n][var_opt_g[n]]:2:3, temp);
         WriteFile(F, "Принимаем подачу, допустимую по размещению стружки и усилию резания: Sz= "+temp+" мм");
//        //str(dzp_g[n][var_opt_g[n],1]:4:3, temp1);
//        //str(Perimetr_g[n][var_opt_g[n],1]:7:1, temp2);
//        //str(P_tek_g[n][var_opt_g[n],1]:7:0, temp3);
//        //str(Trezh_g:2:3, temp);
         WriteFile(F, "Режущий зуб №1: диаметр dz= "+temp1+"(-"+temp+") мм,  рабочий периметр Пz= "+temp2+" мм,  нагрузка Pz= "+temp3+" Н");
         for (int i=1; i<=kol_grupp[n][var_opt_g[n]]; i++) {
         WriteFile(F, "Группа "+QString::number(i));
           for(int j=1; j<=n; j++) {
//            //str(dzp_g[n][var_opt_g[n],(i-1)*n+j+1]:4:3, temp1);
//            //str(Perimetr_g[n][var_opt_g[n],(i-1)*n+j+1]:7:1, temp2);
//            //str(P_tek_g[n][var_opt_g[n],(i-1)*n+j+1]:7:0, temp3);
//            //str(Trezh_g:2:3, temp);
             WriteFile(F, "Режущий зуб №"+QString::number((i-1)*n+j+1)+": диаметр dz= "+temp1+"(-"+temp+") мм,  рабочий периметр Пz= "+temp2+" мм,  нагрузка Pz= "+temp3+" Н");
          }
        }
         for (int i=Zp_g[n][var_opt_g[n]]+1; i<=Zp_g[n][var_opt_g[n]]+Zper; i++) {
//          //str(dzp_g[n][var_opt_g[n],i]:4:3, temp1);
//          //str(Perimetr_g[n][var_opt_g[n],i]:7:1, temp2);
//          //str(P_tek_g[n][var_opt_g[n],i]:7:0, temp3);
//          //str(Trezh_g:2:3, temp);
           WriteFile(F, "Переходный зуб №"+QString::number(i)+": диаметр dz= "+temp1+"(-"+temp+") мм,  рабочий периметр Пz= "+temp2+" мм,  нагрузка Pz= "+temp3+" Н");
        }
         for (int i=Zp_g[n][var_opt_g[n]]+Zper+1; i<=Zp_g[n][var_opt_g[n]]+Zper+Zkal; i++) {
//          //str(dzp_g[n][var_opt_g[n],i]:4:3, temp1);
//          //str(Perimetr_g[n][var_opt_g[n],i]:7:1, temp2);
//          //str(P_tek_g[n][var_opt_g[n],i]:7:0, temp3);
           if (usadka_==true) Tkal=Tizg+delta; else Tkal=Tizg-delta;
//          //str(Tkal:2:3, temp);
           WriteFile(F, "Калибрующий зуб №"+QString::number(i)+": диаметр dz= "+temp1+"(-"+temp+") мм,  рабочий периметр Пz= "+temp2+" мм,  нагрузка Pz= "+temp3+" Н");
        }
         WriteFile(F, "Всего зубьев: "+QString::number(Zp_g[n][var_opt_g[n]]+Zper+Zkal)+"; в том числе: режущих - "+QString::number(Zp_g[n][var_opt_g[n]])+", переходных - "+QString::number(Zper)+", калибрующих - "+QString::number(Zkal));
         WriteFile(F, "На всех режущих зубьях в группах, кроме последнего, в шахматном порядке выполняем выкружки: "+QString::number(n_vik)+" выкруж(ки/ек)");
        //str(h_vik:3:1, temp1);
        //str(a_vik:3:1, temp2);
        //str(R_vik:4:1, temp3);
         WriteFile(F, "Параметры выкружек: глубина - hв= "+temp1+" мм, ширина - ав= "+temp2+" мм, радиус - Rв= "+temp3+" мм (см. приложение)");
        //str(2*R_krug:4:1, temp);
         WriteFile(F, "Диаметр абразивного круга для шлифования выкружек: Dк= "+temp+" мм");
         WriteFile(F, "На всех переходных зубьях в шахматном порядке выполняем выкружки: "+QString::number(n_vik_per)+" выкруж(ки/ек)");
        //str(h_vik_per:3:1, temp1);
        //str(a_vik_per:3:1, temp2);
        //str(R_vik_per:4:1, temp3);
         WriteFile(F, "Параметры выкружек: глубина - hв= "+temp1+" мм, ширина - ав= "+temp2+" мм, радиус - Rв= "+temp3+" мм (см. приложение)");
        //str(2*R_krug_per:4:1, temp);
         WriteFile(F, "Диаметр абразивного круга для шлифования выкружек: Dк= "+temp+" мм");
         WriteFile(F, "");
         WriteFile(F, "Передний угол на режущих и переходных зубьях: "+QString::number(gamma_rezhzub)+" градусов,  задний угол: 3 градуса,  форма зуба: "+forma_rezhzub+" (см. приложение)");
         WriteFile(F, "Передний угол на калибрующих зубьях: "+QString::number(gamma_kalzub)+" градусов,  задний угол: 1 градус,  форма зуба: "+forma_kalzub+" (см. приложение)");
         WriteFile(F, "Угол правки шлифовального круга для заточки переднего угла : 45 градусов");
        //str(Dzat_g:5:2, temp);
         WriteFile(F, "Наибольший диаметр круга для заточки: Dзат="+temp+" мм");
         WriteFile(F, "");
        //str(lp_g:5:1,temp);
         WriteFile(F, "Длина режущей и переходной части протяжки: lp= "+temp+" мм");
        //str(lk_g:5:1,temp);
         WriteFile(F, "Длина калибрующей части протяжки: lk= "+temp+" мм");
        //str(lz:5:1,temp);
         WriteFile(F, "Длина задней направляющей части протяжки: lz= "+temp+" мм");
        //str(Lnp_g:5:1,temp);
         WriteFile(F, "Полная длина протяжки: Lпр= "+temp+" мм");
         WriteFile(F, "");
        //str(Ldop_d:6:1,temp);
         WriteFile(F, "Допустимая длина протяжки из условий жёсткости: L_доп1=40*D0= "+temp+" мм");
        //str(Ldop_st_g:6:1,temp);
         WriteFile(F, "Ход ползуна станка необходимый для данной протяжки: L_доп2=lp+lk+lz+L= "+temp+" мм");
         if ((Ldop_d>=Lnp_g)&&(Ldop_st_g<=Lpx_stanok_)) WriteFile(F, "Все условия ограничения на длину выполняются");
         if ((Ldop_d<Lnp_g)&&(Ldop_st_g<=Lpx_stanok_)){
           komplekt=floor(Lnp_g/Ldop_d)+1;
           WriteFile(F, "Длина протяжки не проходит по жёсткости, проектируем комплект протяжек из: "+QString::number(komplekt)+" штук");
        }
         if ((Ldop_d>=Lnp_g)&&(Ldop_st_g>Lpx_stanok_)){
           komplekt=floor(Ldop_st_g/Lpx_stanok_)+1;
           WriteFile(F, "Длина хода ползуна станка не обеспечит работу протяжки, проектируем комплект протяжек из: "+QString::number(komplekt)+" штук");
        }
         if ((Ldop_d<Lnp_g)&&(Ldop_st_g>Lpx_stanok_)){
           komplekt1=floor(Lnp_g/Ldop_d)+1;
           komplekt2=floor(Ldop_st_g/Lpx_stanok_)+1;
           if (komplekt1>=komplekt2) komplekt=komplekt1; else komplekt=komplekt2;
           WriteFile(F, "Длина протяжки не проходит по жёсткости и ходу ползуна, проектируем комплект протяжек из: "+QString::number(komplekt)+" штук");
        }
    }
}

void MainWindow::Pril_Kanavka(double shag_zub, double *tp, double *hk, double *rs, double *b, double *Rd, double *Fk)
{
    if (shag_zub>=32) { *tp=32; *hk=12.0; *rs=6.0; *b=12.0; *Rd=20.0; *Fk=113.1; }
    if (shag_zub<32) { *tp=30; *hk=12.0; *rs=6.0; *b=11.5; *Rd=20.0; *Fk=113.1; }
    if (shag_zub<30) { *tp=28; *hk=12.0; *rs=6.0; *b=9.5; *Rd=20.0; *Fk=113.1; }
    if (shag_zub<28) { *tp=26; *hk=10.0; *rs=5.0; *b=10.5; *Rd=16.0; *Fk=78.5; }
    if (shag_zub<26) { *tp=25; *hk=10.0; *rs=5.0; *b=9.5; *Rd=16.0; *Fk=78.5; }
    if (shag_zub<25) { *tp=24; *hk=10.0; *rs=5.0; *b=8.5; *Rd=16.0; *Fk=78.5; }
    if (shag_zub<24) { *tp=22; *hk=9.0; *rs=4.5; *b=8.0; *Rd=14.0; *Fk=63.6; }
    if (shag_zub<22) { *tp=21; *hk=9.0; *rs=4.5; *b=7.0; *Rd=14.0; *Fk=63.6; }
    if (shag_zub<21) { *tp=20; *hk=9.0; *rs=4.5; *b=6.0; *Rd=14.0; *Fk=63.6; }
    if (shag_zub<20) { *tp=19; *hk=8.0; *rs=4.0; *b=7.0; *Rd=12.0; *Fk=50.3; }
    if (shag_zub<19) { *tp=18; *hk=8.0; *rs=4.0; *b=6.0; *Rd=12.0; *Fk=50.3; }
    if (shag_zub<18) { *tp=17; *hk=7.0; *rs=3.5; *b=6.0; *Rd=11.0; *Fk=38.5; }
    if (shag_zub<17) { *tp=16; *hk=7.0; *rs=3.5; *b=5.0; *Rd=11.0; *Fk=38.5; }
    if (shag_zub<16) { *tp=15; *hk=6.0; *rs=3.0; *b=5.5; *Rd=10.0; *Fk=28.3; }
    if (shag_zub<15) { *tp=14; *hk=6.0; *rs=3.0; *b=4.5; *Rd=10.0; *Fk=28.3; }
    if (shag_zub<14) { *tp=13; *hk=5.0; *rs=2.5; *b=5.0; *Rd=8.0; *Fk=19.6; }
    if (shag_zub<13) { *tp=12; *hk=5.0; *rs=2.5; *b=4.0; *Rd=8.0; *Fk=19.6; }
    if (shag_zub<12) { *tp=11; *hk=4.5; *rs=2.3; *b=4.0; *Rd=7.0; *Fk=15.9; }
    if (shag_zub<11) { *tp=10; *hk=4.0; *rs=2.0; *b=3.5; *Rd=6.0; *Fk=12.6; }
    if (shag_zub<10) { *tp=9; *hk=3.6; *rs=1.8; *b=3.5; *Rd=5.5; *Fk=9.6; }
    if (shag_zub<9) { *tp=8; *hk=3.6; *rs=1.8; *b=2.5; *Rd=5.5; *Fk=9.6; }
    if (shag_zub<8) { *tp=7; *hk=3.0; *rs=1.5; *b=2.3; *Rd=5.0; *Fk=7.1; }
    if (shag_zub<7) { *tp=6; *hk=2.5; *rs=1.3; *b=2.0; *Rd=4.0; *Fk=4.0; }
    if (shag_zub<6) { *tp=5.5; *hk=2.0; *rs=1.0; *b=2.5; *Rd=3.0; *Fk=3.14; }
    if (shag_zub<5.5) { *tp=5.0; *hk=2.0; *rs=1.0; *b=2.0; *Rd=3.0; *Fk=3.14; }
    if (shag_zub<5.0) { *tp=4.5; *hk=2.0; *rs=1.0; *b=1.5; *Rd=3.0; *Fk=3.14; }
    if (shag_zub<4.5) { *tp=4.0; *hk=1.8; *rs=0.9; *b=1.2; *Rd=2.8; *Fk=2.54; }
}
 //закрытие файла данных





