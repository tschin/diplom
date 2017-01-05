#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QHeaderView>
#include <QRadioButton>
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

};

#endif // MAINWINDOW_H
