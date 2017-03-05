#include "mycontroller.h"
#include <QCoreApplication>
#include <QSettings>

#define MAX_THREADS 32
#define RUN_INTEVAL 600

MyController::MyController(QObject *parent)
    : QObject(parent)
    , m_timer_id(0)
    , m_elapsed(0)
    , m_threads()
{
    qsrand(::time(0));

    QSettings* settings = new QSettings("qlogger.ini", QSettings::IniFormat, this);
    m_logger = new FileLogger(settings);
    m_logger->installMsgHandler();
    m_timer_id = startTimer(1000, Qt::PreciseTimer);
}


MyController::~MyController()
{
    delete m_logger;
}


void MyController::timerEvent(QTimerEvent *tEvent)
{
    if (tEvent->timerId() == m_timer_id)
    {
        ++m_elapsed;

        if (m_elapsed < MAX_THREADS) {
            MyThread* thread = new MyThread();
            m_threads.push_back(thread);
            thread->start();
            printf("start new thread\n");
        }
        else {
            int e = m_elapsed - MAX_THREADS;
            int remain = RUN_INTEVAL - e;
            if (remain > 0) {
                printf("count down: %d\n", remain);
            } else {
                printf("quiting app\n");
                foreach (MyThread* thread, m_threads) {
                    thread->setQuiting();
                }
                foreach (MyThread* thread, m_threads) {
                    thread->wait();
                    delete thread;
                }

                killTimer(m_timer_id);
                m_timer_id = 0;

                qApp->quit();
            }
        }
    }
    else {
        QObject::timerEvent(tEvent);
    }
}

