#include "border.h"

CArc::CArc(QBrush b, QPen p):abrush(b), apen(p)
{
    pressed = false;
    pressmove = true;
    isRightBt= false;
    spanAngle = startAngle = 0;
    m_Rect.setRect(10.0,20.0,80.0,60.0);
    //startPos = endPos = QPointF(0,0);
}

QRectF CArc::boundingRect() const
{
    return m_Rect;
}

void CArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    switch(itemType)
    {
    case 1:
        painter->drawArc(boundingRect(),startAngle*16,spanAngle*16);
        break;
    case 2:
        painter->drawPie(boundingRect(),startAngle*16,spanAngle*16);
        break;
    case 3:
        painter->drawChord(boundingRect(),startAngle*16,spanAngle*16);
        break;
    default:
        QMessageBox msgBox;
        msgBox.setText("item type out of range");
        msgBox.exec();
    }
    static_cast<CBorder*>(parentItem())->DoneDrawing =true;

}

int CArc::type() const
{
    return Type;
}

void CArc::normalize(QRectF rect)
{
    m_Rect.setRect(rect.left()+borderMargin,rect.top()+borderMargin,
                   rect.width()-2*borderMargin,rect.height()-2*borderMargin);
}

void CArc::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed =true;
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CArc::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CArc::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_cursor = event->pos();
    //update(parentItem()->boundingRect());
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void CArc::updateItem()
{
    abrush = static_cast<CBorder*>(parentItem())->abrush;
}
