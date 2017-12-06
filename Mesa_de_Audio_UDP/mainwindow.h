#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "ui_mainwindow.h"
#include "myudp.h"
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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
private:
    MyUDP* Udp;
    bool button1 = true, button2 = true, button3 = true,
         button4 = true, button5 = true, button6 = true, button7 = true,
    button8 = true, button9 = true, button10 = true, button11 = true,
    button12 = true, button13 = true, button14 = true;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
