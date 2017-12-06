


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
    Udp->ChannelsSelect(button1,Udp->ChannelSelect::aux1,0);
    button1 = !button1;
}

void MainWindow::on_pushButton_2_clicked()
{

    if(button2){
        ui->pushButton_2->setText("On");
    }else{
        ui->pushButton_2->setText("Off");
    }

    Udp->ChannelsSelect(button2,Udp->ChannelSelect::aux2,0);
    button2 = !button2;
}
void MainWindow::on_pushButton_3_clicked()
{

    if(button3){
        ui->pushButton_3->setText("On");
    }else{
        ui->pushButton_3->setText("Off");
    }

    Udp->ChannelsSelect(button3,Udp->ChannelSelect::aux3,0);
    button3 = !button3;
}
void MainWindow::on_pushButton_4_clicked()
{

    if(button4){
        ui->pushButton_4->setText("On");
    }else{
        ui->pushButton_4->setText("Off");
    }
    Udp->ChannelsSelect(button4,Udp->ChannelSelect::aux4,0);
    button4 = !button4;
}
void MainWindow::on_pushButton_5_clicked()
{

    if(button5){
        ui->pushButton_5->setText("On");
    }else{
        ui->pushButton_5->setText("Off");
    }
    Udp->ChannelsSelect(button5,Udp->ChannelSelect::aux1,1);
    button5 = !button5;
}
void MainWindow::on_pushButton_6_clicked()
{

    if(button6){
        ui->pushButton_6->setText("On");
    }else{
        ui->pushButton_6->setText("Off");
    }
    Udp->ChannelsSelect(button6,Udp->ChannelSelect::aux2,1);
    button6 = !button6;
}
void MainWindow::on_pushButton_7_clicked()
{

    if(button7){
        ui->pushButton_7->setText("On");
    }else{
        ui->pushButton_7->setText("Off");
    }
    Udp->ChannelsSelect(button7,Udp->ChannelSelect::aux3,1);
    button7 = !button7;
}
void MainWindow::on_pushButton_8_clicked()
{

    if(button8){
        ui->pushButton_8->setText("On");
    }else{
        ui->pushButton_8->setText("Off");
    }
    Udp->ChannelsSelect(button8,Udp->ChannelSelect::aux4,1);
    button8 = !button8;
}
void MainWindow::on_pushButton_9_clicked()
{

    if(button9){
        ui->pushButton_9->setText("On");
    }else{
        ui->pushButton_9->setText("Off");
    }
    Udp->ChannelsSelect(button9,Udp->ChannelSelect::reverb,1);
    button9 = !button9;
}
void MainWindow::on_pushButton_10_clicked()
{

    if(button10){
        ui->pushButton_10->setText("On");
    }else{
        ui->pushButton_10->setText("Off");
    }
    Udp->ChannelsSelect(button10,Udp->ChannelSelect::aux4,2);
    button10 = !button10;
}
void MainWindow::on_pushButton_11_clicked()
{

    if(button11){
        ui->pushButton_11->setText("On");
    }else{
        ui->pushButton_11->setText("Off");
    }
    Udp->ChannelsSelect(button11,Udp->ChannelSelect::aux1,2);
    button11 = !button11;
}
void MainWindow::on_pushButton_12_clicked()
{

    if(button12){
        ui->pushButton_12->setText("On");
    }else{
        ui->pushButton_12->setText("Off");
    }
    Udp->ChannelsSelect(button12,Udp->ChannelSelect::aux3,2);
    button12 = !button12;
}
void MainWindow::on_pushButton_13_clicked()
{

    if(button13){
        ui->pushButton_13->setText("On");
    }else{
        ui->pushButton_13->setText("Off");
    }
    Udp->ChannelsSelect(button13,Udp->ChannelSelect::reverb,2);
    button13 = !button13;
}
void MainWindow::on_pushButton_14_clicked()
{

    if(button14){
        ui->pushButton_14->setText("On");
    }else{
        ui->pushButton_14->setText("Off");
    }
    Udp->ChannelsSelect(button14,Udp->ChannelSelect::aux2,2);
    button14 = !button14;
}

