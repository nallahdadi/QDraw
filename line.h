#ifndef LINE_H
#define LINE_H

#include "constants.h"

class CLine: public QGraphicsItem
{
public:
    CLine(QBrush b, QPen p);
    enum {Type = line};
    int type() const;
    bool pressed, pressmove, isRightBt;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void normalize(QRectF rect);
    void updateItem();

    QRectF m_Rect;
    QPointF m_cursor,startPos, endPos;

    QBrush abrush;
    QPen   apen;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // LINE_H
