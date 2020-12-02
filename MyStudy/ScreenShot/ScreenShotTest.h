#ifndef SCREENSHOTTEST_H
#define SCREENSHOTTEST_H

#include <QWidget>

class ScreenShotTest : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenShotTest(QWidget *parent = 0);

signals:

public slots:
    void slotScreenShot();
};

#endif // SCREENSHOTTEST_H
