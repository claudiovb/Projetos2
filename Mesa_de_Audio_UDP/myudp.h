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

private:
    QUdpSocket *socket;
    QHostAddress *bcast,*host;

};

#endif // MYUDP_H
