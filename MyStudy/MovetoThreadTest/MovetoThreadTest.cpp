#include "MovetoThreadTest.h"
#include "Worker.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QThread>
#include <QDebug>

using namespace Worker;

MovetoThreadTest::MovetoThreadTest(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
    QHBoxLayout *layout = new QHBoxLayout();

    QPushButton *sleepBtn = new QPushButton();
    sleepBtn->resize(100, 40);
    sleepBtn->setText("Sleep");
    QPushButton *workBtn = new QPushButton();
    workBtn->resize(100, 40);
    workBtn->setText("Work");
    QPushButton *stopBtn = new QPushButton();
    stopBtn->resize(100, 40);
    stopBtn->setText("Stop");

    layout->addWidget(sleepBtn);
    layout->addWidget(workBtn);
    layout->addWidget(stopBtn);
    setLayout(layout);

    QThread *input_thread = new QThread;
    QThread *process_thread = new QThread;
    QThread *out_thread = new QThread;

    DataInput *data_input = new DataInput();
    DataProcess *data_process = new DataProcess();
    DataOutput *data_output = new DataOutput();

    data_input->moveToThread(input_thread);
    data_process->moveToThread(process_thread);
    data_output->moveToThread(out_thread);

    //开启线程
    input_thread ->start();
    process_thread ->start();
    out_thread ->start();

    //使得数据处理和数据发送线程睡眠的槽函数和按键sleepBtn的点击信号关联
    connect(sleepBtn,SIGNAL(clicked(bool)),data_process,SLOT(sleep()), Qt::QueuedConnection);
    connect(sleepBtn,SIGNAL(clicked(bool)),data_output,SLOT(sleep()), Qt::QueuedConnection);

    //使得三个线程的work槽函数和按键workBtn的点击信号关联
    connect(workBtn,SIGNAL(clicked(bool)),data_input,SLOT(work()));
    connect(workBtn,SIGNAL(clicked(bool)),data_process,SLOT(work()));
    connect(workBtn,SIGNAL(clicked(bool)),data_output,SLOT(work()));

//    connect(input_thread, SIGNAL(finished()), data_input, SLOT(deleteLater()) );
//    connect(process_thread, SIGNAL(finished()), data_process, SLOT(deleteLater()) );
//    connect(out_thread, SIGNAL(finished()), data_output, SLOT(deleteLater()) );

//    connect(input_thread, SIGNAL(finished()), input_thread, SLOT(deleteLater()) );
//    connect(process_thread, SIGNAL(finished()), process_thread, SLOT(deleteLater()) );
//    connect(out_thread, SIGNAL(finished()), out_thread, SLOT(deleteLater()) );


    connect(stopBtn, &QPushButton::clicked, this, [&](){
        qDebug() << "================================== quit =========================" << endl;
        data_input->stop();
        data_output->stop();
        data_process->stop();
    }, Qt::QueuedConnection);

}
