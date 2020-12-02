#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>

class QWaitCondition;
class QMutex;

class ScreenShot : public QObject
{
    Q_OBJECT
public:
    explicit ScreenShot(QObject *parent = 0);
    virtual ~ScreenShot();

    void setFilePathName(QString str);
signals:

public slots:
    void slotGrabFullScreen();

private:
    int m_posX;
    int m_posY;
    int m_width;
    int m_height;

    QString m_filePathName;
//    QWaitCondition m_condition;
//    QMutex m_mutex;
};

#endif // SCREENSHOT_H
