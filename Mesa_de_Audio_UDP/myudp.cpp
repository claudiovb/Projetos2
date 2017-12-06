
#include "myudp.h"
#include <QTextStream>
MyUDP::MyUDP(QObject *parent) :
    QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    host  = new QHostAddress("192.168.1.233");
    bcast = new QHostAddress("192.168.1.98");


    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
    socket->bind(*host, 9283);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUDP::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello from UDP");

    // Sends the datagram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(Data, *bcast, 8888);
}

void MyUDP::readyRead()
{
    // when data comes in
    QByteArray buffer,Data;
    const char* pBuffer;
    bool sucess= false;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
   // qDebug() << "Message: " << buffer;

    pBuffer = buffer.operator const char *();
    if(pBuffer[0] == 'A' && pBuffer[1] == 'b'){
        if(buffer.size() > 2)
            sucess = DbyteToShort(pBuffer,buffer.size());
             buffer.clear();
    }
    if(!sucess){
        //Data.setNum(0xf,16);
        //socket->writeDatagram(Data, *bcast, 8888);
        qCritical() << "No data recieved" << buffer.size();
    }



}
void MyUDP::Transmission(bool transm){
    QByteArray Data;
    if(transm){
        Data.setNum(0x0,16);
        canChangeEffect = false;
    }
    else{
        Data.setNum(0xf,16);
        CloseFile();
        canChangeEffect = true;
    }
    socket->writeDatagram(Data, *bcast, 8888);

}

bool MyUDP::DbyteToShort(const char *pBuff,int size){
    ushort audioBuff[(size>>1)-2] = {0};
    bool sucess = false;
    for(int i =0; i<((size>>1)-2);i++){
        audioBuff[i] =  (((ushort)pBuff[2*i+2]) << 8) | (0xff & pBuff[2*i+3]);
        //assist = (ushort)c;
        //audioBuff[i] += assist;
    }
     sucess = SaveFile(audioBuff,(size>>1)-2); //certo
   // sucess = SaveFile(pBuff,size);
    return sucess;
}
//bool MyUDP::SaveFile(const char * audioBuff,int size){
bool MyUDP::SaveFile(ushort* audioBuff,int size){ //certo

    if(fp == NULL){
    std::string filename = "Audio/audiofile";
    filename += std::to_string(filenumber);
    filename += ".pcm";
    const char * c = filename.c_str();
    fp = fopen(c,"wb+");
    filenumber++;
    }
    fwrite(audioBuff,sizeof(short),size,fp); //certo
   // fwrite(audioBuff,sizeof(char),size,fp);
    return true;
}
void MyUDP::CloseFile(){
    if(fp != NULL){
        fclose(fp);
        fp = NULL;
    }
}

void MyUDP::parameter1Changed(int value){
    QByteArray Data;
   // qDebug() << "Value changed: " << value;
    if(canChangeEffect){
        Data.resize(7);
        for(int i = 0; i<4;i++)
            Data[i] = 0x55;
        Data[4] = 0x02;
        Data[5] = (value >> 8);
        Data[6] = (value & 0xff);
        qDebug() << "Value changed: " << Data;
        socket->writeDatagram(Data, *bcast, 8888);

    }
}
void MyUDP::parameter2Changed(int value){
    QByteArray Data;
    if(canChangeEffect){
        Data.clear();
        Data.resize(7);
        for(int i = 0; i<4;i++)
            Data[i] = 0x55;
        Data[4] = 0x01;
        Data[5] = (value >> 8);
        Data[6] = (uchar)(value & 0x00ff);
        qDebug() << "Value changed: "<< value;
        //for(int i = 0;i<Data.size();i++)
           // qDebug() << "Value changed: " << i <<QString::number(Data[i], 16);
        socket->writeDatagram(Data, *bcast, 8888);

    }
}

    void MyUDP::ChannelsSelect(bool value,ChannelSelect selected,int in_out){
       QByteArray Data;
       Data.clear();
       QTextStream out(stdout);
       Data.resize(7);
       for(int i = 0; i<4;i++)
           Data[i] = 0x55;
       if(in_out == 0){
           Data[4] = 0x03;
           Data[5] = 0x0;
           Data[6] = 0x0;

            switch(selected){
                case ChannelSelect::aux1:
                    if(value)
                        tryout +=0x1;
                    else if(tryout >= 1)
                       tryout -=0x1;
                break;
                case ChannelSelect::aux2:
                    if(value)
                        tryout +=0x2;
                    else if(tryout >= 2)
                        tryout -=0x2;
                break;
                case ChannelSelect::aux3:
                    if(value)
                        tryout +=0x4;
                    else if(tryout >= 4)
                        tryout -=0x4;
                break;
                case ChannelSelect::aux4:
                    if(value)
                        tryout +=0x08;
                    else if(tryout >= 8)
                        tryout -=0x08;
                break;
                default:
                     qDebug() << "Deu xoli" ;
                break;
            }
            Data[6] = tryout;
        }
       else if(in_out == 1){
           Data[4] = 0x04;
           Data[5] = 0x0;
           Data[6] = 0x0;
           switch(selected){
               case ChannelSelect::aux1:
                   if(value)
                       tryout1 +=0x1;
                   else if(tryout1 >= 1)
                      tryout1 -=0x1;
               break;
               case ChannelSelect::aux2:
                   if(value)
                       tryout1 +=0x2;
                   else if(tryout1 >= 2)
                       tryout1 -=0x2;
               break;
               case ChannelSelect::aux3:
                   if(value)
                       tryout1 +=0x4;
                   else if(tryout1 >= 4)
                       tryout1 -=0x4;
               break;
               case ChannelSelect::aux4:
                   if(value)
                       tryout1 +=0x08;
                   else if(tryout1 >= 8)
                       tryout1 -=0x08;
               break;
           case ChannelSelect::reverb:
               if(value)
                   tryout1 +=0x10;
               else if(tryout1 >= 16)
                   tryout1 -=0x10;
           break;

           }
           Data[6] = tryout1;
       }
       else if(in_out==2){
           Data[4] = 0x05;
           Data[5] = 0x0;
           Data[6] = 0x0;
           switch(selected){
               case ChannelSelect::aux1:
                   if(value)
                       tryout2 +=0x1;
                   else if(tryout2 >= 1)
                      tryout2 -=0x1;
               break;
               case ChannelSelect::aux2:
                   if(value)
                       tryout2 +=0x2;
                   else if(tryout2 >= 2)
                       tryout2 -=0x2;
               break;
               case ChannelSelect::aux3:
                   if(value)
                       tryout2 +=0x4;
                   else if(tryout2 >= 4)
                       tryout2 -=0x4;
               break;
               case ChannelSelect::aux4:
                   if(value)
                       tryout2 +=0x08;
                   else if(tryout2 >= 8)
                       tryout2 -=0x08;
               break;
           case ChannelSelect::reverb:
               if(value)
                   tryout2 +=0x10;
               else if(tryout2 >= 16)
                   tryout2 -=0x10;
           break;

           }
           Data[6] = tryout2;
       }
        qDebug() << "Value changed: "<< Data;
         out << "Value changed= " << Data << "  Msg last byte = " << Data[6] << endl;
        socket->writeDatagram(Data, *bcast, 8888);
    }


