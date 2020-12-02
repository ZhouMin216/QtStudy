#ifndef WORKER_H
#define WORKER_H

#include <QObject>

namespace Worker {

    class DataInput : public QObject
    {
        Q_OBJECT
    public:
        explicit DataInput(QObject *parent = 0);
    signals:

    public slots:
        void work();
        void sleep();
        void stop();
    private:
        bool m_loop;
    };

    class DataProcess : public QObject
    {
        Q_OBJECT
    public:
        explicit DataProcess(QObject *parent = 0);
    signals:

    public slots:
        void work();
        void sleep();
        void stop();
    private:
        bool m_loop;
    };

    class DataOutput : public QObject
    {
        Q_OBJECT
    public:
        explicit DataOutput(QObject *parent = 0);
    signals:

    public slots:
        void work();
        void sleep();
        void stop();
    private:
        bool m_loop;
    };
}


#endif // WORKER_H
