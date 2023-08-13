#ifndef CIRCLE_H
#define CIRCLE_H

#include "constants.h"

class CCircle: public QGraphicsItem
{
public:
    CCircle(QBrush b, QPen p);
    enum {Type = circle};
    int type() const;
    bool pressed;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void normalize(QRectF rect);
    void updateItem();

    QRectF m_Rect;
    QPointF m_cursor;

    QBrush abrush;
    QPen   apen;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CIRCLE_H



