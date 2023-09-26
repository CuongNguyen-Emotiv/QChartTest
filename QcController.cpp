#include "QcController.h"
#include <QValueAxis>

QcController::~QcController()
{

}

void QcController::setPointsPerSec(int pointsPerSec)
{
    m_pointPerSec = pointsPerSec;
}

void QcController::createDataProducers(QList<QAbstractSeries *> seriesList)
{
    cleanUp();
    createDataProducerThreads();

    for (int i = 0; i < seriesList.count(); ++i) {
        QLineSeries* series = (QLineSeries*)seriesList[i];
        series->setUseOpenGL(true);
        QcDataProducer* dataProducer = new QcDataProducer(i * CHART_RANGE);

        dataProducer->moveToThread(m_dataProducerThreads[i % m_dataProducerThreads.count()]);
        dataProducer->moveToThread(m_dataProducerThreads[i % m_dataProducerThreads.count()]);
        dataProducer->setPointsPerSec(m_pointPerSec);
        connect(this, &QcController::startDataProducer, dataProducer, &QcDataProducer::start);
        connect(this, &QcController::stopDataProducer, dataProducer, &QcDataProducer::stop);
        
        QcLineSeries* lineSeries = new QcLineSeries(dataProducer, series);
        m_lineSeriesList.append(lineSeries);
        m_dataProducers.append(dataProducer);
    }
    emit startDataProducer();
}

void QcController::cleanUp()
{
    emit stopDataProducer();
    for (auto& lineSeries : m_lineSeriesList) {
        delete lineSeries;
    }
    m_lineSeriesList.clear();
    m_dataProducers.clear();

    destroyDataProducerThreads();
}

void QcController::createDataProducerThreads()
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

void QcController::destroyDataProducerThreads()
{
    emit stopDataProducer();
    for (auto& thread : m_dataProducerThreads) {
        thread->quit();
        thread->wait();
        delete thread;
    }
    m_dataProducerThreads.clear();
}
