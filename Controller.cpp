#include "Controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::setPointsPerSec(int pointsPerSec)
{
    m_pointPerSec = pointsPerSec;
}

void Controller::createDataProducerThreads()
{
    unsigned int hardwareConcurrency = std::thread::hardware_concurrency();
    int dataProducerThreadNumber = hardwareConcurrency - 1;
    if (dataProducerThreadNumber < 1) {
        dataProducerThreadNumber = 1;
    }
    qDebug() << "dataProducerThreadNumber" << dataProducerThreadNumber;
    for (int i = 0; i < dataProducerThreadNumber; ++i) {
        QThread* thread = new QThread();
        thread->start();
        m_dataProducerThreads.append(thread);
    }
}

void Controller::destroyDataProducerThreads()
{
    emit stopDataProducer();
    for (auto& thread : m_dataProducerThreads) {
        thread->quit();
        thread->wait();
        delete thread;
    }
    m_dataProducerThreads.clear();
}
