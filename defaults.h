#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <QObject>

class Defaults : public QObject
{
    Q_OBJECT
public:
    explicit Defaults(QObject *parent = 0);
    QString database()  { return m_database; }
    QString host() { return m_host; }
    QString user() { return m_user; }
    int port() { return m_port; }

signals:

public slots:

private:
    QString m_host;
    QString m_database;
    QString m_user;
    int m_port;
};

#endif // DEFAULTS_H
