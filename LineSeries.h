#ifndef LINESERIES_H
#define LINESERIES_H

#include <QObject>
#include "DataProducer.h"

class LineSeries : public QObject
{
    Q_OBJECT
public:
    explicit LineSeries(DataProducer* dataProducer, QLineSeries* lineSeries, QObject *parent = nullptr);
    ~LineSeries();

private slots:
    void updateChart(QList<QPointF> points);

signals:

private:
    QLineSeries* m_lineSeries;

};

#endif // LINESERIES_H
