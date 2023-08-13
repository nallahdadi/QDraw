#ifndef ARC_H
#define ARC_H

#include "constants.h"

class CArc : public QGraphicsItem
{
public:
    CArc(QBrush b, QPen p);
    enum {Type = arc};
    int type() const;
    bool pressed, pressmove, isRightBt;
    int spanAngle, startAngle, itemType;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void normalize(QRectF rect);
    void updateItem();
    QRectF m_Rect;
    QPointF m_cursor,startPos, endPos;
    void setItemType(int tp) {itemType = tp;}

    QBrush abrush;
    QPen   apen;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

#endif // ARC_H
