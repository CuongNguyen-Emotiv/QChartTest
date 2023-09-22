#ifndef FPSTEXT_H
#define FPSTEXT_H

#include <QQuickPaintedItem>

class FPSText : public QQuickPaintedItem
{
    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)
    Q_OBJECT
public:
    FPSText(QQuickItem *parent = 0);
    void paint(QPainter *);
    int fps() const;

signals:
    void fpsChanged(int);

private:
    void recalculateFPS();
    int _currentFPS;
    int _cacheCount;
    QVector<qint64> _times;
};

#endif // FPSTEXT_H
