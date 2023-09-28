#ifndef QWTCONTROLLER_H
#define QWTCONTROLLER_H

#include "Controller.h"
#include "QwtChart.h"
#include "QwtDataProducer.h"

class QwtController : public Controller
{
    Q_OBJECT
public:
    QwtController(QObject *parent = nullptr);
    Q_INVOKABLE void createDataProducers(QwtChart* qwtChart, int numberOfLineSeries);

private slots:
    void updateChart(QList<QVector<double>> xDataList, QList<QVector<double>> yDataList);

private:
    QList<QwtPlotCurve*> m_lineSeriesList;
    QwtChart* m_qwtChart = nullptr;
    QwtDataProducer* m_dataProducer;
};

#endif // QWTCONTROLLER_H
