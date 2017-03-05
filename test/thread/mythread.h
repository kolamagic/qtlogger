#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class MyThread : public QThread
{
    Q_OBJECT

private:
    bool m_quiting;
    QMutex m_mutex;
    QWaitCondition m_wait_cond;

public:
    explicit MyThread(QObject *parent = 0);

    void run() Q_DECL_OVERRIDE;

    void setQuiting();

private:
    QByteArray randstr() const;

signals:

public slots:
};

#endif // MYTHREAD_H
