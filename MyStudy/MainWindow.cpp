#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "MovetoThreadTest.h"
#include "ScreenShotTest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    MovetoThreadTest * ovetoThreadTestWig = new MovetoThreadTest(this) ;
//    setCentralWidget(ovetoThreadTestWig);

    ScreenShotTest *screenShotTest = new ScreenShotTest;
    setCentralWidget(screenShotTest);

}

MainWindow::~MainWindow()
{
    delete ui;
}
