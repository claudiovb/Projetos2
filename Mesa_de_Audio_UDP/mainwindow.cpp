#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Udp = new MyUDP();
    Udp->HelloUDP();
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),Udp,SLOT(parameter1Changed(int)));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),Udp,SLOT(parameter2Changed(int)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startRecord_clicked()
{
    ui->label->setText("gravando");
    Udp->Transmission(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText("parou");
    Udp->Transmission(false);
}
