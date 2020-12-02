#include "ScreenShot.h"
#include <QScreen>
#include <QGuiApplication>
#include <QDateTime>
#include <QDebug>

#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QPixmap>

ScreenShot::ScreenShot(QObject *parent) : QObject(parent), m_posX(0), m_posY(0),
   m_width(0), m_height(0), m_filePathName("")
{
//    m_mutex.lock();
//    m_condition.wait(&m_mutex);
//    m_mutex.unlock();
    qDebug() << "ScreenShot has be created" << endl;
}

ScreenShot::~ScreenShot()
{
    qDebug() << "delete ScreenShot" << endl;
}

void ScreenShot::setFilePathName(QString str)
{
    qDebug() << "ScreenShot::setFilePathName, thread id is " << QThread::currentThreadId();
    qDebug() << str << endl;
    m_filePathName = str;
}


void ScreenShot::slotGrabFullScreen()
{
    qDebug() << "ScreenShot::slotGrabFullScreen, thread id is " << QThread::currentThreadId();

    QScreen *screen = QGuiApplication::primaryScreen();

    if(m_filePathName.isEmpty())
    {
        m_filePathName = "full-";
        m_filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
        m_filePathName += ".jpg";
    }

//    QString filePathName = "full-";
//    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
//    filePathName += ".jpg";
    if(!screen->grabWindow(0, 0, 0, 800, 600).save(m_filePathName, "jpg"))
    {
        qDebug()<<"save full screen failed"<<endl;
    }
}
