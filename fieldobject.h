#ifndef FIELDOBJECT_H
#define FIELDOBJECT_H

#include <QObject>
#include <QRectF>
#include "sides.h"
#include <QVector>

typedef enum{
    LTC, //Corners, left/top etc.
    LBC,
    RTC,
    RBC,
    TBCROSS, //top/bot and left/right
    TLCROSS, //top/left and right/bot
    TRCROSS, //top/right and left/bot
    HLINE, //top/bot line
    VLINE, //LR line
    LEND,//ending pieces
    REND,
    TEND,
    BEND,
    TT,//Triangles, TBRL spitze
    TB,
    TR,
    TL,
    EMPTY
}FieldType;

class QPainter;

class FieldObject
{
public:
    FieldObject();

    void init(FieldType type,QRectF area);

    void paint(QPainter *painter);
    void rotate();
    //filling with respect to the current rotation
    bool filled(Side s);
    bool initialized(){return initdone;}

    static bool filled(Side s, FieldType type);
    static bool isPossible(QVector<Side> sidestobe, QVector<Side> sidesnottobe, FieldType type);

private:
    void connectSides(Side start, Side end, QPainter *painter);
    void connectSide(Side start, bool endpoint, QPainter *painter);

    QRectF area;
    FieldType type;
    unsigned int rotation;
    bool initdone;

};

#endif // FIELDOBJECT_H
