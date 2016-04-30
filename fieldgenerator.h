#ifndef FIELDGENERATOR_H
#define FIELDGENERATOR_H

#include <QObject>
#include <QMap>
#include "fieldobject.h"
#include "field.h"
class QPainter;

class FieldGenerator : public QObject
{
    Q_OBJECT
public:
    explicit FieldGenerator(QObject *parent = 0);

    Field *generateLevel(qreal objsize, int width, int height, QMap<FieldType, qreal> probabilities);

signals:

public slots:

private:
};

#endif // FIELDGENERATOR_H
