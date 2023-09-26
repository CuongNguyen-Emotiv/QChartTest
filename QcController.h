#ifndef QCCONTROLLER_H
#define QCCONTROLLER_H

#include "QcDataProducer.h"
#include <QValueAxis>
#include <QObject>
#include <QQuickItem>
#include <QLineSeries>
#include <QThread>
#include "QcLineSeries.h"

class QcController : public QObject
{
    Q_OBJECT
public:
    ~QcController();
    Q_INVOKABLE void setPointsPerSec(int pointsPerSec);
    Q_INVOKABLE void createDataProducers(QList<QAbstractSeries*> seriesList);
    Q_INVOKABLE void cleanUp();

signals:
    void startDataProducer();
    Q_INVOKABLE void stopDataProducer();

private:
    void createDataProducerThreads();
    void destroyDataProducerThreads();

private:
    QList<QThread*> m_dataProducerThreads;
    QList<QcDataProducer*> m_dataProducers;
    QList<QcLineSeries*> m_lineSeriesList;
    
    int m_pointPerSec = LOW_POINTS_PER_SEC;
};

#endif // QCCONTROLLER_H
