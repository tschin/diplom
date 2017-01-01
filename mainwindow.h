#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QHeaderView>
struct tool
{
    QString type;
    QString model;
    int power;
    int step;
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
private:
    Ui::MainWindow *ui;
    void FillTable();
    QList<tool> GetTools();
};

#endif // MAINWINDOW_H
