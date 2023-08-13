#include "border.h"
#include <QTextOption>

CText::CText()
{
    pressed = false;
    m_Rect.setRect(0,0,100,50);
    textOption.setAlignment(Qt::AlignCenter);
}

QRectF CText::boundingRect() const
{
    return m_Rect;
}

void CText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush abrush = QBrush(Qt::yellow);
    if(pressed)
    {
        //abrush.setColor(Qt::red);
    }
    else
    {
        //abrush.setColor(Qt::yellow);
    }
    painter->setBrush(abrush);
    painter->drawText(m_Rect,text,textOption);
    static_cast<CBorder*>(parentItem())->DoneDrawing =true;

}

int CText::type() const
{
    return Type;
}

void CText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed =true;
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CText::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}
