#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include "fieldobject.h"
#include <QSize>

class QPainter;

class Field
{
public:
    explicit Field(FieldObject** objs, unsigned int width, unsigned int height, qreal objectsize);

    void redraw(QPainter *painter);
    void clicked(unsigned int x, unsigned int y);

    void resetLevel(int easiness);

    bool solved();


private:
    unsigned int width;
    unsigned int height;
    FieldObject** objs;
    qreal objectsize;
};

#endif // FIELD_H
