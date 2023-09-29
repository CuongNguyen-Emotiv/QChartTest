#ifndef PRODATAPROCEDUCER_H
#define PRODATAPROCEDUCER_H

#include <DataProducer.h>

class ProDataProceducer : public DataProducer
{
    Q_OBJECT
public:
    explicit ProDataProceducer(int lineSeriesNumber, int pointsPerSec, QObject *parent = nullptr);

signals:
    void updateChart(QList<QVector<double>> xDataList, QList<QVector<double>> yDataList);

    // DataProducer interface
protected slots:
    virtual void producePoints() override;
    virtual void updateChartView() override;
    virtual void cleanOldData() override;

private:
    QList<QVector<double>> m_xDataList;
    QList<QVector<double>> m_yDataList;

    int m_count;
    QList<QVector<double>> m_newXList;
    QList<QVector<double>> m_newYList;
};

#endif // PRODATAPROCEDUCER_H
