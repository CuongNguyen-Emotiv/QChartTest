#ifndef QCCONTROLLER_H
#define QCCONTROLLER_H

#include "QcDataProducer.h"
#include <QValueAxis>
#include <QObject>
#include <QQuickItem>
#include <QLineSeries>
#include "Controller.h"
#include "QcLineSeries.h"

class QcController : public Controller
{
    Q_OBJECT
public:
    ~QcController();
    Q_INVOKABLE void createDataProducers(QList<QAbstractSeries*> lineSeriesList);
    Q_INVOKABLE void cleanUp();

private:
    QList<QcDataProducer*> m_dataProducers;
    QList<QcLineSeries*> m_lineSeriesList;
};

#endif // QCCONTROLLER_H
