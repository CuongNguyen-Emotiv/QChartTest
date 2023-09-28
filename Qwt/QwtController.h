#ifndef QWTCONTROLLER_H
#define QWTCONTROLLER_H

#include "Controller.h"
#include "QwtChart.h"
#include "QwtDataProducer.h"

class QwtController : public Controller
{
    Q_OBJECT
public:
    virtual ~QwtController();
    Q_INVOKABLE void createDataProducers(QwtChart* qwtChart, int numberOfLineSeries);

private:
    int randomInt(int low, int high);

private slots:
    void updateChart(QList<QVector<double>> xDataList, QList<QVector<double>> yDataList);

private:
    QList<QwtPlotCurve*> m_lineSeriesList;
    QwtChart* m_qwtChart = nullptr;
    QwtDataProducer* m_dataProducer;
};

#endif // QWTCONTROLLER_H
