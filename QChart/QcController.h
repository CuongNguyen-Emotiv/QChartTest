#ifndef QCCONTROLLER_H
#define QCCONTROLLER_H

#include "QcDataProducer.h"
#include <QValueAxis>
#include <QObject>
#include <QQuickItem>
#include <QLineSeries>
#include "Controller.h"

class QcController : public Controller
{
    Q_OBJECT
public:
    ~QcController();
    Q_INVOKABLE void createDataProducers(QList<QAbstractSeries*> lineSeriesList, QValueAxis* axisX, QValueAxis* axisY);
    Q_INVOKABLE void cleanUp();

private:
    void updateChart(QList<QList<QPointF>> pointsList);

private:
    QcDataProducer* m_dataProducers;
    QList<QLineSeries*> m_lineSeriesList;
    QValueAxis *m_axisX = nullptr;
    QValueAxis *m_axisY = nullptr;
};

#endif // QCCONTROLLER_H
