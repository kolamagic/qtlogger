#include "mythread.h"

MyThread::MyThread(QObject *parent)
    : QThread(parent)
    , m_quiting(false)
    , m_mutex(QMutex::NonRecursive)
    , m_wait_cond()
{

}


void MyThread::setQuiting()
{
    m_mutex.lock();
    m_quiting = true;
    m_mutex.unlock();

    m_wait_cond.wakeOne();
}


void MyThread::run()
{
    static int counter = 0;
    for (;;) {
        m_mutex.lock();
        if (m_quiting) {
            m_mutex.unlock();
            qInfo("thread will quiting");
            break;
        }
        else {
            bool wait = m_wait_cond.wait(&m_mutex, 20);
            if (wait && m_quiting) {
                m_mutex.unlock();
                qInfo("thread will quiting");
                break;
            } else {
                m_mutex.unlock();

                for (int i=0; i<10; i++) {
                    ++counter;
                    switch (counter % 4) {
                    case 0:
                        qDebug("debug log %s", randstr().data());
                        break;
                    case 1:
                        qInfo("info log %s", randstr().data());
                        break;
                    case 2:
                        qWarning("warn info %s", randstr().data());
                        break;
                    case 3:
                        qCritical("error info %s", randstr().data());
                        break;
                    }
                }
            }
        }
    }
}


static QByteArray randword()
{
    static char letters[] = "abcdefghijklmnopqrstuvwxyz";

    int len = 3 + (qrand() % 12);
    QByteArray ret;
    for (int i=0; i<len; ++i) {
        int r = qrand() % (sizeof(letters));
        ret.append(letters[r]);
    }
    return ret;
}

QByteArray MyThread::randstr() const
{
    int words = 3 + (qrand() % 7);
    QByteArray ret;
    for (int i=0; i<words; ++i) {
        QByteArray word = randword();
        ret.append(word);
        ret.append(' ');
    }
    ret.append('\0');
    return ret;
}

