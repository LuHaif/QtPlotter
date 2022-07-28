#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT
public:
    UdpSender();
    ~UdpSender();
    void initSender(QString desHost, int port);
    void send(QByteArray msg);
public slots:
    void recMsg(QByteArray msgInfo);
private:
    QUdpSocket *m_Socket = NULL;
    QString m_address;
    int m_port;
};

#endif // UDPSENDER_H
