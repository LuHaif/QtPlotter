#include "udpreciver.h"

UdpReciver::UdpReciver(QObject *parent) : QObject(parent)
{
    m_thread = new QThread();
    m_udpSocket = new QUdpSocket();
    QString localhost = "";
    init_port(localhost, 43897);
    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(readDatagrams()), Qt::DirectConnection);
    this->moveToThread(m_thread);
    m_udpSocket->moveToThread(m_thread);
    m_thread->start();
}
UdpReciver::~UdpReciver()
{
    m_thread->quit();
    m_thread->wait();
    m_thread->deleteLater();
    m_udpSocket->close();
    m_udpSocket->deleteLater();
}

void UdpReciver::run(){

}
void UdpReciver::init_port(QString tmphost, int tmport)
{
    m_port = tmport;
    m_localhost = tmphost;
    m_udpSocket->bind(QHostAddress(m_localhost), m_port);
}
void UdpReciver::readDatagrams()
{
    QHostAddress client_address; //client ip addr
    m_data.clear();
    while(m_udpSocket->hasPendingDatagrams())
    {

        m_data.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(m_data.data(), m_data.size(), &client_address);
        QString strclient_address = client_address.toString();
        deliverInfo(m_data, strclient_address);
//        std::reverse(m_data.begin(), m_data.end());
        QByteArray m_little_data = (QByteArray)qToLittleEndian(m_data);
        emit signal_new_info(m_little_data);
    }
}
