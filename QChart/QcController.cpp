#include "QcController.h"
#include <QValueAxis>

QcController::~QcController()
{

}

void QcController::createDataProducers(QList<QAbstractSeries *> lineSeriesList)
{
    cleanUp();
    createDataProducerThreads();

    for (int i = 0; i < lineSeriesList.count(); ++i) {
        QLineSeries* series = (QLineSeries*)lineSeriesList[i];
        series->setUseOpenGL(true);
        QcDataProducer* dataProducer = new QcDataProducer(i * CHART_RANGE, m_pointPerSec);

        dataProducer->moveToThread(m_dataProducerThreads[i % m_dataProducerThreads.count()]);
        dataProducer->moveToThread(m_dataProducerThreads[i % m_dataProducerThreads.count()]);
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
