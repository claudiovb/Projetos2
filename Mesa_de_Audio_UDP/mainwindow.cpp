


#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Udp = new MyUDP();
    Udp->HelloUDP();
    QStateMachine machine1,machine2,machin3,machine4;
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),Udp,SLOT(parameter1Changed(int)));
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),Udp,SLOT(parameter2Changed(int)));
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    if(button1){
        ui->pushButton->setText("On");
    }else{
        ui->pushButton->setText("Off");
    }
    Udp->ChannelsSelect(button1,Udp->ChannelSelect::aux1);
    button1 = !button1;
}

void MainWindow::on_pushButton_2_clicked()
{

    if(button2){
        ui->pushButton_2->setText("On");
    }else{
        ui->pushButton_2->setText("Off");
    }

    Udp->ChannelsSelect(button2,Udp->ChannelSelect::aux2);
    button2 = !button2;
}
void MainWindow::on_pushButton_3_clicked()
{

    if(button3){
        ui->pushButton_3->setText("On");
    }else{
        ui->pushButton_3->setText("Off");
    }

    Udp->ChannelsSelect(button3,Udp->ChannelSelect::aux3);
    button3 = !button3;
}
void MainWindow::on_pushButton_4_clicked()
{

    if(button4){
        ui->pushButton_4->setText("On");
    }else{
        ui->pushButton_4->setText("Off");
    }
    Udp->ChannelsSelect(button4,Udp->ChannelSelect::aux4);
    button4 = !button4;
}

