#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "Constant.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    Q_INVOKABLE void setPointsPerSec(int pointsPerSec);

protected:
    void createDataProducerThreads();
    void destroyDataProducerThreads();

signals:
    void startDataProducer();
    Q_INVOKABLE void stopDataProducer();

protected:
    QList<QThread*> m_dataProducerThreads;

    int m_pointPerSec = LOW_POINTS_PER_SEC;
};

#endif // CONTROLLER_H
