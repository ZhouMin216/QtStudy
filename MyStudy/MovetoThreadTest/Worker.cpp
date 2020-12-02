#include "Worker.h"
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>

using namespace Worker;

QWaitCondition condition_input; //数据收线程的条件变量，控制线程睡眠和唤醒
QWaitCondition condition_process;//数据处理线程的条件变量，控制线程睡眠和唤醒
QWaitCondition condition_output;//数据发线程的条件变量，控制线程睡眠和唤醒

//保护条件变量，防止多线程同时访问条件变量
QMutex mutex_input;
QMutex mutex_process;
QMutex mutex_output;

/********************************************DataInput**************************************************/
DataInput::DataInput(QObject *parent)
{
    Q_UNUSED(parent)
    m_loop = true;
    qDebug() << "I'm Worker::DataInput, my thread id is " << QThread::currentThread() << endl;
}

void DataInput::work()
{
    while (m_loop) {
       qDebug() << "Now at DataInput::work, thread id is " << QThread::currentThread() << endl;
       mutex_process.lock();
       condition_process.wakeOne();     //唤醒下一次的数据处理线程
       mutex_process.unlock();

       mutex_input.lock();
       condition_input.wait(&mutex_input);      //睡眠当前的收线程
       mutex_input.unlock();
    }
}

void DataInput::sleep()
{
    qDebug() << "Now at DataInput::sleep, thread id is " << QThread::currentThread() << endl;
    mutex_input.lock();
    condition_input.wait(&mutex_input);      //睡眠当前的收线程
    mutex_input.unlock();
}

void DataInput::stop()
{
    qDebug() << "======================== DataInput::stop() ======================";
    m_loop = false;
}


/********************************************DataProcess**************************************************/
DataProcess::DataProcess(QObject *parent)
{
    Q_UNUSED(parent)
    m_loop = true;
    qDebug() << "I'm Worker::DataProcess, my thread id is " << QThread::currentThread() << endl;
}

void DataProcess::work()
{
    while (m_loop) {
       qDebug() << "Now at DataProcess::work, thread id is " << QThread::currentThread() << endl;
       mutex_output.lock();
       condition_output.wakeOne();     //唤醒下一次的数据处理线程
       mutex_output.unlock();

       mutex_process.lock();
       condition_process.wait(&mutex_process);      //睡眠当前的收线程
       mutex_process.unlock();
    }
}

void DataProcess::sleep()
{
    qDebug() << "Now at DataProcess::sleep, thread id is " << QThread::currentThread() << endl;
    mutex_process.lock();
    condition_process.wait(&mutex_process);      //睡眠当前的收线程
    mutex_process.unlock();
}

void DataProcess::stop()
{
    qDebug() << "======================== DataProcess::stop() ======================";
    m_loop = false;
}

/********************************************DataOutput**************************************************/
DataOutput::DataOutput(QObject *parent)
{
    Q_UNUSED(parent)
    m_loop = true;
    qDebug() << "I'm Worker::DataOutput, my thread id is " << QThread::currentThread() << endl;
}

void DataOutput::work()
{
    while (m_loop) {
       qDebug() << "Now at DataOutput::work, thread id is " << QThread::currentThread() << endl;
       mutex_input.lock();
       condition_input.wakeOne();     //唤醒下一次的数据处理线程
       mutex_input.unlock();

       mutex_output.lock();
       condition_output.wait(&mutex_output);      //睡眠当前的收线程
       mutex_output.unlock();
    }
}

void DataOutput::sleep()
{
    qDebug() << "Now at DataOutput::sleep, thread id is " << QThread::currentThread() << endl;
    mutex_output.lock();
    condition_output.wait(&mutex_output);      //睡眠当前的收线程
    mutex_output.unlock();
}

void DataOutput::stop()
{
    qDebug() << "======================== DataOutput::stop() ======================";
    m_loop = false;
}


