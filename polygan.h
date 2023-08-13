#ifndef POLYGAN_H
#define POLYGAN_H

#include "constants.h"

class CPolygan: public QGraphicsItem
{
public:
    CPolygan(QBrush b, QPen p);
    enum {Type = polygan};
    int type() const;
    bool pressed,moving,rightPress,addpoly, gon;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void normalize(QRectF rect);
    void updateItem();

    bool  IsinBounding(QPointF point,QRectF rect);
    QRectF m_Rect;
    QPolygonF polyPoints;
    QPointF m_cursor;
    QPointF startPos;
    QPointF endPos;

    QRectF sThumb;

    QBrush abrush;
    QPen   apen;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


#endif // POLYGAN_H
