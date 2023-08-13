#ifndef BORDER_H
#define BORDER_H

#include "constants.h"

/// include item header files

#include "rectangle.h"
#include "circle.h"
#include "polygan.h"
#include "bezier.h"
#include "thumb.h"
#include "line.h"
#include "arc.h"
#include "text.h"

#include <QObject>

/// this class is the parent of all shapes will draw in view
/// it have 8 points to resizing rectangular border around the shape
/// and one point for rotating in the view

class CBorder:public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CBorder(int itemType);
    enum {Type = border};
    //enum CBorderItem { arc, bezier, circle, line, polygan, rectangle,text };
    int type() const;
    QString type();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setBorderFromItemSize(QGraphicsItem* item);
    bool normalize(int corner);
    QGraphicsItem* selectedItem();
    void updateItem();
    int  IsCornerPos(QPointF point);
    bool IsinBounding(QPointF point);
    void resizeWithHandles();

    int type1;

    bool    pressed,  pressResize, pressMove, drawCHandle, DoneDrawing;
    QPointF m_cursor, startPos,    endPos,    oldPos;
    QRectF  m_Rect,   borderRect, oldRect;

    QList<QGraphicsItem*> childList;
    CThumb*  m_cornerHandle[9];
    int      corner;
    QBrush   abrush, oldBrush;
    QPen     apen,   oldPen;

signals:
    void itemMoved(CBorder* border,QPointF movedFromPosition);
    void itemResized(CBorder* border,QRectF ResizeFirstRect);
    void MouseDoubleClicked(CBorder* border,QGraphicsSceneMouseEvent *event);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void setcornnerhandles();
};


#endif // BORDER_H
