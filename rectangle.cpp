#include "border.h"


CRectangle::CRectangle(QBrush b, QPen p):abrush(b), apen(p)
{
    //setFlags(ItemIsSelectable|ItemIsMovable);
    pressed = false;
    m_Rect.setRect(0,0,100,100);
}

QRectF CRectangle::boundingRect() const
{
    return m_Rect;
}

void CRectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //prepareGeometryChange();
    QRectF rect = boundingRect();
    if(pressed)
    {
        //abrush.setColor(Qt::red);
    }
    else
    {
       // abrush.setColor(Qt::green);
    }
    m_Rect = boundingRect();
    painter->fillRect(rect,abrush);
    painter->setPen(apen);
    painter->drawRect(rect);
    static_cast<CBorder*>(parentItem())->DoneDrawing =true;
    //update();
}

int CRectangle::type() const
{
    return Type;
}

void CRectangle::normalize(QRectF rect)
{
    m_Rect.setRect(rect.left()+borderMargin,rect.top()+borderMargin,
                   rect.width()-2*borderMargin,rect.height()-2*borderMargin);
}


void CRectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    m_cursor = event->pos();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    m_cursor = event->pos();
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void CRectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    m_cursor = event->pos();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CRectangle::updateItem()
{
    abrush = static_cast<CBorder*>(parentItem())->abrush;
}
