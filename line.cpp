#include "border.h"

CLine::CLine(QBrush b, QPen p):abrush(b), apen(p)
{
    pressed = false;
    pressmove = true;
    isRightBt= false;
    m_Rect.setRect(0,0,200,200);
    //startPos = endPos = QPointF(0,0);
}

QRectF CLine::boundingRect() const
{
    return m_Rect;
}

void CLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(pressed)
    {
        //abrush.setColor(Qt::red);
    }
    else
    {
        //abrush.setColor(Qt::yellow);
    }
    painter->setBrush(abrush);
    painter->setPen(apen);
    painter->drawLine(m_Rect.topLeft(),m_Rect.bottomRight());
    static_cast<CBorder*>(parentItem())->DoneDrawing =true;
}

int CLine::type() const
{
    return Type;
}

void CLine::normalize(QRectF rect)
{
    m_Rect.setRect(rect.left()+borderMargin,rect.top()+borderMargin,
                   rect.width()-2*borderMargin,rect.height()-2*borderMargin);
}

void CLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed =true;
    m_cursor = event->pos();
    if(event->button() == Qt::RightButton) isRightBt=true;
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CLine::updateItem()
{
    apen = static_cast<CBorder*>(parentItem())->apen;
}

