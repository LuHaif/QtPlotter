#include "udpsender.h"

UdpSender::UdpSender()
{
    m_Socket = new QUdpSocket();
    initSender("255.255.255.255", 8194);
}
UdpSender::~UdpSender()
{
    if (m_Socket != NULL)
    {
        delete m_Socket;
        m_Socket = NULL;
    }
}
void UdpSender::initSender(QString desHost, int port)
{
    m_address = desHost;
    m_port = port;
}
void UdpSender::send(QByteArray msg)
{
    m_Socket->writeDatagram(msg, QHostAddress(m_address), m_port);
}
void UdpSender::recMsg(QByteArray msgInfo)
{
    send(msgInfo);
}
