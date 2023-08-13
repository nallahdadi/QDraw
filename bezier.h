#ifndef BEZIER_H
#define BEZIER_H
#include "constants.h"

class CBezier: public QGraphicsItem
{
public:
    CBezier(QBrush b, QPen p);

    enum {Type = bezier};
    int type() const;
    bool pressed,pressResize, pressMove,addbez;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void normalize(int corner);
    int IsCtrlPoint(QPointF point);
    void redrawWithCtrl();
    void normalize(QRectF rect);
    void updateItem();

    int ctrlcorner;
    QRectF m_Rect;
    QPainterPath myPath;
    QRectF sThumb[4];
    QPointF m_cursor;
    QList<QPointF> c;

    QBrush abrush;
    QPen   apen;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BEZIER_H
