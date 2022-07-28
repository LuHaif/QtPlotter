#ifndef UDPRECIVER_H
#define UDPRECIVER_H
#include <QUdpSocket>
#include <QThread>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#include <QtEndian>
#include <QDateTime>
struct CommandHead{
  uint32_t code;
  int32_t command_value_;
   /// This value indicate whether you have messages to be send behind the    address of the value named type
   /// @param 1 : There are messages to be send
   /// @param 0 :There is nothing to be send ;
   uint32_t type ;
};
struct CommandMessage{
  CommandHead command;
  uint8_t data_buffer[1024];
};
class UdpReciver : public QObject
{
    Q_OBJECT
public:
    UdpReciver(QObject *parent = NULL);
    ~UdpReciver();
    void init_port(QString tmphost, int tmport);
signals:
    void deliverInfo(QByteArray info, QString clientip);
    void signal_new_info(QByteArray);
public slots:
    void readDatagrams(); //listen UDP data
protected:
    void run();
private:
    QUdpSocket *m_udpSocket;
    QString m_localhost;
    int m_port;
    QByteArray m_data;
    QThread *m_thread;
};

#endif // UDPRECIVER_H
