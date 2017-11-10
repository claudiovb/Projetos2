// myudp.h

#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);
    void HelloUDP();
    void Transmission(bool transm);
signals:

public slots:
    void readyRead();
    void parameter1Changed(int value);
    void parameter2Changed(int value);
private:
    bool canChangeEffect = true;
    int filenumber = 0;
    FILE* fp = NULL;
    QUdpSocket *socket;
    QHostAddress *bcast,*host;
    bool DbyteToShort(const char* pBuff,int size);
    bool SaveFile(ushort* audioBuff,int size);
    //bool SaveFile(const char* audioBuff,int size);
    void CloseFile();

};

#endif // MYUDP_H
