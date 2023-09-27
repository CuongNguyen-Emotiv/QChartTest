#ifndef QWTDATAPRODUCER_H
#define QWTDATAPRODUCER_H

#include <QObject>

class QwtDataProducer : public QObject
{
    Q_OBJECT
public:
    explicit QwtDataProducer(QObject *parent = nullptr);

signals:

};

#endif // QWTDATAPRODUCER_H
