#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <QRadioButton>
#include <QFile>
#include <QDir>
#include <QVariant>
struct tool
{
    QString type;
    QString model;
    int power;
    int step;
};
struct material
{
    QString group;
    QString mark;
};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void TestSlot();
    void Cylinder();
    void SwitchTable(bool);
    void on_pushButton_clicked();
    void slotRadioToggled(bool);

private:
    Ui::MainWindow *ui;
    void FillTableTool();
    void FillTableMaterial();
    void FillTableCylinderHorizontal();
    QList<tool> GetToolsCylinderVertical();
    QList<material> GetMaterial();
    QString hbString;
    QList<QRadioButton*> listHBRadioButton;
    int indexHBRadioButton;
    QList<tool> GetToolsCylinderHorizontal();
    void WriteFile (QString nameFile, QString string);

    void Protyagka_Tzil(QString typ_stanok_, QString model_stanok_, int P_stanok_, int Lpx_stanok_, QString mat_zag_, int cod_zag_, int HB_zag_, bool usadka_, QString mat_sozh_, int cod_sozh_, double Ra_, int D0_, int D_, int L_, int Kvalitet_, int HiOtkl_, int LowOtkl_, QString nameFile);
};

#endif // MAINWINDOW_H
