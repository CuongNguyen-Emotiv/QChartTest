#ifndef QWTCONTROLLER_H
#define QWTCONTROLLER_H

#include "Controller.h"
#include "QwtChart.h"
#include "QwtLineSeries.h"

class QwtController : public Controller
{
    Q_OBJECT
public:
    Q_INVOKABLE void createDataProducers(QwtChart* qwtChart, int numberOfLineSeries);

private:
    QList<QwtLineSeries*> m_lineSeriesList;
};

#endif // QWTCONTROLLER_H
