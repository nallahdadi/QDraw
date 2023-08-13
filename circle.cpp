#include "border.h"


CCircle::CCircle(QBrush b, QPen p):abrush(b), apen(p)
{
    //setFlags(ItemIsSelectable|ItemIsMovable);
    pressed = false;
    m_Rect.setRect(0,0,100,100);
}

QRectF CCircle::boundingRect() const
{
    return m_Rect;
}

void CCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //prepareGeometryChange();
    QRectF rect = boundingRect();
    if(pressed)
    {
        //abrush.setColor(Qt::red);
    }
    else
    {
        //abrush.setColor(Qt::yellow);
    }
    m_Rect = boundingRect();
    painter->setBrush(abrush);
    painter->setPen(apen);
    painter->drawEllipse(rect);
    static_cast<CBorder*>(parentItem())->DoneDrawing =true;
    //update(m_Rect);
    //update(parentItem()->boundingRect());

}

int CCircle::type() const
{
    return Type;
}

void CCircle::normalize(QRectF rect)
{
    m_Rect.setRect(rect.left()+borderMargin,rect.top()+borderMargin,
                   rect.width()-2*borderMargin,rect.height()-2*borderMargin);
}

void CCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed =true;
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CCircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CCircle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CCircle::updateItem()
{
    abrush = static_cast<CBorder*>(parentItem())->abrush;
}

