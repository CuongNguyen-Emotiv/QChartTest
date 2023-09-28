#ifndef QWTDATAPRODUCER_H
#define QWTDATAPRODUCER_H

#include <QObject>
#include "DataProducer.h"

class QwtDataProducer : public DataProducer
{
    Q_OBJECT
public:
    explicit QwtDataProducer(int lineSeriesNumber, int pointsPerSec, QObject *parent = nullptr);

signals:
    void updateChart(QList<QVector<double>> xDataList, QList<QVector<double>> yDataList);

    // DataProducer interface
protected slots:
    virtual void producePoints() override;
    virtual void updateChartView() override;
    virtual void cleanOldData() override;

private:
    QList<QVector<double>> m_currentXDataList;
    QList<QVector<double>> m_currentYDataList;

    QList<QVector<double>> m_newXDataList;
    QList<QVector<double>> m_newYDataList;
};

#endif // QWTDATAPRODUCER_H
