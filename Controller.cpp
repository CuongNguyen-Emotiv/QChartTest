#include "Controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

Controller::~Controller()
{
    destroyDataProducerThread();
}

void Controller::setPointsPerSec(int pointsPerSec)
{
    m_pointPerSec = pointsPerSec;
}

void Controller::createDataProducerThread()
{
    destroyDataProducerThread();
    m_dataProducerThread = new QThread();
    m_dataProducerThread->start();
}

void Controller::destroyDataProducerThread()
{
    emit stopDataProducer();
    if (m_dataProducerThread) {
        m_dataProducerThread->quit();
        m_dataProducerThread->wait();
        delete m_dataProducerThread;
        m_dataProducerThread = nullptr;
    }
}
