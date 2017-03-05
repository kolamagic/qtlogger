#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include <QObject>
#include "mythread.h"
#include <QList>
#include <QTimerEvent>
#include "filelogger.h"

class MyController : public QObject
{
    Q_OBJECT
private:
    int m_timer_id;
    int m_elapsed;
    QList<MyThread*> m_threads;
    FileLogger* m_logger;

public:
    explicit MyController(QObject *parent = 0);
    ~MyController();

    void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;
signals:

public slots:
};

#endif // MYCONTROLLER_H
