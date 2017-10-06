
#include "myudp.h"

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
    if(pBuffer[0] == 'A' && pBuffer[1] == 'b')
        sucess = DbyteToShort(pBuffer,buffer.size());

    if(!sucess){
        Data.setNum(0xf,16);
        socket->writeDatagram(Data, *bcast, 8888);
        qCritical() << "critical error line 61,stopping transmission";
    }



}
void MyUDP::Transmission(bool transm){
    QByteArray Data;
    if(transm) Data.setNum(0x0,16);
    else{
        Data.setNum(0xf,16);
        CloseFile();
    }
    socket->writeDatagram(Data, *bcast, 8888);

}

bool MyUDP::DbyteToShort(const char *pBuff,int size){
    ushort audioBuff[(size>>1)-2] = {0};
    ushort assist = 0;
    bool sucess = false;
    for(int i =0; i<((size>>1)-2);i++){
        audioBuff[i] =  (((ushort)pBuff[2*i+2]) << 8) | (0xff & pBuff[2*i+3]);
        //assist = (ushort)c;
        //audioBuff[i] += assist;
    }
     sucess = SaveFile(audioBuff,(size>>1)-2);
    return sucess;
}
bool MyUDP::SaveFile(ushort* audioBuff,int size){

    if(fp == NULL){
    std::string filename = "Audio/audiofile";
    filename += std::to_string(filenumber);
    filename += ".pcm";
    const char * c = filename.c_str();
    fp = fopen(c,"wb+");
    filenumber++;
    }
    fwrite(audioBuff,sizeof(short),size,fp);
    return true;
}
void MyUDP::CloseFile(){
    if(fp != NULL){
        fclose(fp);
        fp = NULL;
    }
}

