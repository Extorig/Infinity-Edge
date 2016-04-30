#include "fieldobject.h"
#include <QPainter>

FieldObject::FieldObject()
    : area(QRectF()), type(EMPTY),rotation(0),initdone(false)
{

}

void FieldObject::init(FieldType type, QRectF area){
    this->area = area;
    this->type = type;
    initdone=true;
}

bool FieldObject::filled(Side s){
    return filled((Side)((s+rotation)&0x3),type);
}

void FieldObject::rotate(){
    rotation = (rotation+1)&0x3;
}

void FieldObject::connectSides(Side start, Side end, QPainter *painter){

    unsigned int x = area.x();
    if(start==TOP || start==BOTTOM) x+= area.width()/2.;
    if(start==RIGHT) x+=area.width();

    unsigned int y = area.y();
    if(start==RIGHT || start==LEFT) y+= area.height()/2.;
    if(start==BOTTOM) y+=area.height();

    QPoint x1(x,
              y);

    x = area.x();
    if(end==TOP || end==BOTTOM) x+= area.width()/2.;
    if(end==RIGHT) x+=area.width();

    y = area.y();
    if(end==RIGHT || end==LEFT) y+= area.height()/2.;
    if(end==BOTTOM) y+=area.height();

    QPoint x2(x,
              y);
    painter->drawLine(x1,x2);
}

void FieldObject::connectSide(Side start,bool endpoint, QPainter *painter){
    unsigned int x = area.x();
    if(start==TOP || start==BOTTOM) x+= area.width()/2.;
    if(start==RIGHT) x+=area.width();

    unsigned int y = area.y();
    if(start==RIGHT || start==LEFT) y+= area.height()/2.;
    if(start==BOTTOM) y+=area.height();

    QPoint x1(x,
              y);

    QPoint x2(area.x()+area.width()/2.,area.y()+area.height()/2.);
    painter->drawLine(x1,x2);
    if(endpoint)
        painter->drawEllipse(QPointF(area.x()+area.width()/2.,area.y()+area.height()/2.),area.width()/4.,area.height()/4.);
}


bool FieldObject::filled(Side s, FieldType type){
    switch (s) {
    case TOP:
        return type==LTC || type==RTC || type==TBCROSS || type==TLCROSS || type==TRCROSS || type==VLINE || type==TEND || type==TT || type==TR || type==TL;
        break;
    case BOTTOM:
        return type==LBC || type==RBC || type==TBCROSS || type==TLCROSS || type==TRCROSS || type==VLINE || type==BEND || type==TB || type==TR || type==TL;
        break;
    case LEFT:
        return type==LBC || type==LTC || type==TBCROSS || type==TLCROSS || type==TRCROSS || type==HLINE || type==LEND || type==TT || type==TB || type==TL;
        break;
    case RIGHT:
        return type==RBC || type==RTC || type==TBCROSS || type==TLCROSS || type==TRCROSS || type==HLINE || type==REND || type==TT || type==TR || type==TB;
        break;
    default:
        return false;
        break;
    }
}

bool FieldObject::isPossible(QVector<Side> sidestobe, QVector<Side> sidesnottobe, FieldType type){
    bool ret = true;
    foreach(Side s, sidestobe){
        if(!filled(s,type))ret=false;
    }
    foreach(Side s,sidesnottobe){
        if(filled(s,type))ret=false;
    }

    return ret;
}


void FieldObject::paint(QPainter *painter){
    switch(type){
        case LTC:
            //connectSides((Side)((LEFT+rotation)&0x3),(Side)((TOP+rotation)&0x3),painter);
            connectSide((Side)((LEFT+rotation)&0x3),false,painter);
            connectSide((Side)((TOP+rotation)&0x3),false,painter);
            break;
        case LBC:
            //connectSides((Side)((LEFT+rotation)&0x3),(Side)((BOTTOM+rotation)&0x3),painter);
                connectSide((Side)((LEFT+rotation)&0x3),false,painter);
                connectSide((Side)((BOTTOM+rotation)&0x3),false,painter);
            break;
        case RTC:
            //connectSides((Side)((RIGHT+rotation)&0x3),(Side)((TOP+rotation)&0x3),painter);
            connectSide((Side)((RIGHT+rotation)&0x3),false,painter);
            connectSide((Side)((TOP+rotation)&0x3),false,painter);
            break;
        case RBC:
            //connectSides((Side)((RIGHT+rotation)&0x3),(Side)((BOTTOM+rotation)&0x3),painter);
            connectSide((Side)((RIGHT+rotation)&0x3),false,painter);
            connectSide((Side)((BOTTOM+rotation)&0x3),false,painter);
            break;
        case TBCROSS:
            connectSides((Side)((BOTTOM+rotation)&0x3),(Side)((TOP+rotation)&0x3),painter);
            connectSides((Side)((LEFT+rotation)&0x3),(Side)((RIGHT+rotation)&0x3),painter);
            break;
        case TLCROSS:
            connectSides((Side)((LEFT+rotation)&0x3),(Side)((TOP+rotation)&0x3),painter);
            connectSides((Side)((BOTTOM+rotation)&0x3),(Side)((RIGHT+rotation)&0x3),painter);
            break;
        case TRCROSS:
            connectSides((Side)((RIGHT+rotation)&0x3),(Side)((TOP+rotation)&0x3),painter);
            connectSides((Side)((LEFT+rotation)&0x3),(Side)((BOTTOM+rotation)&0x3),painter);
            break;
        case HLINE:
            connectSides((Side)((LEFT+rotation)&0x3),(Side)((RIGHT+rotation)&0x3),painter);
            break;
        case VLINE:
            connectSides((Side)((BOTTOM+rotation)&0x3),(Side)((TOP+rotation)&0x3),painter);
            break;
        case LEND:
            connectSide((Side)((LEFT+rotation)&0x3),true,painter);
            break;
        case REND:
            connectSide((Side)((RIGHT+rotation)&0x3),true,painter);
            break;
        case TEND:
            connectSide((Side)((TOP+rotation)&0x3),true,painter);
            break;
        case BEND:
            connectSide((Side)((BOTTOM+rotation)&0x3),true,painter);
            break;
        case TT:
            connectSide((Side)((TOP+rotation)&0x3),false,painter);
            connectSides((Side)((LEFT+rotation)&0x3),(Side)((RIGHT+rotation)&0x3),painter);
            break;
        case TB:
            connectSide((Side)((BOTTOM+rotation)&0x3),false,painter);
            connectSides((Side)((LEFT+rotation)&0x3),(Side)((RIGHT+rotation)&0x3),painter);
            break;
        case TR:
            connectSide((Side)((RIGHT+rotation)&0x3),false,painter);
            connectSides((Side)((TOP+rotation)&0x3),(Side)((BOTTOM+rotation)&0x3),painter);
            break;
        case TL:
            connectSide((Side)((LEFT+rotation)&0x3),false,painter);
            connectSides((Side)((TOP+rotation)&0x3),(Side)((BOTTOM+rotation)&0x3),painter);
            break;

        default:
            break;
    }

}
