#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <QUdpSocket>

class Server : public QThread
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    
signals:
    void message(const QString &message);

public slots:

protected:
    void run();

private:
    QUdpSocket *m_socket;
};

#endif // SERVER_H
