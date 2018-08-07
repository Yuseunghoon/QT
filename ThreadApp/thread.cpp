#include "thread.h"

Thread::Thread(QObject *obj)
{
    m_label=(QLabel*)obj;
    m_stopFlag=Play;

}

void Thread::run(){
    for(int count=0;;){
        m_mutex.lock();
        if(m_stopFlag == Stop)
            m_waitCondition.wait(&m_mutex);
        m_mutex.unlock();
        emit setLabel(QString("run%1").arg(count++));
        sleep(1);
    }
}

void Thread::stopThread(){
    m_stopFlag=Stop;
}

void Thread::resumeThread(){
    m_mutex.lock();
    m_stopFlag=Play;
    m_waitCondition.wakeAll();
    m_mutex.unlock();
}
