#include "QcController.h"
#include <QValueAxis>

QcController::~QcController()
{
    m_lineSeriesList.clear();
}

void QcController::createDataProducers(QList<QAbstractSeries *> lineSeriesList, QValueAxis* axisX, QValueAxis* axisY)
{
    if (lineSeriesList.empty() || !axisX || !axisY) {
        return;
    }
    m_axisX = axisX;
    m_axisY = axisY;
    cleanUp();
    createDataProducerThread();
    m_dataProducers = new QcDataProducer(lineSeriesList.count(), m_pointPerSec);
    connect(m_dataProducers, &QcDataProducer::updateChart, this, &QcController::updateChart);
    m_dataProducers->moveToThread(m_dataProducerThread);
    connect(this, &QcController::startDataProducer, m_dataProducers, &QcDataProducer::start);
    connect(this, &QcController::stopDataProducer, m_dataProducers, &QcDataProducer::stop);
    connect(this, &QcController::stopDataProducer, m_dataProducers, &QcDataProducer::deleteLater);

    for (int i = 0; i < lineSeriesList.count(); ++i) {
        QLineSeries* lineSeries = (QLineSeries*)lineSeriesList[i];
        lineSeries->setUseOpenGL(true);
        lineSeries->setProperty("width", 1);
        m_lineSeriesList.append(lineSeries);
    }
    emit startDataProducer();
}

void QcController::cleanUp()
{
    emit stopDataProducer();
    m_lineSeriesList.clear();
    destroyDataProducerThread();
}

void QcController::updateChart(QList<QList<QPointF> > pointsList)
{
    for (int i = 0; i < pointsList.count(); ++i) {
        m_lineSeriesList[i]->replace(pointsList[i]);
    }

    if (pointsList.first().count() < m_pointPerSec*DATA_SECS) {
        m_axisX->setRange(pointsList.first().first().x(), pointsList.first().first().x() + (double)ONE_SEC_MS/1000 * DATA_SECS);
    } else {
        m_axisX->setRange(pointsList.first().first().x(), pointsList.first().last().x());
    }
}
