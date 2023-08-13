#ifndef THUMB_H
#define THUMB_H
#include "constants.h"

class CThumb: public QGraphicsItem
{
public:
    CThumb(QPointF Start,int Size=10);
    CThumb(int x, int y,int Size=10);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setSize(int s);
    int x() const {return start.x();}
    int y() const {return start.y();}
    bool IsinThumb(QPointF point);
private:
    QPointF start;
    QSizeF size;
};

#endif // THUMB_H
