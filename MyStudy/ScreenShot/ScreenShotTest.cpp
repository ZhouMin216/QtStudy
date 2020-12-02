#include "ScreenShotTest.h"
#include "ScreenShot.h"
#include <QPushButton>
#include <QThread>
#include <QDebug>
#include <QFileDialog>

ScreenShotTest::ScreenShotTest(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);

    QPushButton *btn = new QPushButton("ScreenShot", this);
    btn->resize(100, 30);

    connect(btn, &QPushButton::clicked, this, &ScreenShotTest::slotScreenShot);
}

void ScreenShotTest::slotScreenShot()
{
    qDebug() << "ScreenShotTest::slotScreenShot, thread id is " << QThread::currentThreadId();

    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"full.jpg",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    qDebug() << "ScreenShotTest::slotScreenShot ========================= , thread id is " << QThread::currentThreadId();

    QThread *thread = new QThread;
    ScreenShot *screenShot = new ScreenShot;

    screenShot->setFilePathName(filename);

    connect(thread, &QThread::started, screenShot, &ScreenShot::slotGrabFullScreen);
    connect(thread, &QThread::finished, screenShot, &ScreenShot::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    screenShot->moveToThread(thread);
    thread->start();
}
