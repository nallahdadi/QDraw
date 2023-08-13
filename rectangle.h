#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "constants.h"

class CRectangle: public QGraphicsItem
{
public:
    CRectangle(QBrush b, QPen p);
    enum {Type = rectangle};
    int type()const;
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
    void m(void);
};

#endif // RECTANGLE_H
