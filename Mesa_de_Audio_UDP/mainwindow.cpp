#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myudp.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyUDP* Udp = new MyUDP();
    Udp->HelloUDP();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startRecord_clicked()
{
    ui->label->setText("gravando");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText("parou");
}
